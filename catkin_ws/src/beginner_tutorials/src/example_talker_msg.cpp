#include "ros/ros.h"
#include "beginner_tutorials/Num.h"
#include <sstream>
//Usage:publish a msg with topic named message


int main(int argc, char **argv)
{
  ros::init(argc, argv, "example_talker_msg");
  ros::NodeHandle n;
  //advertise a topic named "message"
  ros::Publisher pub=n.advertise<beginner_tutorials::Num>("message",1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    beginner_tutorials::Num msg;
    msg.A=1;
    msg.B=2;
    msg.C=3;
    pub.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
