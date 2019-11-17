/**
 * This is a node listen to a topic, which will send a list of target objects,
 * and fuse a series of detection results.
 *
 * Author: BIgRunner
 * email: xnhan@mail.ustc.edu.cn
 */

// #include <math.h>
#include <mutex>
#include <vector>
#include <iterator>

#include <ros/ros.h>
#include <ros/spinner.h>
#include <ros/callback_queue.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <image_transport/image_transport.h>
#include <image_transport/subscriber_filter.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <cv_bridge/cv_bridge.h>
// #include <time.h>

#include <opencv2/core/core.hpp>

#include "id_data_msgs/ID_Data.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "darknet_ros_msgs/BoundingBox.h"
#include "kinect_detect_msgs/ObjectIDs.h"
#include "kinect_detect_msgs/ObjectPose.h"
#include "kinect_detect_msgs/ObjectPoses.h"

struct TargetRoughPose
{
    int class_id;
    double confidence;
    int counts;
    int rect[4];             // Rectangular area of object in image
    double center[3];        // Pose center of object
    double quaternation[4];  // Quaternation of object

};

struct Rectangular
{
    int x, y, w, h;
};

class DetectionFuser
{
private:
    std::mutex lock;

    double duration;
    double iou_thresh;

    ros::MultiThreadedSpinner spinner;

    ros::NodeHandle nh_1_, nh_2_;
    ros::CallbackQueue callbackQueue_1_;
    ros::CallbackQueue callbackQueue_2_;
    ros::Subscriber notice_listener_;
    ros::Publisher notice_responser_;
    ros::Publisher detect_publisher_;
    ros::Subscriber yolo_listenser_;
    ros::Subscriber list_listener_;
    // ros::Subscriber linemod_listener_;



    // show the status of the fuser
    bool detecting;
    // update object list at the beginning of each detection process
    bool updated;

    // record all objects to be detected
    std::vector<uint> object_ids;
    // tough pose record of all objects
    std::vector<TargetRoughPose> object_rough_poses;
    std::vector<TargetRoughPose> object_fine_poses;
    // record of all objects
    //
    kinect_detect_msgs::ObjectPoses object_poses_results_;


    id_data_msgs::ID_Data id_data;

    cv::Mat T_eye2hand;

    image_transport::ImageTransport imageTransport_;
    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image, sensor_msgs::CameraInfo> ColorDepthSyncPolicy;
    image_transport::SubscriberFilter *subImageColor, *subImageDepth;
    message_filters::Subscriber<sensor_msgs::CameraInfo> *subCameraInfo;
    message_filters::Synchronizer<ColorDepthSyncPolicy> *sync;

    cv::Mat colorImageCopy_;
    cv::Mat depthImageCopy_;

    cv::Mat cameraIntrinsicMatrix_, cameraDistortionCoefficients_;


    // workspace
    double low_xmin, low_xmax, low_ymin, low_ymax, low_zmin, low_zmax;
    double mid_xmin, mid_xmax, mid_ymin, mid_ymax, mid_zmin, mid_zmax;
    double high_xmin, high_xmax, high_ymin, high_ymax, high_zmin, high_zmax;


public:
    DetectionFuser(): nh_1_("hh_1_"), nh_2_("nh_2_"), imageTransport_(nh_1_), detecting(false), updated(false),
                      spinner(0)
    {
        init();
        if (!readParameters())
            ros::requestShutdown();
    }

    ~DetectionFuser(){}

    void run()
    {
        start();
        stop();
    }

private:
    void id_data_clear()
    {
        lock.lock();
        id_data.id = 0;
        for(int i=0; i<8; i++)
            id_data.data[i] = 0;
        lock.unlock();
    }


