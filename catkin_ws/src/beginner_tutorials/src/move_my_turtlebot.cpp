// move_my_turtlebot.cpp : 定义控制台应用程序的入口点。
//

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#define pi 3.1415926

int main(int argc, char **argv)
{
	ros::init(argc,argv,"move_my_turtlebot");
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

	int linear_ticks,angular_ticks;
	linear_ticks = angular_ticks = 0;
	linear_ticks =int(linear_duration*rate);
	angular_ticks =int(angular_duration*rate);

	geometry_msgs::Twist msg;

	while (ros::ok())
	{		
		if(linear_ticks != 0)
		{			
			msg.linear.x = linear_speed;
			vel_pub.publish(msg);
			msg.linear.x = 0;
			ros::spinOnce();
			linear_ticks--;
			loop_rate.sleep();
		}
		else if (angular_ticks != 0)
		{
			msg.angular.z = angular_speed;
			vel_pub.publish(msg);
			msg.angular.z = 0;
			ros::spinOnce();
			angular_ticks--;
			loop_rate.sleep();
		}
		else
		{	msg.linear.x = 0;
			msg.angular.z = 0;
			vel_pub.publish(msg);
			ros::spinOnce();
			loop_rate.sleep();
			ROS_INFO("%s", "Stopping the robot ...");
			break;
		}
	}	
	return 0;
}

