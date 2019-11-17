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
#include "beginner_tutorials/ForceData.h"
#include "geometry_msgs/Twist.h"//use for move bhand by keyboard
#include "id_data_msgs/ID_Data.h"//using for notie event
/*****************************************************************************************
 *debug note:
 * well suitable to the keyboard_control.cpp of 2016,11,18 17:00.
 *
 *date:.
 * ***************************************************************************************/
using namespace std;

//pre-define
#define f1_sensor_id 0X0758//1880
#define f2_sensor_id 0x0708//1800
#define f3_sensor_id 0x06e0//1760

//globals
float key_control_value=0;
bool close_hand_flag=false;
bool open_hand_flag=false;

struct sensor_flag
{
    char row0_flag,row1_flag,row2_flag,row3_flag,row4_flag,row5_flag,row6_flag,row7_flag;
};
sensor_flag sensor1_flag={0},sensor2_flag={0},sensor3_flag={0};

int f1_heavy_force_point_num,f2_heavy_force_point_num,f3_heavy_force_point_num;
int force_threshold=90;
//when catch the joy, the threshold is 80.
//when catch some hard object, it is better set the threshold as 90,or 100.
int num_count=0;


//function declaration
void Sensor_ForceHeavyPoint_Count(beginner_tutorials::ForceData force_msg,int sensor_id,int *f_heavy_force_point_num,sensor_flag *sensorflag);
void notice_data_clear(id_data_msgs::ID_Data *test);

//
class bhand_state_init
{
public:
    boost::function<void (const bhand_controller::State::ConstPtr&)> StateCallbackFun;
    bhand_state_init(string mode);
    void bhand_control_mode(string mode);
    void bhand_action_test(int act,int delay);
    void bhand_spinner(char set);

private:
    ros::NodeHandle bhand_state;
    ros::SubscribeOptions ops;
    ros::Subscriber listen_state;
    ros::AsyncSpinner *state_spinner;
    ros::CallbackQueue state_callback_queue;
    void state_callback(const bhand_controller::State::ConstPtr& msg);

    ros::ServiceClient client;
    bhand_controller::SetControlMode control_mode;

    bhand_controller::Actions test_act;
    string set_mode;
public:
    __uint8_t flag;
    char first_init_state;

};

bhand_state_init::bhand_state_init(string mode)
{
    StateCallbackFun=boost::bind(&bhand_state_init::state_callback,this,_1);
    ops=ros::SubscribeOptions::create<bhand_controller::State>(
                "/bhand_node/state",
                1,
                StateCallbackFun,
                ros::VoidPtr(),
                &state_callback_queue
                );
    listen_state=bhand_state.subscribe(ops);
    state_spinner=new ros::AsyncSpinner(1,&state_callback_queue);
    flag=0;
    set_mode=mode;
    first_init_state=1;
}

void bhand_state_init::state_callback(const bhand_controller::State::ConstPtr& msg)
{

    //ROS_INFO("Callback Hand state: %s",msg->state_description.c_str());
    //ROS_INFO("Callback Control mode: %s",msg->control_mode.c_str());
    //set hand state: INIT_STATE->READY_STATE
    //INIT_STATE = 100
    //STANDBY_STATE = 200
    //READY_STATE = 300
    //EMERGENCY_STATE = 400
    //FAILURE_STATE = 500
    //SHUTDOWN_STATE = 600
    if(msg->state==100)
    {
        //Init barrett hand
        //Perform the init action then delay 4 sec.
        ros::Duration(1).sleep();
        if(first_init_state==1)
        {
            bhand_action_test(bhand_controller::Service::INIT_HAND,4);
            first_init_state=0;
        }

    }
    if(msg->state==300)
        first_init_state=0;
    if(msg->state==500)
    {
        ros::Duration(4).sleep();
    }
    //set control mode
    if(msg->control_mode != set_mode)
    {
        //set control mode
        bhand_control_mode(set_mode);
    }

    flag=1;
}