    void init()
    {
        // read eye2_hand calibration file
        std::string calibPath;
        std::string calibFile;
        nh_1_.param("calib_results/name", calibFile, std::string("external-calib-results.yaml"));
        nh_1_.param("calib_path", calibPath, std::string("/default"));
        calibPath += "/" + calibFile;

        cv::FileStorage fs(calibPath, cv::FileStorage::READ);
        fs["T_eye2hand"] >> T_eye2hand;
        fs.release();

        // listen to kinect
        std::string colorTopicName;
        std::string depthTopicName;
        std::string cameraInfoTopicName;
        nh_1_.param("subscribers/color_reading/topic", colorTopicName,
                std::string("/kinect2/qhd/image_color_rect"));
        nh_1_.param("subscribers/depth_reading/topic", depthTopicName,
                std::string("/kinect2/qhd/image_depth_rect"));
        nh_1_.param("subscribers/camera_info/topic", cameraInfoTopicName,
                std::string("/kinect2/qhd/camera_info"));


        notice_listener_ = nh_1_.subscribe("/notice", 1000, &DetectionFuser::notice_sub_callback, this);
        notice_responser_ = nh_1_.advertise<id_data_msgs::ID_Data>("/notice", 1000);
        detect_publisher_ = nh_1_.advertise<kinect_detect_msgs::ObjectPose>("/objects_detected", 1000);

        list_listener_ = nh_1_.subscribe("/objects_to_detect", 1000, &DetectionFuser::update_list, this);
        yolo_listenser_ = nh_2_.subscribe("/bounding_boxes", 1000, &DetectionFuser::yolo_fuse_callback, this);
        // linemod_listener_ = nh.subscribe("/", 1000, linemod_fuse_callback);

        nh_1_.setCallbackQueue(&callbackQueue_1_);
        nh_2_.setCallbackQueue(&callbackQueue_2_);

        image_transport::TransportHints hints("compressed");
        subImageColor = new image_transport::SubscriberFilter(imageTransport_, colorTopicName, 1, hints);
        subImageDepth = new image_transport::SubscriberFilter(imageTransport_, depthTopicName, 1, hints);
        subCameraInfo = new message_filters::Subscriber<sensor_msgs::CameraInfo>(nh_1_, cameraInfoTopicName, 1);

        sync = new message_filters::Synchronizer<ColorDepthSyncPolicy>(
                    ColorDepthSyncPolicy(5), *subImageColor, *subImageDepth, *subCameraInfo);
        sync -> registerCallback(boost::bind(&DetectionFuser::cameraCallback, this, _1, _2, _3));
    }

    bool readParameters()
    {
        nh_1_.param("detect_paras/duration", duration, 3.0);
        nh_1_.param("detect_paras/iou_thresh", iou_thresh, 0.5);

        nh_1_.param("workspace/low/xmin", low_xmin, 150.0);
        nh_1_.param("workspace/low/xmax", low_xmax, 400.0);
        nh_1_.param("workspace/low/ymin", low_ymin, -800.0);
        nh_1_.param("workspace/low/ymax", low_ymax, -400.0);
        nh_1_.param("workspace/low/zmin", low_zmin, 300.0);
        nh_1_.param("workspace/low/zmax", low_zmax, 450.0);

        nh_1_.param("workspace/mid/xmin", mid_xmin, 150.0);
        nh_1_.param("workspace/mid/xmax", mid_xmax, 400.0);
        nh_1_.param("workspace/mid/ymin", mid_ymin, -800.0);
        nh_1_.param("workspace/mid/ymax", mid_ymax, -400.0);
        nh_1_.param("workspace/mid/zmin", mid_zmin, 600.0);
        nh_1_.param("workspace/mid/zmax", mid_zmax, 750.0);

        nh_1_.param("workspace/high/xmin", high_xmin, 150.0);
        nh_1_.param("workspace/high/xmax", high_xmax, 400.0);
        nh_1_.param("workspace/high/ymin", high_ymin, -800.0);
        nh_1_.param("workspace/high/ymax", high_ymax, -400.0);
        nh_1_.param("workspace/high/zmin", high_zmin, 900.0);
        nh_1_.param("workspace/high/zmax", high_zmax, 1050.0);

        ROS_DEBUG("Parameters have been read...");

        return true;
    }


    void start()
    {

        spinner.spin(&callbackQueue_1_);

        // std::chrono::milliseconds duration(1);

        while (!detecting)
        {
            if(!ros::ok())
            {
                return;
            }
            // std::this_thread::sleep_for(duration);
            ros::Duration(0.1).sleep();
        }

        ROS_DEBUG("Begin to fuse detection results.");

        detectionFuse();


    }

