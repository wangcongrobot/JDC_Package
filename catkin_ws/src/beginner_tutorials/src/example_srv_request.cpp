#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"

bool add(beginner_tutorials::AddTwoInts::Request &req,
         beginner_tutorials::AddTwoInts::Response &res)
{
    res.sum=req.A+req.B+req.C;
    ROS_INFO("request: A=%ld,B=%ld,C=%ld",(int)req.A,(int)req.B,(int)req.C);
    ROS_INFO("sending back response:[%ld]",(int)res.sum);

    return true;
}


int main(int argc,char **argv)
{
   ros::init(argc,argv,"add_3_ints_server");
   ros::NodeHandle n;
   //init service:
   //Name: add_3_ints,advertise the service. add: call back function
   ros::ServiceServer service=n.advertiseService("add_3_ints",add);
   ROS_INFO("Ready to add 3 ints.");
   ros::spin();

   return 0;
}