void bhand_state_init::bhand_control_mode(string mode)
{
    set_mode=mode;
    client=bhand_state.serviceClient<bhand_controller::SetControlMode>("bhand_node/set_control_mode");
    control_mode.request.mode=mode;
    if(client.call(control_mode))
        ROS_INFO("Set %s mode successfully!",mode.c_str());
    else
        ROS_INFO("Failed to set control mode!");

}

void bhand_state_init::bhand_action_test(int act,int delay)
{
    client=bhand_state.serviceClient<bhand_controller::Actions>("bhand_node/actions");
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
    if(client.call(test_act))
        ROS_INFO("Call service successfully!");
    else
        ROS_INFO("Failed to call service!");
    ros::Duration(delay).sleep();

}

void bhand_state_init::bhand_spinner(char set)
{
    if (set==1)
        state_spinner->start();
    else
        state_spinner->stop();
}


//monitor position
//sensor_msgs::JointState msg_state;
//volatile unsigned char command_flag=0;

class bhand_pose
{
public:
    boost::function<void (const sensor_msgs::JointState::ConstPtr&)> cmdCallbackFun;//C++ Template
    bhand_pose()
    {
        flag=0;
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

    void bhand_move_position(float base,float f1,float f2,float f3,int delay)
    {
        msg_state.name={"bh_j11_joint","bh_j32_joint","bh_j12_joint","bh_j22_joint"};
        //4 Freedom: j11-Base spread,j32-F3,j12-F1,j22-F2
        msg_state.position={base,f3,f1,f2};
        //ROS_INFO("Position desired-Base: %f,F1: %f,F2: %f,F3: %f",msg_state.position[0],msg_state.position[2],msg_state.position[3],msg_state.position[1]);

        msg_state.velocity={0.05,0.1,0.1,0.1};
        msg_state.effort={0.1,0.3,0.3,0.3};
        //monitor state: READY && POSITIONS
        ros::Duration(delay).sleep();
        command_pub.publish(msg_state);
    }

    void bhand_move_velocity(float base,float f1,float f2,float f3,int delay)
    {
        msg_state.name={"bh_j11_joint","bh_j32_joint","bh_j12_joint","bh_j22_joint"};
        //4 Freedom: j11-Base spread,j32-F3,j12-F1,j22-F2
        msg_state.position={0,0,0,0};
        //ROS_INFO("Position desired-Base: %f,F1: %f,F2: %f,F3: %f",msg_state.position[0],msg_state.position[2],msg_state.position[3],msg_state.position[1]);

        msg_state.velocity={base,f3,f1,f2};
        msg_state.effort={0.1,0.3,0.3,0.3};
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
public:
    float base_pose,f1_pose,f2_pose,f3_pose;
    float rec_base,rec_f1,rec_f2,rec_f3;
    float delta_base,delta_f1,delta_f2,delta_f3;
    __uint8_t flag;

};

void bhand_pose::command_callback(const sensor_msgs::JointState::ConstPtr& msg)
{

    //ROS_INFO("Position  readed-Base: %f,F1: %f,F2: %f,F3: %f",msg->position[6],msg->position[1],msg->position[2],msg->position[3]);
    rec_base=msg->position[6];
    if(rec_base<0)  rec_base=0;//avoid some abnormal phenomenons
    if(rec_base>3)  rec_base=2.5;
    rec_f1=msg->position[1];
    if(rec_f1<0)    rec_f1=0;
    if(rec_f1>3)    rec_f1=2.5;
    rec_f2=msg->position[2];
    if(rec_f2<0)    rec_f2=0;
    if(rec_f2>3)    rec_f2=2.5;
    rec_f3=msg->position[3];
    if(rec_f3<0)    rec_f3=0;
    if(rec_f3>3)    rec_f3=2.5;
    delta_base=base_pose-rec_base;
    delta_f1  =f1_pose-rec_f1;
    delta_f2  =f2_pose-rec_f2;
    delta_f3  =f3_pose-rec_f3;

    //ROS_INFO("Position   delta-Base: %f,F1: %f,F2: %f,F3: %f",delta_base,delta_f1,delta_f2,delta_f3);
    //4 Freedom: j11-Base spread,j32-F3,j12-F1,j22-F2
    //other process
    if(fabs(delta_base)<=0.02 && fabs(delta_f1)<=0.02 && fabs(delta_f2)<=0.02 && fabs(delta_f3)<=0.02)
        flag=1;
}


//Usage:set barett hand in any position
//Input:pose data of each freedom are base,finger 1,finger 2,finger 3,pose number stamp.
//example:
//bhand_PoseSets bhandpose1(0,1.6,1.55,1.65,1);
class bhand_PoseSets{

public:
    bhand_PoseSets();
    void Set(float base,float f1,float f2,float f3,int delay,int no);
    void Set_velocity(float base,float f1,float f2,float f3,float limit_base,float limit_f1,float limit_f2,float limit_f3);
private:
    bhand_pose bhand_pose1;
    __uint8_t flag;
};

bhand_PoseSets::bhand_PoseSets()
{
    bhand_pose1.flag=0;
}

void bhand_PoseSets::Set(float base,float f1,float f2,float f3,int delay,int no)
{
    bhand_pose1.base_pose=base;
    bhand_pose1.f1_pose=f1;
    bhand_pose1.f2_pose=f2;
    bhand_pose1.f3_pose=f3;
    bhand_pose1.bhand_move_position(base,f1,f2,f3,delay);
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        bhand_pose1.bhand_spinner(1);
        if(bhand_pose1.flag==1)
        {
            bhand_pose1.bhand_spinner(0);
            //ROS_INFO("No.%d Bhand pose achieved!",no);
            break;
        }
        loop_rate.sleep();
    }
    bhand_pose1.flag=0;
}
void bhand_PoseSets::Set_velocity(float base, float f1, float f2, float f3, float limit_base, float limit_f1, float limit_f2, float limit_f3)
{
    bhand_pose1.base_pose=limit_base;
    bhand_pose1.f1_pose=limit_f1;
    bhand_pose1.f2_pose=limit_f2;
    bhand_pose1.f3_pose=limit_f3;
    ros::Rate loop_rate(10);
    if(bhand_pose1.rec_base<0)  bhand_pose1.rec_base=0;//avoid some abnormal phenomenons
    if(bhand_pose1.rec_base>3)  bhand_pose1.rec_base=limit_base;
    if(bhand_pose1.rec_f1<0)    bhand_pose1.rec_f1=0;
    if(bhand_pose1.rec_f1>3)    bhand_pose1.rec_f1=limit_f1;
    if(bhand_pose1.rec_f2<0)    bhand_pose1.rec_f2=0;
    if(bhand_pose1.rec_f2>3)    bhand_pose1.rec_f2=limit_f2;
    if(bhand_pose1.rec_f3<0)    bhand_pose1.rec_f3=0;
    if(bhand_pose1.rec_f3>3)    bhand_pose1.rec_f3=limit_f3;
    while(ros::ok())
    {
        ROS_INFO("base %f,f1 %f,f2 %f,f3 %f",bhand_pose1.rec_base,bhand_pose1.rec_f1,bhand_pose1.rec_f2,bhand_pose1.rec_f3);
        if((bhand_pose1.rec_base>=0 && bhand_pose1.rec_base<=limit_base) && (bhand_pose1.rec_f1>=0 && bhand_pose1.rec_f1<=limit_f1)&& (bhand_pose1.rec_f2>=0 && bhand_pose1.rec_f2<=limit_f2)&& (bhand_pose1.rec_f3>=0 && bhand_pose1.rec_f3<=limit_f3))
        {
            bhand_pose1.bhand_move_velocity(base,f1,f2,f3,0);
        }
        else
        {
            break;
        }
        bhand_pose1.bhand_spinner(1);
        loop_rate.sleep();
    }


}

class tactile_listener
{
public:
    boost::function<void (const beginner_tutorials::ForceData::ConstPtr&)> tactile_msgCallbackFun;
    tactile_listener();
    void tactile_sub_spinner(char set);

private:
    ros::NodeHandle tactile_handle;
    ros::Subscriber tactile_subscriber;
    ros::SubscribeOptions tactile_ops;
    ros::AsyncSpinner *tactile_spinner;
    ros::CallbackQueue tactile_callbackqueue;
    void tactile_msgCallback(const beginner_tutorials::ForceData::ConstPtr &tactile_msg);
};

tactile_listener::tactile_listener()
{
    tactile_msgCallbackFun=boost::bind(&tactile_listener::tactile_msgCallback,this,_1);
    tactile_ops=ros::SubscribeOptions::create<beginner_tutorials::ForceData>(
                "/ArrayForcePUB",
                1,
                tactile_msgCallbackFun,
                ros::VoidPtr(),
                &tactile_callbackqueue
                );
    tactile_subscriber=tactile_handle.subscribe(tactile_ops);
    tactile_spinner=new ros::AsyncSpinner(1,&tactile_callbackqueue);
}

void tactile_listener::tactile_sub_spinner(char set)
{
    if (set==1)
        tactile_spinner->start();
    if (set==0)
        tactile_spinner->stop();

}

void tactile_listener::tactile_msgCallback(const beginner_tutorials::ForceData::ConstPtr &tactile_msg)
{
//    printf("Tactile Sensor,ID: %u,Data: ",tactile_msg->id);
//    for(char i=0;i<8;i++)
//    {
//        printf("%u ",tactile_msg->data[i]);
//        if(i==7) printf("\n");
//    }
    beginner_tutorials::ForceData force_msg;
    force_msg.id=tactile_msg->id;
    force_msg.data=tactile_msg->data;
    Sensor_ForceHeavyPoint_Count(force_msg,f1_sensor_id,&f1_heavy_force_point_num,&sensor1_flag);
    Sensor_ForceHeavyPoint_Count(force_msg,f2_sensor_id,&f2_heavy_force_point_num,&sensor2_flag);
    Sensor_ForceHeavyPoint_Count(force_msg,f3_sensor_id,&f3_heavy_force_point_num,&sensor3_flag);
}


class keyboard_monitor
{
public:
    boost::function<void (const geometry_msgs::Twist::ConstPtr&)> keyboard_monitor_CallbackFun;
    keyboard_monitor();
    void keyboard_monitor_spinner(char set);
private:
    ros::NodeHandle keyboard_handle;
    ros::Subscriber keyboard_subscriber;
    ros::SubscribeOptions keyboard_ops;
    ros::AsyncSpinner *keyboard_spinner;
    ros::CallbackQueue keyboard_callbackQueue;
    void keyboard_monitor_callback(const geometry_msgs::Twist::ConstPtr &key_control_msg);
};

keyboard_monitor::keyboard_monitor()
{
   keyboard_monitor_CallbackFun=boost::bind(&keyboard_monitor::keyboard_monitor_callback,this,_1);
   keyboard_ops=ros::SubscribeOptions::create<geometry_msgs::Twist>(
               "/keyboard_control",
               1,
               keyboard_monitor_CallbackFun,
               ros::VoidPtr(),
               &keyboard_callbackQueue
               );
   keyboard_subscriber=keyboard_handle.subscribe(keyboard_ops);
   keyboard_spinner=new ros::AsyncSpinner(1,&keyboard_callbackQueue);

}

void keyboard_monitor::keyboard_monitor_spinner(char set)
{
    if(set==1)
        keyboard_spinner->start();
    if(set==0)
        keyboard_spinner->stop();

}

void keyboard_monitor::keyboard_monitor_callback(const geometry_msgs::Twist::ConstPtr &key_control_msg)
{
//    ROS_INFO("Keyboard control speed:%f",key_control_msg->linear.x);
    key_control_value=key_control_msg->linear.x;
}


class notice_pub_sub
{
public:
    boost::function<void (const id_data_msgs::ID_Data::ConstPtr&)> notice_pub_sub_msgCallbackFun;