    void stop()
    {
        delete subImageColor;
        delete subImageDepth;
        delete subCameraInfo;
        delete sync;
    }

    void notice_sub_callback(const id_data_msgs::ID_Data::ConstPtr& id_data_msg)
    {
        // judge whether it's a msg for detect and response
        if(id_data_msg -> id == 3 && id_data_msg -> data[0] == 1)
        {
            lock.lock();
            detecting = true;
            lock.unlock();

            id_data_clear();
            id_data.id = 3;
            id_data.data[0] = 14;
            notice_responser_.publish(id_data);
            id_data_clear();
        }
    }

    void update_list(const kinect_detect_msgs::ObjectIDs::ConstPtr& object_ids_msg)
    {
        if(detecting && !updated)
        {
            // manage object_list
            lock.lock();
            object_ids = object_ids_msg -> object_ids;
            updated = true;
            lock.unlock();
        }

    }

    void yolo_fuse_callback(const darknet_ros_msgs::BoundingBoxes::ConstPtr& bounding_boxes_msg)
    {
        if(detecting && updated)
        {
            // update detection results
            std::vector<darknet_ros_msgs::BoundingBox> boxes = bounding_boxes_msg -> bounding_boxes;
            for (std::vector<darknet_ros_msgs::BoundingBox>::iterator it = boxes.begin();
                    it != boxes.end(); ++it)
            {
                updateObjectLists(*it);
            }
        }
    }

