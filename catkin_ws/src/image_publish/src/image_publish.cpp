#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


const std::string VIDEO_FILE = "/home/robot/Dataset/JDChallenge/Objects.mp4";


int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher rgb_img_pub = it.advertise("/kinect2/image_color", 1);
    ros::Rate loop_rate(10);

    cv::VideoCapture capture(VIDEO_FILE);
    cv::Mat color_image;

    while( capture.isOpened() && ros::ok())
    {
        
        capture >> color_image;
        if(color_image.empty())
            break;
        sensor_msgs::ImagePtr color_img_msg =
            cv_bridge::CvImage(std_msgs::Header(), "bgr8", color_image).toImageMsg();
        rgb_img_pub.publish(color_img_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
