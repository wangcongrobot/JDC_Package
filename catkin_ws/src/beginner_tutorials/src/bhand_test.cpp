#include <ros/ros.h>
#include "bhand_controller/Service.h"
#include "bhand_controller/Actions.h"
#include "bhand_controller/SetControlMode.h"
#include "sensor_msgs/JointState.h"
#include "bhand_controller/State.h"
#include "ros/callback_queue.h"
#include "string"
#include "iostream"
#include "cmath"
#include "ros/subscribe_options.h"

using namespace std;

//Usage:
//bhand_action_test(int act),act: set the target action
//bhand_action_test.bhand_action_run(int delay),delay:perform the action then delay (delay) secs.
//example:
//    //close half hand
//    bhand_action_test act_close_half(bhand_controller::Service::CLOSE_HALF_GRASP);
//    act_close_half.bhand_action_run(6);//perform the close action then delay 6 sec.
//Author: SIA HeKai

class bhand_action_test
{
public:
    bhand_action_test(int act){
    client=nh.serviceClient<bhand_controller::Actions>("bhand_node/actions");
    test_act.request.action=act;
    switch (act) {
        case 1:ROS_INFO("Call INIT_HAND service!");break;
        case 2:ROS_INFO("Call CLOSE_GRASP service!");break;
        case 3:ROS_INFO("Call OPEN_GRASP service!");break;
        case 4:ROS_INFO("Call SET_GRASP_1 service!");break;
        case 5:ROS_INFO("Call SET_GRASP_2 service!");break;
        case 6:ROS_INFO("Call CLOSE_HALF_GRASP service!");break;
        default:ROS_INFO("Warnnig:Please Call correct service!");break;
        }
    }
    void bhand_action_run(int delay)
    {
        if(client.call(test_act))
            ROS_INFO("Call service successfully!");
        else
            ROS_INFO("Failed to call service!");
        ros::Duration(delay).sleep();
    }
private:
    ros::NodeHandle nh;
    ros::ServiceClient client;
    bhand_controller::Actions test_act;
};



class bhand_control_mode
{
public:

    bhand_control_mode(string mode){
    client=nh.serviceClient<bhand_controller::SetControlMode>("bhand_node/set_control_mode");
    control_mode.request.mode=mode;
    if(client.call(control_mode))
        ROS_INFO("Set control mode successfully!");
    else
        ROS_INFO("Failed to set control mode!");

    }

private:
    ros::NodeHandle nh;
    ros::ServiceClient client;
    bhand_controller::SetControlMode control_mode;
};

//monitor position
//sensor_msgs::JointState msg_state;
float delta_base,delta_f1,delta_f2,delta_f3;
float base_pose,f1_pose,f2_pose,f3_pose;
volatile unsigned char command_flag=0;

//boost::function fun=boost::bind(&,this);
class bhand_pose
{
public:
    boost::function<void (const sensor_msgs::JointState::ConstPtr&)> cmdCallbackFun;//C++ Template
    bhand_pose()
    {
        command_flag=0;
        command_pub=bhand_command.advertise<sensor_msgs::JointState>("/bhand_node/command",1000);
        cmdCallbackFun=boost::bind(&bhand_pose::command_callback,this,_1);

        ops=ros::SubscribeOptions::create<sensor_msgs::JointState>(
                    "/joint_states",
                    1,
                    cmdCallbackFun/*command_callback*/,
                    ros::VoidPtr(),
                    &command_callback_queue
                    );
        listen_position=bhand_command.subscribe(ops);//monitor hand pose
        command_spinner=new ros::AsyncSpinner(1,&command_callback_queue);
    }

    void bhand_move(float base,float f1,float f2,float f3,int delay)
    {
        msg_state.name={"bh_j11_joint","bh_j32_joint","bh_j12_joint","bh_j22_joint"};
        //4 Freedom: j11-Base spread,j32-F3,j12-F1,j22-F2
        msg_state.position={base,f3,f1,f2};
        ROS_INFO("Position desired-Base: %f,F1: %f,F2: %f,F3: %f",msg_state.position[0],msg_state.position[2],msg_state.position[3],msg_state.position[1]);

        msg_state.velocity={0.1,0.1,0.1,0.1};
        msg_state.effort={0,0,0,0};
        //monitor state: READY && POSITIONS
        ros::Duration(delay).sleep();
        command_pub.publish(msg_state);
    }

