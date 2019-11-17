// move_my_turtlebot2.cpp
//

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#define pi 3.1415926

int main(int argc, char **argv)
{
	ros::init(argc,argv,"move_my_turtlebot2");
	ros::NodeHandle n;
	ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/safety_controller",1);

	unsigned char rate;
	rate = 50;
	ros::Rate loop_rate(rate);
	float linear_speed, goal_distance, linear_duration, angular_speed, goal_angle, angular_duration;
	
	linear_speed = 0.2;
	goal_distance = 1.0;
	linear_duration = goal_distance / linear_speed;

	angular_speed = 1.0;
	goal_angle = pi;
	angular_duration = goal_angle / angular_speed;

	int ticks;
	

	geometry_msgs::Twist msg;

	while (ros::ok())
	{		
		for(char re=0;re<2;re++)
		{
			msg.linear.x = linear_speed;
			int ticks=int(linear_duration*rate);
			for(int i=0;i<ticks;i++)
			{
				vel_pub.publish(msg);
				loop_rate.sleep();	
			}

			msg.linear.x = 0;
			vel_pub.publish(msg);
			ros::Duration(1).sleep();

			msg.angular.z = angular_speed;
			ticks=int(angular_duration*rate);
			for(int i=0;i<ticks;i++)
			{
				vel_pub.publish(msg);
				loop_rate.sleep();	
			}

			msg.angular.z = 0;
			vel_pub.publish(msg);
			ros::Duration(1).sleep();

		}
		
		msg.linear.x = 0;
		msg.angular.z = 0;
		vel_pub.publish(msg);
		ROS_INFO("%s", "Stopping the robot ...");
		break;
		
	}	
	return 0;
}

