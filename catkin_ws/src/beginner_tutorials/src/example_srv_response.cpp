#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"
#include <cstdlib>

//argc,related to the number of variable of the main()
//argv[0]:the name of the current file
//argv[1]:variable when build
//...
//argv[argc]:null
int main(int argc,char **argv)
{
    ros::init(argc,argv,"add_3_ints_client");
    if(argc != 4)
    {
        ROS_INFO("usage: add_3_ints_client A B C");
        return 1;
    }
    ros::NodeHandle n;
    ros::ServiceClient client=n.serviceClient<beginner_tutorials::AddTwoInts>("add_3_ints");

    beginner_tutorials::AddTwoInts srv;

    //atoll:convert a string to long long int variable
    srv.request.A=atoll(argv[1]);
    srv.request.B=atoll(argv[2]);
    srv.request.C=atoll(argv[3]);


    if(client.call(srv))
    {
        ROS_INFO("Sum:%ld",(long int)srv.response.sum);
    }
    else
    {
        ROS_ERROR("Failed to call service add_three_ints");
        return 1;

    }
    return 0;
}