    void bhand_spinner(char set)
    {
        if (set==1)
            command_spinner->start();
        else
            command_spinner->stop();
    }

private:
    ros::NodeHandle bhand_command;
    ros::Publisher command_pub;
    sensor_msgs::JointState msg_state;
    ros::SubscribeOptions ops;
    ros::Subscriber listen_position;
    ros::AsyncSpinner *command_spinner;
    ros::CallbackQueue command_callback_queue;
    void command_callback(const sensor_msgs::JointState::ConstPtr& msg);

};

void bhand_pose::command_callback(const sensor_msgs::JointState::ConstPtr& msg)
{

    ROS_INFO("Position  readed-Base: %f,F1: %f,F2: %f,F3: %f",msg->position[6],msg->position[1],msg->position[2],msg->position[3]);
    delta_base=base_pose-msg->position[6];
    delta_f1  =f1_pose-msg->position[1];
    delta_f2  =f2_pose-msg->position[2];
    delta_f3  =f3_pose-msg->position[3];
    ROS_INFO("Position   delta-Base: %f,F1: %f,F2: %f,F3: %f",delta_base,delta_f1,delta_f2,delta_f3);
    //4 Freedom: j11-Base spread,j32-F3,j12-F1,j22-F2
    //other process
    if(fabs(delta_base)<=0.02 && fabs(delta_f1)<=0.02 && fabs(delta_f2)<=0.02 && fabs(delta_f3)<=0.02)
        command_flag=1;
}


//state monitor process
volatile unsigned char init_state_flag=0;
ros::CallbackQueue state_callback_queue;
void state_callback(const bhand_controller::State::ConstPtr& msg)
{

    ROS_INFO("Hand state: %s",msg->state_description.c_str());
    //set hand state: INIT_STATE->READY_STATE
    if(msg->state==100)
    {
        //Init barrett hand
        bhand_action_test act_init(bhand_controller::Service::INIT_HAND);
        act_init.bhand_action_run(4);//Perform the init action then delay 4 sec.
    }

    //set control mode: POSITION
    if(msg->control_mode == "VELOCITY")
    {
        //set control mode
        bhand_control_mode control_mode("POSITION");
    }
    else
        ROS_INFO("Control mode: %s",msg->control_mode.c_str());
    init_state_flag=1;
}


//Usage:set barett hand in any position
//Input:pose data of each freedom are base,finger 1,finger 2,finger 3,pose number stamp.
//example:
//bhand_PoseSets bhandpose1(0,1.6,1.55,1.65,1);
class bhand_PoseSets{

public:
    bhand_PoseSets(float base,float f1,float f2,float f3,int no);
private:
    bhand_pose bhand_pose1;
};

bhand_PoseSets::bhand_PoseSets(float base,float f1,float f2,float f3,int no)
{
    base_pose=base;f1_pose=f1;f2_pose=f2;f3_pose=f3;
    bhand_pose1.bhand_move(base_pose,f1_pose,f2_pose,f3_pose,2);
    while(ros::ok())
    {
        bhand_pose1.bhand_spinner(1);
        if(command_flag==1)
        {
            bhand_pose1.bhand_spinner(0);
            ROS_INFO("No.%d Bhand pose achieved!",no);
            break;
        }
    }
}


int main(int argc,char **argv)
{
    ros::init(argc,argv,"example_srv_bhand");

    //monitor the state of the hand.
    ros::NodeHandle bhand_state;

    ros::SubscribeOptions ops=ros::SubscribeOptions::create<bhand_controller::State>(
                "/bhand_node/state",
                1,
                state_callback,
                ros::VoidPtr(),
                &state_callback_queue
                );
    ros::Subscriber listen_state=bhand_state.subscribe(ops);
    //Failed to subscribe the topic when put it in while(ros::ok()).
    ros::AsyncSpinner state_spinner(1,&state_callback_queue);

    while(ros::ok())
    {
        if(init_state_flag == 1)
        {
            state_spinner.stop();
            break;
        }
        state_spinner.start();

    }
    //init result: Hand state: READY_STATE; Control mode: POSITION;

    //set hand in any position
    //float base,float f1,float f2,float f3,int no
    bhand_PoseSets bhandpose1(0,1.6,1.55,1.65,1);
    ros::Duration(3).sleep();
    bhand_PoseSets bhandpose2(0,0,0,0,2);
    ros::Duration(3).sleep();
    bhand_PoseSets bhandpose3(0.5,1.28,1.28,1.28,3);
    ros::Duration(3).sleep();


    return 0;
}













