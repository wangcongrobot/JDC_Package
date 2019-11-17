#include <stdlib.h>
#include <mutex>
#include <thread>
#include <vector>
#include <sstream>
#include <chrono>

#include <opencv2/opencv.hpp>

#include <ros/ros.h>
#include <ros/spinner.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>

#include <geometry_msgs/PointStamped.h>

#include <cv_bridge/cv_bridge.h>

#include <image_transport/image_transport.h>
#include <image_transport/subscriber_filter.h>

#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
// #include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <kinect2_bridge/kinect2_definitions.h>

class Calibrator
{
private:
    std::mutex lock;

    const std::string topicColor, topicDepth;
    const std::string topicHand;

    bool updateImage, updateHand;
    bool detected;
    bool running;
    const size_t queueSize;


    double scale;
    double cx;
    double cy;
    double fx;
    double fy;
    

    cv::Mat color, depth;
    cv::Mat cameraMatrixColor, cameraMatrixDepth;
    cv::Mat cameraIntrinsicMatrix, cameraDistortionCoefficients;

    cv::Mat T_eye2hand;
    cv::Mat T_hand2eye;

    cv::Point3f handPoint;
    cv::Point2f imagePoint;

    std::vector<cv::Point2f> imagePoints2D;
    std::vector<cv::Point3f> handPoints3D;

    typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image,
            sensor_msgs::Image, sensor_msgs::CameraInfo,
            sensor_msgs::CameraInfo, geometry_msgs::PointStamped> ApproxmateSyncPolicy;

    ros::NodeHandle nh;
    ros::AsyncSpinner spinner;
    image_transport::ImageTransport it;
    image_transport::SubscriberFilter *subImageColor, *subImageDepth;
    message_filters::Subscriber<sensor_msgs::CameraInfo> *subCameraInfoColor,
        *subCameraInfoDepth;
    message_filters::Subscriber<geometry_msgs::PointStamped> *subHandPoint;

    message_filters::Synchronizer<ApproxmateSyncPolicy> *syncApproximate;

    // std::thread imageViewThread;

public:
    Calibrator(const std::string &topicColor, const std::string &topicDepth,
            const std::string topicHand)
        : topicColor(topicColor), topicDepth(topicDepth), topicHand(topicHand),
          updateImage(false), updateHand(false), running(false),
          detected(false), queueSize(5), nh("~"), spinner(0), it(nh)
    {
        cameraMatrixColor = cv::Mat::zeros(3, 3, CV_64F);
        cameraMatrixDepth = cv::Mat::zeros(3, 3, CV_64F);

        cameraIntrinsicMatrix = cv::Mat::zeros(3, 3, CV_64FC1);
        cameraDistortionCoefficients = cv::Mat::zeros(5, 1, CV_64FC1);
    }

    ~Calibrator()
    {
    }

    void run()
    {
        start();
        stop();
    }

private:
    void start()
    {
        running = true;
 
        // camera intrinsic matrix
        nh.param("/calib/parameters/kinect2/scale", scale, 1000.0);
        nh.param("/calib/parameters/kinect2/cx", cx, 461.185699);
        nh.param("/calib/parameters/kinect2/cy", cy, 278.003533);
        nh.param("/calib/parameters/kinect2/fx", fx, 505.565471);
        nh.param("/calib/parameters/kinect2/fy", fy, 506.534290);

        std::string topicCameraInfoColor = topicColor.substr(0,
                topicColor.rfind('/')) + "/camera_info";
        std::string topicCameraInfoDepth = topicDepth.substr(0,
                topicDepth.rfind('/')) + "/camera_info";

        image_transport::TransportHints hints("raw");
        subImageColor = new image_transport::SubscriberFilter(it, topicColor,
                queueSize, hints);
        subImageDepth = new image_transport::SubscriberFilter(it, topicDepth,
                queueSize, hints);
        subCameraInfoColor = new message_filters::Subscriber<
            sensor_msgs::CameraInfo>(nh, topicCameraInfoColor, queueSize);
        subCameraInfoDepth = new message_filters::Subscriber<
            sensor_msgs::CameraInfo>(nh, topicCameraInfoDepth, queueSize);

        subHandPoint = new message_filters::Subscriber<
            geometry_msgs::PointStamped>(nh, topicHand, queueSize);


        syncApproximate = new message_filters::Synchronizer<ApproxmateSyncPolicy>(
                ApproxmateSyncPolicy(queueSize), *subImageColor, *subImageDepth,
                *subCameraInfoColor, *subCameraInfoColor, *subHandPoint);
        syncApproximate->registerCallback(boost::bind(&Calibrator::callback,
                    this, _1, _2, _3, _4, _5));

        spinner.start();

        std::chrono::milliseconds duration(1);
        while(!updateImage || !updateHand)
        {
            if(!ros::ok())
            {
                return;
            }
            std::this_thread::sleep_for(duration);
        }

        imageViewer();

    }


