#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc,char **argv)
{
    ros::init(argc,argv,"circle_my_turtle");
//    ros::NodeHandle n;
//    ros::Publisher vel_pub=n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",1000);


    ros::NodeHandle n;
    ros::Publisher key_pub=n.advertise<geometry_msgs::Twist>("keyboard_control",1);

    ros::Rate loop_rate(1);

    while(ros::ok())
    {
        geometry_msgs::Twist msg;
//        msg.linear.x=2;

//        msg.angular.z=1.8;

//        vel_pub.publish(msg);

        msg.linear.x=0.01;
        printf("linear speed x:%f\n",msg.linear.x);
        key_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;



















}