    notice_pub_sub();
    void notice_pub_sub_listener();
    void notice_pub_sub_pulisher(id_data_msgs::ID_Data id_data);
    void notice_display(id_data_msgs::ID_Data notice_msg,bool set);
    void notice_sub_spinner(char set);

private:
    ros::NodeHandle notice_handle;
    ros::Subscriber notice_subscriber;
    ros::Publisher notice_publisher;
    ros::SubscribeOptions notice_ops;
    ros::AsyncSpinner *notice_spinner;
    ros::CallbackQueue notice_callbackqueue;
    void notice_msgCallback(const id_data_msgs::ID_Data::ConstPtr &notice_msg);
};

notice_pub_sub::notice_pub_sub()
{
    notice_pub_sub_msgCallbackFun=boost::bind(&notice_pub_sub::notice_msgCallback,this,_1);
    notice_ops=ros::SubscribeOptions::create<id_data_msgs::ID_Data>(
                "/notice",
                1,
                notice_pub_sub_msgCallbackFun,
                ros::VoidPtr(),
                &notice_callbackqueue
                );
    notice_subscriber=notice_handle.subscribe(notice_ops);
    notice_spinner=new ros::AsyncSpinner(1,&notice_callbackqueue);

    notice_publisher=notice_handle.advertise<id_data_msgs::ID_Data>("/notice",1);
}

void notice_pub_sub::notice_pub_sub_listener()
{

}

void notice_pub_sub::notice_pub_sub_pulisher(id_data_msgs::ID_Data id_data)
{
    notice_publisher.publish(id_data);
}

void notice_pub_sub::notice_display(id_data_msgs::ID_Data notice_msg,bool set)
{

    if(set)
    {
        printf("REC Notice message,ID: %d,Data: ",notice_msg.id);
        for(char i=0;i<8;i++)
        {
            printf("%d ",notice_msg.data[i]);
            if(i==7) printf("\n");
        }

    }

}
void notice_pub_sub::notice_msgCallback(const id_data_msgs::ID_Data::ConstPtr &notice_msg)
{

    id_data_msgs::ID_Data notice_message;
    notice_message.id=0;
    for(char i=0;i<8;i++)notice_message.data[i]=0;

    notice_message.id=notice_msg->id;
    for(char i=0;i<8;i++)notice_message.data[i]=notice_msg->data[i];

    notice_pub_sub::notice_display(notice_message,false);

    if(notice_message.id==1 && notice_message.data[0]==1)//close flag
    {
        close_hand_flag=true;
        notice_data_clear(&notice_message);
        notice_message.id=1;
        notice_message.data[0]=14;
        notice_publisher.publish(notice_message);
    }
    if(notice_message.id==1 && notice_message.data[0]==0)//open flag
    {
        open_hand_flag=true;
        notice_data_clear(&notice_message);
        notice_message.id=1;
        notice_message.data[0]=14;
        notice_publisher.publish(notice_message);
    }

}

void notice_pub_sub::notice_sub_spinner(char set)
{
    if(set==1)
        notice_spinner->start();
    if(set==0)
        notice_spinner->stop();
}


int main(int argc,char **argv)
{
    ros::init(argc,argv,"bhand_force_control");
    ros::NodeHandle test_handle;//useless
    bhand_state_init state_test("POSITION");
    int loop_hz=100;
    ros::Rate loop_rate(loop_hz);
    while(ros::ok())
    {
        if (state_test.flag)
        {
            state_test.bhand_spinner(0);
            break;
        }
        else
            state_test.bhand_spinner(1);
        loop_rate.sleep();
    }
    //velocity control
    state_test.bhand_control_mode("VELOCITY");

    //soft contact control
    //strategy:
    //step delta,then monitor the tactile sensor, and if its' value do not get the threshold,
    //then continue moving delta.
    bhand_pose bhandpose1;
    float v_base=0.001,v_f1=0,v_f2=0,v_f3=0,rec_v_base,rec_v_f1,rec_v_f2,rec_v_f3;
    float delta_v_base,delta_v_f1,delta_v_f2,delta_v_f3;
    tactile_listener tactile_test;
    keyboard_monitor keyboard_control;
    ros::Rate speed_loop_rate(loop_hz);
    float limit_speed=0.4;

    bhand_PoseSets bhand_pose_pre_catch;
    bhand_pose_pre_catch.Set_velocity(0,0.4,0.4,0.4,0,0.5,0.5,0.5);
    printf("Pre-catch pose have achieved!\n");

    notice_pub_sub notice_test;
    id_data_msgs::ID_Data notice_data_pub;
    bool f1_close_flag=false,f2_close_flag=false,f3_close_flag=false;
    while(ros::ok())
    {
        //monitor tactile sensor topic
        //while base<=2, f1<=2,...
        //bhandpose1.Set(base+0.1,f1+0.1,f2+0.1,f3+0.1,count+1);
        v_base=-v_base;
        v_f1+=key_control_value;
        v_f2+=key_control_value;
        v_f3+=key_control_value;
        if(v_f1<=-1.0) v_f1=-limit_speed;
        if(v_f1>= 1.0) v_f1= limit_speed;
        if(v_f2<=-1.0) v_f2=-limit_speed;
        if(v_f2>= 1.0) v_f2= limit_speed;
        if(v_f3<=-1.0) v_f3=-limit_speed;
        if(v_f3>= 1.0) v_f3= limit_speed;

        //ROS_INFO("Joint Speed:base %f,f1 %f,f2 %f,f3 %f.\n",v_base,v_f1,v_f2,v_f3);
        if((num_count++)%100==0)
        {
            ROS_INFO("base %f,f1 %f,f2 %f,f3 %f",bhandpose1.rec_base,bhandpose1.rec_f1,bhandpose1.rec_f2,bhandpose1.rec_f3);
	    //ROS_INFO("Joint Speed:f1 %f,f2 %f,f3 %f.",v_f1,v_f2,v_f3);
            //ROS_INFO("Sensor Heavy Point number:F1 %d,F2 %d,F3 %d\n",f1_heavy_force_point_num,f2_heavy_force_point_num,f3_heavy_force_point_num);
        }
        key_control_value=0;
        delta_v_f1=v_f1-rec_v_f1;
        delta_v_f2=v_f2-rec_v_f2;
        delta_v_f3=v_f3-rec_v_f3;
        if((bhandpose1.rec_f1<=2.2 && bhandpose1.rec_f1>=0)&&(bhandpose1.rec_f2<=2.2 && bhandpose1.rec_f2>=0)&&(bhandpose1.rec_f3<=2.2 && bhandpose1.rec_f3>=0))
        {
            if(f1_heavy_force_point_num>=3) v_f1=0;
            if(f2_heavy_force_point_num>=3) v_f2=0;
            if(f3_heavy_force_point_num>=3) v_f3=0;
            bhandpose1.bhand_move_velocity(v_base,v_f1,v_f2,v_f3,0);

        }
        else
            v_f1=v_f2=v_f3=0;
//        if(bhandpose1.rec_f1>=2.2 || bhandpose1.rec_f2>=2.2 || bhandpose1.rec_f3>=2.2)
//        {
//            usleep(500000);
//            bhandpose1.bhand_spinner(1);
//            usleep(500000);
//            if(bhandpose1.rec_f1>=2.2 || bhandpose1.rec_f2>=2.2 || bhandpose1.rec_f3>=2.2)
//            {
//                v_f1=v_f2=v_f3=-0.02;
//                bhandpose1.bhand_move_velocity(0,v_f1,v_f2,v_f3,0);
//            }
//        }

        rec_v_f1=v_f1;
        rec_v_f2=v_f2;
        rec_v_f3=v_f3;
        //------notice topic control hand close or open start......

        if(close_hand_flag)
            {
//
//            //action deal
//                float joint_limit=1.45;
//                v_f1=v_f2=v_f3=0.4;
//                if(f1_heavy_force_point_num>=3)
//                {
//                    v_f1=0;
//                }
//                if(f2_heavy_force_point_num>=3)
//                {
//                    v_f2=0;
//                }
//                if(f3_heavy_force_point_num>=3)
//                {
//                    v_f3=0;
//                }

//                if(bhandpose1.rec_f1>=joint_limit )
//                {
//                    //usleep(10000);
//                    if(bhandpose1.rec_f1>=joint_limit )
//                    {
//                        v_f1=0;
//                        f1_close_flag=true;
//                        close_wait_flag=true;
//                        close_wait_count=num_count;
//                        ROS_INFO("f3 closed finished.close time:%d",close_wait_count);
//                    }

//                }
//                if(bhandpose1.rec_f2>=joint_limit )
//                {
//                    //usleep(10000);
//                    if(bhandpose1.rec_f1>=joint_limit )
//                    {
//                        v_f2=0;
//                        f2_close_flag=true;
//                        close_wait_flag=true;
//                        close_wait_count=num_count;
//                        ROS_INFO("f3 closed finished.close time:%d",close_wait_count);
//                    }
//                }
//                if(bhandpose1.rec_f3>=joint_limit )
//                {
//                    //usleep(10000);
//                    if(bhandpose1.rec_f1>=joint_limit )
//                    {
//                        v_f3=0;
//                        f3_close_flag=true;
//                        close_wait_flag=true;
//                        close_wait_count=num_count;
//                        ROS_INFO("f3 closed finished.close time:%d",close_wait_count);
//                    }
//                }
//                if(( (f1_heavy_force_point_num>=3) && (f2_heavy_force_point_num>=3) && (f3_heavy_force_point_num>=3)))
//                {
//                    v_f1=v_f2=v_f3=0;
//                    bhandpose1.bhand_move_velocity(v_base,v_f1,v_f2,v_f3,0);
//                    notice_data_clear(&notice_data_pub);
//                    notice_data_pub.id=1;
//                    notice_data_pub.data[0]=2;
//                    notice_test.notice_pub_sub_pulisher(notice_data_pub);
//                    close_hand_flag=false;
//                    printf("Close hand successfully!\n");
//                }

//                if( (f1_close_flag && f2_close_flag )||(f1_close_flag && f3_close_flag)||(f2_close_flag && f3_close_flag))
//                {
//                    f1_close_flag=false;f2_close_flag=false;f3_close_flag=false;
//                    v_f1=v_f2=v_f3=0;
//                    bhandpose1.bhand_move_velocity(v_base,v_f1,v_f2,v_f3,0);
//                    notice_data_clear(&notice_data_pub);
//                    notice_data_pub.id=1;
//                    notice_data_pub.data[0]=2;
//                    notice_test.notice_pub_sub_pulisher(notice_data_pub);
//                    close_hand_flag=false;
//                    printf("Close hand successfully!\n");
//                }
//                else if(close_wait_flag)
//                {
//                    if((num_count-close_wait_count)>=1000)
//                    {
//                        close_wait_flag=false;
//                        f1_close_flag=false;f2_close_flag=false;f3_close_flag=false;
//                        v_f1=v_f2=v_f3=0;
//                        bhandpose1.bhand_move_velocity(v_base,v_f1,v_f2,v_f3,0);
//                        notice_data_clear(&notice_data_pub);
//                        notice_data_pub.id=1;
//                        notice_data_pub.data[0]=2;
//                        notice_test.notice_pub_sub_pulisher(notice_data_pub);
//                        close_hand_flag=false;
//                        printf("Close hand exceeds Waiting time!\n");
//                    }
//                }
                open_hand_flag=false;
                state_test.bhand_control_mode("POSITION");
                sleep(3);
                bhandpose1.bhand_move_position(0,1.5,1.5,1.5,1);
                sleep(5);
                state_test.bhand_control_mode("VELOCITY");

                notice_data_clear(&notice_data_pub);
                notice_data_pub.id=1;
                notice_data_pub.data[0]=2;
                notice_test.notice_pub_sub_pulisher(notice_data_pub);
                close_hand_flag=false;
                printf("Close hand successfully!\n");



            }

        if(open_hand_flag)
            {
                close_hand_flag=false;
                //action deal
                v_f1=v_f2=v_f3=-0.4;
                bhandpose1.bhand_move_velocity(v_base,v_f1,v_f2,v_f3,0);
                if(bhandpose1.rec_f1<=0.2) v_f1=0;
                if(bhandpose1.rec_f2<=0.2) v_f2=0;
                if(bhandpose1.rec_f3<=0.2) v_f3=0;
                if(bhandpose1.rec_f1<=0.2 && bhandpose1.rec_f2<=0.2 && bhandpose1.rec_f3<=0.2)
                {
                    v_f1=v_f2=v_f3=0;
                    bhandpose1.bhand_move_velocity(v_base,v_f1,v_f2,v_f3,0);
                    notice_data_clear(&notice_data_pub);
                    notice_data_pub.id=1;
                    notice_data_pub.data[0]=2;
                    notice_test.notice_pub_sub_pulisher(notice_data_pub);
                    open_hand_flag=false;
                    printf("Open hand successfully!\n");
                    state_test.bhand_control_mode("POSITION");
                    state_test.bhand_action_test(3,1);
                    sleep(3);
                    bhandpose1.bhand_move_position(0,0.5,0.5,0.5,1);
                    sleep(5);
                    state_test.bhand_control_mode("VELOCITY");
                }
            }
	
        v_f1=rec_v_f1;
        v_f2=rec_v_f2;
        v_f3=rec_v_f3;

        //------notice topic control hand close or open end......


        state_test.bhand_spinner(1);
        bhandpose1.bhand_spinner(1);
        tactile_test.tactile_sub_spinner(1);
        keyboard_control.keyboard_monitor_spinner(1);
        //notice call back function trigger
        notice_test.notice_sub_spinner(1);

        speed_loop_rate.sleep();

    }

    return 0;
}

void Sensor_ForceHeavyPoint_Count(beginner_tutorials::ForceData force_msg,int sensor_id,int *f_heavy_force_point_num,sensor_flag *sensorflag)
{
    if(force_msg.id==sensor_id+0 )
    {
        for(char i=0;i<8;i++)
        {
            if(force_msg.data[i]>=force_threshold)
                *f_heavy_force_point_num=*f_heavy_force_point_num+1;
        }
        sensorflag->row0_flag=1;
    }
    if(force_msg.id==sensor_id+1 )
    {
        for(char i=0;i<8;i++)
        {
            if(force_msg.data[i]>=force_threshold)
                *f_heavy_force_point_num=*f_heavy_force_point_num+1;
        }
        sensorflag->row1_flag=1;
    }
    if(force_msg.id==sensor_id+2 )
    {
        for(char i=0;i<8;i++)
        {
            if(force_msg.data[i]>=force_threshold)
                *f_heavy_force_point_num=*f_heavy_force_point_num+1;
        }
        sensorflag->row2_flag=1;
    }
    if(force_msg.id==sensor_id+3 )
    {
        for(char i=0;i<8;i++)
        {
            if(force_msg.data[i]>=force_threshold)
                *f_heavy_force_point_num=*f_heavy_force_point_num+1;
        }
        sensorflag->row3_flag=1;
    }
    if(force_msg.id==sensor_id+4 )
    {
        for(char i=0;i<8;i++)
        {
            if(force_msg.data[i]>=force_threshold)
                *f_heavy_force_point_num=*f_heavy_force_point_num+1;
        }
        sensorflag->row4_flag=1;
    }
    if(force_msg.id==sensor_id+5 )
    {
        for(char i=0;i<8;i++)
        {
            if(force_msg.data[i]>=force_threshold)
                *f_heavy_force_point_num=*f_heavy_force_point_num+1;
        }
        sensorflag->row5_flag=1;
    }
    if(force_msg.id==sensor_id+6 )
    {
        for(char i=0;i<8;i++)
        {
            if(force_msg.data[i]>=force_threshold)
                *f_heavy_force_point_num=*f_heavy_force_point_num+1;
        }
        sensorflag->row6_flag=1;
    }
    if(force_msg.id==sensor_id+7 )
    {
        for(char i=0;i<8;i++)
        {
            if(force_msg.data[i]>=force_threshold)
                *f_heavy_force_point_num=*f_heavy_force_point_num+1;
        }
        sensorflag->row7_flag=1;
    }
    if(sensorflag->row0_flag && sensorflag->row1_flag && sensorflag->row2_flag && sensorflag->row3_flag && sensorflag->row4_flag && sensorflag->row5_flag && sensorflag->row6_flag && sensorflag->row7_flag)
    {
        *(sensorflag)={0};
        *f_heavy_force_point_num=0;
    }
}

void notice_data_clear(id_data_msgs::ID_Data *test)
{
    test->id=0;
    for(int i=0;i<8;i++) test->data[i]=0;
}