    void stop()
    {
        spinner.stop();

        delete syncApproximate;

        delete subImageColor;
        delete subImageDepth;
        delete subCameraInfoColor;
        delete subCameraInfoDepth;
        delete subHandPoint;

        running = false;
    }


    void callback(const sensor_msgs::Image::ConstPtr imageColor,
            const sensor_msgs::Image::ConstPtr imageDepth,
            const sensor_msgs::CameraInfo::ConstPtr cameraInfoColor,
            const sensor_msgs::CameraInfo::ConstPtr CameraInfoDepth,
            const geometry_msgs::PointStamped::ConstPtr handPoint)
    {
        cv::Mat color, depth;
        cv::Point3f handpoint;

        // readCameraInfo(cameraInfoColor, cameraMatrixColor);
        // readCameraInfo(cameraInfoDepth, cameraMatrixDepth);
        readCameraInfo(cameraInfoColor, cameraIntrinsicMatrix,
                cameraDistortionCoefficients);
        readImage(imageColor, color);
        readImage(imageDepth, depth);

        // IR image input
        if(color.type() == CV_16U)
        {
            cv::Mat tmp;
            color.convertTo(tmp, CV_8U, 0.02);
            cv::cvtColor(tmp, color, CV_GRAY2BGR);
        }

        readHandPoint(handPoint, handpoint);

        lock.lock();
        this->color = color;
        this->depth = depth;
        this->handPoint = handpoint;
        updateImage = true;
        updateHand = true;
        lock.unlock();
    }

    void imageViewer()
    {
        // cv::Mat color, depth, depthDisp;
        std::chrono::time_point<std::chrono::high_resolution_clock> start, now;
        double fps = 0;
        size_t frameCount = 0;
        std::ostringstream oss;
        const cv::Point pos(5, 15);
        const cv::Scalar colorText = CV_RGB(255, 255, 255);
        const double sizeText = 0.5;
        const int lineText = 1;
        const int font = cv::FONT_HERSHEY_SIMPLEX;

        cv::namedWindow("Image Viewer");
        oss << "starting to calibrate...";
        
        // cvSetMouseCallback("Image Viewer", mouse_calib, 0);

        start = std::chrono::high_resolution_clock::now();
        while(running && ros::ok())
        {
            if(updateImage && updateHand)
            {
                detectImagePoint();
                updateImage = false;
                updateHand = false;

                ++frameCount;
                now = std::chrono::high_resolution_clock::now();
                double elapsed = std::chrono::duration_cast<
                    std::chrono::milliseconds>(now-start).count()/1000.0;
                if(elapsed >= 1.0)
                {
                    fps = frameCount/elapsed;
                    oss.str("");
                    oss << "fps: " << fps << " ( " << elapsed / frameCount
                        * 1000.0 << " ms)";
                    start = now;
                    frameCount = 0;
                }

                cv::putText(color, oss.str(), pos, font, sizeText, colorText,
                        lineText, CV_AA);
                cv::imshow("Image Viewer", color);
            }


            int key = cv::waitKey(1);
            switch(key & 0xFF)
            {
                case 27:
                case 'q':
                    running = false;
                    break;
                case ' ':
                case 's':
                    ROS_INFO_STREAM("'s' is pressed");
                    savePoints();
                    break;
                case 'c':
                    ROS_INFO_STREAM("'c' is pressed");
                    calibrate();
                    break;
               case 't':
                    ROS_INFO_STREAM("'t' is pressed");
                    validate();
                    break;
            }
        }
        cv::destroyAllWindows();
        cv::waitKey(100);
    }


