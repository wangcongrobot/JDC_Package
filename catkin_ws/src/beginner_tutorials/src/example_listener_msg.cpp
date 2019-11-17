#include "ros/ros.h"
#include "beginner_tutorials/Num.h"
#include "beginner_tutorials/AddTwoInts.h"

//declaration of the Example class:construct function, member and so on.
class Example{
public:
    Example();
private:
    ros::NodeHandle nh;
    ros::ServiceClient client;
    ros::Subscriber listener;
    void messageCallback(const beginner_tutorials::Num::ConstPtr& msg);

};

//implementation of construct function.
Example::Example()
{
    client=nh.serviceClient<beginner_tutorials::AddTwoInts>("add_3_ints");
    //monitor a topic named message,this -> current object,pointer
    listener=nh.subscribe("message",1000,&Example::messageCallback,this);

}

//implementation of one of the Example class memeber.
void Example::messageCallback( const beginner_tutorials::Num::ConstPtr& msg)
{
//    ROS_INFO("I heard:[%d] [%d] [%d]",msg->A,msg->B,msg->C);
    beginner_tutorials::AddTwoInts srv;
    srv.request.A=msg->A;
    srv.request.B=msg->B;
    srv.request.C=msg->C;
    if(ros::service::call("add_3_ints",srv))
        ROS_INFO("SUM: %ld",(long int)srv.response.sum);
    else
        ROS_ERROR("Failed to call service add_three_ints");
    /*
    if(client.call(srv))
    {
        ROS_INFO("SUM: %ld",(long int)srv.response.sum);
    }
    else
    {
        ROS_ERROR("Failed to call service add_three_ints");

    }
    */
}



int main(int argc, char **argv)
{
  ros::init(argc, argv, "example_listener_msg");
  Example exp;
  ros::spin();
  return 0;
}