    void cameraCallback(const sensor_msgs::Image::ConstPtr colorMsg,
            const sensor_msgs::Image::ConstPtr depthMsg,
            const sensor_msgs::CameraInfo::ConstPtr cameraInfo)
    {
        ROS_INFO("Images are received.");

        cv_bridge::CvImagePtr colorImage;
        cv_bridge::CvImagePtr depthImage;
        cv::Mat color, depth;

        try
        {
            colorImage = cv_bridge::toCvCopy(colorMsg, colorMsg->encoding);
            depthImage = cv_bridge::toCvCopy(depthMsg, depthMsg->encoding);
            // imageHeader_ = colorMsg->header;
            color = colorImage->image.clone();
            depth = depthImage->image.clone();
        }
        catch(cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        lock.lock();
        colorImageCopy_ = color;
        depthImageCopy_ = depth;
        readCameraInfo(cameraInfo);
        lock.unlock();

    }

    void readCameraInfo(const sensor_msgs::CameraInfo::ConstPtr &cameraInfo)
    {
        double *itC = cameraIntrinsicMatrix_.ptr<double>(0, 0);
        for(size_t i = 0; i < 9; ++i, ++itC)
        {
            *itC = cameraInfo->K[i];
        }

        double *itD = cameraDistortionCoefficients_.ptr<double>(0, 0);
        for(size_t i = 0; i < 9; ++i, ++itD)
        {
            *itD = cameraInfo->D[i];
        }
    }

    // void linemod_fuse_callback(const MSG)
    // {
    //     if(detecting && updated)
    //     {
    //         for ()
    //     }
    // }

    void detectionFuse()
    {
        while(ros::ok())
        {
            if(detecting && updated)

            {
                object_rough_poses.clear();
                object_fine_poses.clear();

                callbackQueue_2_.callAvailable(ros::WallDuration(duration));

                lock.lock();


                detecting = false;
                updated = false;

                fineFuse();
                lock.unlock();

                filterByList();
                filterByWorkSpace();

                // imform ge_test, detection task finished
                id_data_clear();
                lock.lock();
                id_data.id = 3;
                id_data.data[0] = 15;
                notice_responser_.publish(id_data);
                lock.unlock();
                id_data_clear();


                // publish detection fusion results
                ROS_DEBUG("publishing detection fustion results...");
                publishTargetPose();


            }
        }
    }

    // find the object in same position update it
    void updateObjectLists(darknet_ros_msgs::BoundingBox& box)
    {
        ROS_DEBUG("Updating the object list...");
        bool found = false;
        for (std::vector<TargetRoughPose>::iterator it = object_rough_poses.begin();
                it != object_rough_poses.end(); ++it)
        {
            if(it->class_id == box.class_id && computeIOU(*it, box) > iou_thresh)
            {
                found = true;
                if(box.probability > it -> confidence)
                {
                    it -> counts ++;
                    it -> confidence = box.probability;
                    it -> rect[0] = box.xmin;
                    it -> rect[1] = box.ymin;
                    it -> rect[2] = box.xmax - box.xmin;
                    it -> rect[3] = box.ymax - box.ymin;
                }
            }
        }

        if(!found)
        {
            TargetRoughPose roughPose_;
            roughPose_.class_id = box.class_id;
            roughPose_.counts = 0;
            roughPose_.confidence = box.probability;
            roughPose_.rect[0] = box.xmin;
            roughPose_.rect[1] = box.ymin;
            roughPose_.rect[2] = box.xmax - box.xmin;
            roughPose_.rect[3] = box.ymax - box.ymin;
            object_rough_poses.push_back(roughPose_);
        }
    }


    // Try to filter wrong detected objects in same position
    void fineFuse()
    {
        ROS_DEBUG("Filtering objects at same position ...");
        bool found = false;
        for(std::vector<TargetRoughPose>::iterator it_rough = object_rough_poses.begin();
                it_rough != object_rough_poses.end(); it_rough++)
        {
            for(std::vector<TargetRoughPose>::iterator it_fine = object_fine_poses.begin();
                    it_fine != object_rough_poses.end(); it_rough++)
            {
                if(computeIOU(*it_rough, *it_fine) > iou_thresh)
                {
                    found = true;
                    if(it_rough -> counts > it_fine -> counts)
                    {
                        *it_fine = *it_rough;
                    }
                }
            }

            if(!found)
            {
                object_fine_poses.push_back(*it_rough);
            }
        }
    }

    double computeIOU(const Rectangular &rect_1, const Rectangular &rect_2)
    {
        double ratio = 0.0;

        double xmax = std::max(rect_1.x + rect_1.w, rect_2.x + rect_2.w);
        double xmin = std::min(rect_1.x, rect_2.x);
        double width = rect_1.w + rect_2.w - (xmax - xmin);

        double ymax = std::max(rect_1.y + rect_1.h, rect_2.y + rect_2.h);
        double ymin = std::min(rect_1.y, rect_2.y);
        double height = rect_1.w + rect_2.w -(ymax - ymin);

        if(width > 0.0 && height > 0.0)
        {
            double area = width * height;
            double area1 = rect_1.w * rect_1.h;
            double area2 = rect_2.w * rect_2.h;
            ratio = area / (area1 + area2 - area);
        }

        return ratio;

    }

    double computeIOU(const TargetRoughPose &pose, const darknet_ros_msgs::BoundingBox &box)
    {
        Rectangular rect_1;
        rect_1.x = pose.rect[0];
        rect_1.y = pose.rect[1];
        rect_1.w = pose.rect[2];
        rect_1.h = pose.rect[3];
        Rectangular rect_2;
        rect_2.x = box.xmin;
        rect_2.y = box.ymin;
        rect_2.w = box.xmax - box.xmin;
        rect_2.h = box.ymax - box.ymin;
        return computeIOU(rect_1, rect_2);
    }

    double computeIOU(const TargetRoughPose &pose_1, const TargetRoughPose &pose_2)
    {
        Rectangular rect_1;
        rect_1.x = pose_1.rect[0];
        rect_1.y = pose_1.rect[1];
        rect_1.w = pose_1.rect[2];
        rect_1.h = pose_1.rect[3];
        Rectangular rect_2;
        rect_2.x = pose_2.rect[0];
        rect_2.y = pose_2.rect[1];
        rect_2.w = pose_2.rect[2];
        rect_2.h = pose_2.rect[3];
        return computeIOU(rect_1, rect_2);
    }

    void filterByList()
    {
        ROS_DEBUG("Find objects in the list...");
        std::vector<uint>::iterator result;
        std::vector<TargetRoughPose> temp;
        for(std::vector<TargetRoughPose>::iterator it_fine = object_fine_poses.begin();
                it_fine != object_fine_poses.end(); it_fine ++)
        {
            result = find(object_ids.begin(), object_ids.end(), it_fine->class_id);
            if(result != object_ids.end())
            {
                temp.push_back(*it_fine);
            }
        }

        object_fine_poses.clear();
        object_fine_poses = temp;
    }

    // O
    void filterByWorkSpace()
    {
        ROS_DEBUG("Filtering objects out of range...");
        std::vector<TargetRoughPose> results;
        for (std::vector<TargetRoughPose>::iterator it_fine = object_fine_poses.begin();
                it_fine != object_fine_poses.end(); it_fine++)
        {
            if(withInSpace(*it_fine))
            {
                results.push_back(*it_fine);
            }
        }
        object_fine_poses = results;
    }


    bool withInSpace(TargetRoughPose &pose)
    {
        cv::Point2d center;
        center.x = pose.rect[0] + pose.rect[2]/2;
        center.y = pose.rect[1] + pose.rect[3]/2;
        int c_left = (center.x - 5) > pose.rect[0] ? (center.x - 5) : pose.rect[0];
        int c_right = (center.x + 5) > pose.rect[0] + pose.rect[2]? (center.x + 5) : pose.rect[0] + pose.rect[2];
        int r_top = (center.y - 5) > pose.rect[1] ? (center.y - 5) : pose.rect[1];
        int r_bottom = (center.y + 5) > pose.rect[1] + pose.rect[3]? (center.y + 5) : pose.rect[1] + pose.rect[3];

        bool valid = false;

        int depth;
        int depth_sum = 0;
        int valid_counter = 0;
        lock.lock();
        for (int r = r_top; r <= r_bottom; r++)
            for (int c = c_left; c <= c_right; c++)
            {
                depth = depthImageCopy_.ptr<ushort>(r)[c];
                if(depth != 0)
                {
                    depth_sum += depth;
                    valid_counter += 1;
                }
            }
        lock.unlock();

        cv::Point3f targetPoint;
        if (valid_counter > 9)
        {
            lock.lock();
            double depth_average = (double)depth_sum/valid_counter;
            targetPoint.z = depth_average / 1000.0;
            targetPoint.x = (center.x - cameraIntrinsicMatrix_.ptr<double>(0)[2]) * targetPoint.z / cameraIntrinsicMatrix_.ptr<double>(0)[0];
            targetPoint.y = (center.y - cameraIntrinsicMatrix_.ptr<double>(1)[2]) * targetPoint.z / cameraIntrinsicMatrix_.ptr<double>(1)[1];
            lock.unlock();

            cv::Mat targetInEye = (cv::Mat_<double>(4,1) << targetPoint.x, targetPoint.y, targetPoint.z, 1.0);
            cv::Mat targetInHand = T_eye2hand * targetInEye;

            pose.center[0] = targetInHand.ptr<double>(0)[0];
            pose.center[1] = targetInHand.ptr<double>(1)[0];
            pose.center[2] = targetInHand.ptr<double>(2)[0];


            valid = (pose.center[0] >= low_xmin && pose.center[0] < low_xmax && pose.center[1] >= low_ymin && pose.center[1] < low_ymax
                    && pose.center[2] >= low_zmin && pose.center[2] < low_zmax) ||
                (pose.center[0] >= mid_xmin && pose.center[0] < mid_xmax && pose.center[1] >= mid_ymin && pose.center[1] < mid_ymax
                    && pose.center[2] >= mid_zmin && pose.center[2] < mid_zmax) ||
                (pose.center[0] >= high_xmin && pose.center[0] < high_xmax && pose.center[1] >= high_ymin && pose.center[1] < high_ymax
                    && pose.center[2] >= high_zmin && pose.center[2] < high_zmax);
        }
        return valid;
    }



    void publishTargetPose()
    {
        kinect_detect_msgs::ObjectPose object_pose_;
        for(std::vector<TargetRoughPose>::iterator it = object_fine_poses.begin();
                it != object_fine_poses.end(); ++it)
        {
            object_pose_.class_id = it -> class_id;
            object_pose_.confidence = it -> confidence;
            object_pose_.center[0] = it -> center[0];
            object_pose_.center[1] = it -> center[1];
            object_pose_.center[2] = it -> center[2];
            // object_pose_.quaternation = it -> quaternation;
            object_poses_results_.object_poses.push_back(object_pose_);
        }
        detect_publisher_.publish(object_poses_results_);

    }
};


int main()
{
    DetectionFuser fuser;
    fuser.run();
}