    void mouse_calib(int event, int x, int y, int flags, void* ustc)
    {
        if (event == CV_EVENT_LBUTTONDOWN)
        {
            imagePoint = cv::Point2f(x, y);
            savePoints();
        }
        else if (event == CV_EVENT_RBUTTONDOWN)
        {
            calibrate();
        }
        else if (event == CV_EVENT_MOUSEMOVE)
        {
            cv::Point pt = cv::Point(x, y);

            char temp[16];
            sprintf(temp, "(%d, %d)", pt.x, pt.y);
            cv::putText(color, temp, pt, cv::FONT_HERSHEY_SIMPLEX, 5, cvScalar(255, 255, 255, 0));
            cv::circle(color, pt, 2, cvScalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
        }
    }

    void readImage(const sensor_msgs::Image::ConstPtr msgImage, cv::Mat &image)
        const
    {
        cv_bridge::CvImageConstPtr pCvImage;
        pCvImage = cv_bridge::toCvShare(msgImage, msgImage->encoding);
        pCvImage->image.copyTo(image);
    }

    void readCameraInfo(const sensor_msgs::CameraInfo::ConstPtr cameraInfo,
            cv::Mat &cameraIntrinsicMatrix, cv::Mat &cameraDistortionCoefficients)
        const
    {
        double *itC = cameraIntrinsicMatrix.ptr<double>(0, 0);
        for(size_t i = 0; i < 9; ++i, ++itC)
        {
            *itC = cameraInfo->K[i];
        }

        double *itD = cameraDistortionCoefficients.ptr<double>(0, 0);
        for(size_t i = 0; i < 9; ++i, ++itC)
        {
            *itD = cameraInfo->D[i];
        }
    }

    void readHandPoint(const geometry_msgs::PointStamped::ConstPtr handPoint,
            cv::Point3f &handpoint) const
    {
        handpoint.x = handPoint->point.x;
        handpoint.y = handPoint->point.y;
        handpoint.z = handPoint->point.z;
    }

    void detectImagePoint()
    {
       size_t circle_number = 0;

       cv::Mat image_tmp = color.clone();
       cv::Mat edge;
       cv::cvtColor(image_tmp, image_tmp, CV_RGB2GRAY);
       cv::GaussianBlur(image_tmp, image_tmp, cv::Size(9,9), 2, 2);
       cv::Canny(image_tmp, edge, 10, 200, 3, false);

       std::vector<cv::Vec3f> circle0;
       cv::HoughCircles(image_tmp, circle0, CV_HOUGH_GRADIENT, 1, 10000, 200,
               20, 20, 30);


       if(circle0.size() == 0)
           return;

       detected = true;

       // for(size_t i = 0; i < circle0.size(); i++)
       // {
       //     cv::Point2f center(circle0[i][0], circle0[i][1]);
       //     double radius = circle0[i][2];
       //     cv::circle(color, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
       //     cv::circle(color, center, radius, cv::Scalar(255, 0, 0), 1.5, 8, 0);
       //     avg_u += circle0[i][0];
       //     avg_v += circle0[i][1];
       //     circle_number += 1;
       // }
       

       // imagePoint = cv::Point2f(avg_u/circle_number, avg_v/circle_number);
       
       cv::Point2f center(circle0[0][0], circle0[0][1]);
       double radius = circle0[0][2];
       cv::circle(color, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
       cv::circle(color, center, radius, cv::Scalar(255, 0, 0), 1.5, 8, 0);
       
       imagePoint = cv::Point2f(circle0[0][0], circle0[0][1]);

    }

    void savePoints()
    {
        std::cout << "cy: " << cy << std::endl;
        ROS_INFO_STREAM("save method");
        if(detected)
        {
            handPoints3D.push_back(handPoint);
            imagePoints2D.push_back(imagePoint);
            ROS_INFO_STREAM("new circles are detected!");
            detected = false;
        }

        else
        {
            ROS_INFO_STREAM("No new circles are detected!");
        }
    }

    void calibrate()
    {
        ROS_INFO_STREAM("calibrate method");
        if(handPoints3D.size() < 4)
        {
            std::cout << "too few points to calibrate" << std::endl;
            return;
        }

        cv::Mat rvec, tvec;
        solvePnP(handPoints3D, imagePoints2D, cameraIntrinsicMatrix,
                cameraDistortionCoefficients, rvec, tvec, false, CV_EPNP);

        cv::Mat rotationMat;

        cv::Rodrigues(rvec, rotationMat);

        T_hand2eye = cv::Mat::zeros(4, 4, CV_64F);

        T_hand2eye.ptr<double>(0)[0] = rotationMat.ptr<double>(0)[0];
        T_hand2eye.ptr<double>(0)[1] = rotationMat.ptr<double>(0)[1];
        T_hand2eye.ptr<double>(0)[2] = rotationMat.ptr<double>(0)[2];
        T_hand2eye.ptr<double>(1)[0] = rotationMat.ptr<double>(1)[0];
        T_hand2eye.ptr<double>(1)[1] = rotationMat.ptr<double>(1)[1];
        T_hand2eye.ptr<double>(1)[2] = rotationMat.ptr<double>(1)[2];
        T_hand2eye.ptr<double>(2)[0] = rotationMat.ptr<double>(2)[0];
        T_hand2eye.ptr<double>(2)[1] = rotationMat.ptr<double>(2)[1];
        T_hand2eye.ptr<double>(2)[2] = rotationMat.ptr<double>(2)[2];

        T_hand2eye.ptr<double>(0)[3] = tvec.ptr<double>(0)[0];
        T_hand2eye.ptr<double>(1)[3] = tvec.ptr<double>(1)[0];
        T_hand2eye.ptr<double>(2)[3] = tvec.ptr<double>(2)[0];
        T_hand2eye.ptr<double>(3)[3] = 1.0;

        T_eye2hand = T_hand2eye.inv();

        std::cout << "T_hand2eye: " << std::endl << T_hand2eye << std::endl;
        std::cout << "T_eye2hand: " << std::endl << T_eye2hand << std::endl;
        std::cout << "E: " << std::endl << T_hand2eye * T_eye2hand << std::endl;

        cv::FileStorage fs1("/home/robot/catkin_ws/src/darknet_ros/darknet_ros/calib/external-calib-results.yaml", cv::FileStorage::WRITE);
        fs1 << "T_hand2eye" << T_hand2eye;
        fs1 << "T_eye2hand" << T_eye2hand;
        fs1.release();
        
        std::cout << "calibration results are saved." << std::endl;
    }

    void validate()
    {
        std::cout << "hand point: " << handPoint.x << ", " << handPoint.y << ", " << handPoint.z << std::endl;
        std::cout << "image point: " << imagePoint.x << ", " << imagePoint.y << std::endl;  
        cv::Mat homoHandPoint = cv::Mat(4, 1, CV_64F);
        
        homoHandPoint.ptr<double>(0)[0] = handPoint.x;
        homoHandPoint.ptr<double>(1)[0] = handPoint.y;
        homoHandPoint.ptr<double>(2)[0] = handPoint.z;
        homoHandPoint.ptr<double>(3)[0] = 1.0;
     
        cv::Mat homoHandPoint_in_eye = T_hand2eye * homoHandPoint;
        
        double depth = homoHandPoint_in_eye.ptr<double>(2)[0];
        int z = depth * scale;
        int u = homoHandPoint_in_eye.ptr<double>(0)[0] * fx / depth + cx;
        int v = homoHandPoint_in_eye.ptr<double>(1)[0] * fy / depth + cy;
        std::cout << "hand point in eye: " << u << ", " << v << std::endl;
        
        std::cout << "camera intrinsic: " << cameraIntrinsicMatrix << std::endl;
        std::cout << "cx: " << cx << std::endl;
        std::cout << "cy: " << cy << std::endl;
        std::cout << "fx: " << fx << std::endl;
        std::cout << "fy: " << fy << std::endl;
    
    
    }
};


int main(int argc, char **argv)
{
    ros::init(argc, argv, "eye2hand_calib",
            ros::init_options::AnonymousName);

    if(!ros::ok())
    {
        return 0;
    }

    std::string ns = K2_DEFAULT_NS;
    std::string topicColor = K2_TOPIC_QHD K2_TOPIC_IMAGE_COLOR K2_TOPIC_IMAGE_RECT;
    std::string topicDepth = K2_TOPIC_QHD K2_TOPIC_IMAGE_DEPTH K2_TOPIC_IMAGE_RECT;

    // need to improve
    std::string topicHand = argv[1];

    topicColor = "/" + ns + topicColor;
    topicDepth = "/" + ns + topicDepth;
    OUT_INFO("topic color: " FG_CYAN << topicColor << NO_COLOR);
    OUT_INFO("topic depth: " FG_CYAN << topicDepth << NO_COLOR);

    Calibrator calibrator(topicColor, topicDepth, topicHand);

    OUT_INFO("starting eye-to-hand calibrate...");
    calibrator.run();

    ros::shutdown();
    return 0;
}
