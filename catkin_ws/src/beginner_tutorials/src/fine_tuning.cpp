#include "ros/callback_queue.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ros/ros.h>
#include <time.h>

#include <id_data_msgs/ID_Data.h>

using namespace std;

double waittime   = 15.0;
double time_limit = 3000.0;

// globals
const string objects[] = {"book",   "toothbrush", "can",        "strips",  "chips", "oreo",  "pacific", "shampoo",
                          "tissue", "sausage",    "toothpaste", "teether", "milk",  "jelly", "tablet",  "orange"};
int      error_index = 0;
set<int> object_list; // the list of target objects to fetch
// vector<int> place_sequence;   // the sequence of place goal to navigate
int place_length;
multimap<int, int> place_obj_sequence; // each element composed of place and object
// int row[20]={0},column[20]={0};
// int obj_num=0;
// int loop_sys_cnt=0;
// int obj_cnt=0;

// 1,navigation section,id=2
bool nav_msg_rec_flag; // data[0]=14
// bool nav_start_pos_flag;   //data[0]=0
// bool nav_column1_pos_flag; //data[0]=1
// bool nav_column2_pos_flag; //data[0]=2
// bool nav_column3_pos_flag; //data[0]=3
// bool nav_release_pos_flag; //data[0]=4
bool nav_navigation_flag; // data[0]=1
bool nav_finetuning_flag; // data[0]=1
bool nav_finished_flag;   // data[0]=15
bool command_move_finished_flag = false;

// 2,kinect scan section,id=3
bool kinect_scan_start_flag; // data[0]=1
// bool kinect_scan_stop_flag;        //data[0]=0
// bool kinect_scan_fail_flag;        //data[0]=13
bool kinect_msg_rec_flag; // data[0]=14
bool kinect_reset_flag = false;
bool kinect_scan_finished_flag; // data[0]=15
bool kinect_need_finetune_flag; // data[0]=16
bool kinect_not_found_flag;     // data[0]=17

// 3,arm control section,id=4
bool arm_start_fetch_flag;  // data[0]=1
bool arm_stop_fetch_flag;   // data[0]=0
bool arm_keep_fetch_flag;   // data[0]=2
bool arm_release_obj_flag;  // data[0]=3
bool arm_msg_rec_flag;      // data[0]=14
bool arm_act_finished_flag; // data[0]=15

// derfine
// int set_ontime=0;

// For target position
int pose_x, pose_y, pose_z;

void notice_data_clear(id_data_msgs::ID_Data *test);

class notice_pub_sub
{
  public:
	boost::function<void(const id_data_msgs::ID_Data::ConstPtr &)> notice_pub_sub_msgCallbackFun;

	notice_pub_sub();
	~notice_pub_sub();
	void notice_pub_sub_publisher(id_data_msgs::ID_Data id_data);
	void notice_display(id_data_msgs::ID_Data notice_msg, bool set);
	void notice_sub_spinner(char set);

  private:
	ros::NodeHandle       notice_handle;
	ros::Subscriber       notice_subscriber;
	ros::Publisher        notice_publisher;
	ros::SubscribeOptions notice_ops;
	ros::AsyncSpinner *   notice_spinner;
	ros::CallbackQueue    notice_callbackqueue;
	void notice_msgCallback(const id_data_msgs::ID_Data::ConstPtr &notice_msg);
};

notice_pub_sub::notice_pub_sub()
{
	notice_pub_sub_msgCallbackFun = boost::bind(&notice_pub_sub::notice_msgCallback, this, _1);
	notice_ops = ros::SubscribeOptions::create<id_data_msgs::ID_Data>("/notice", 50, notice_pub_sub_msgCallbackFun,
	                                                                  ros::VoidPtr(), &notice_callbackqueue);
	notice_subscriber = notice_handle.subscribe(notice_ops);
	notice_spinner    = new ros::AsyncSpinner(1, &notice_callbackqueue);

	notice_publisher = notice_handle.advertise<id_data_msgs::ID_Data>("/notice", 50);
}

notice_pub_sub::~notice_pub_sub() { delete notice_spinner; }

void notice_pub_sub::notice_pub_sub_publisher(id_data_msgs::ID_Data id_data) { notice_publisher.publish(id_data); }

void notice_pub_sub::notice_display(id_data_msgs::ID_Data notice_msg, bool set)
{

	if (set)
	{
		printf("REC Notice message,ID: %d,Data: ", notice_msg.id);
		for (char i = 0; i < 8; i++) {
			printf("%d ", notice_msg.data[i]);
			if (i == 7)
				printf("\n");
		}
	}
}

void notice_pub_sub::notice_msgCallback(const id_data_msgs::ID_Data::ConstPtr &notice_msg)
{

	id_data_msgs::ID_Data notice_message;
	notice_message.id = 0;
	for (char i = 0; i < 8; i++) notice_message.data[i] = 0;

	notice_message.id = notice_msg->id;
	for (char i = 0; i < 8; i++) notice_message.data = notice_msg->data;

	notice_pub_sub::notice_display(notice_message, true);

	// 1,navigation section
	if (notice_message.id == 2 && notice_message.data[0] == 14) // msg received flag
	{
		nav_msg_rec_flag = true;
	}
	if (notice_message.id == 2 && notice_message.data[0] == 16) // nav finished flag
	{
		nav_finished_flag = true;
	}
	// if(notice_message.id==2 && notice_message.data[0]==16)//nav finished flag
	// {
	//     // set_ontime++;
	//     // ROS_WARN("ON TIME No.%d",set_ontime);
	// }
	if (notice_message.id == 2 && notice_message.data[0] == 8)
	{
		command_move_finished_flag = true;
		ROS_INFO("Received dashgo command move finished flag");
	}

	// 2,kinect scan section
	if (notice_message.id == 3 && notice_message.data[0] == 14) // kinect msg received flag
	{
		kinect_msg_rec_flag   = true;
		kinect_not_found_flag = false;
	}
	if (notice_message.id == 3 && notice_message.data[0] == 15) // kinect scan finished flag
	{
		kinect_scan_finished_flag = true;
		pose_x                    = notice_message.data[2];
		pose_y                    = notice_message.data[3];
		pose_z                    = notice_message.data[4];
	}
	if (notice_message.id == 3 && notice_message.data[0] == 16) // target out of range
	{
		// to be filled
		kinect_not_found_flag     = true;
		kinect_scan_finished_flag = true;
		ROS_INFO("need fine tuning");
	}

	if (notice_message.id == 3 && notice_message.data[0] == 17)
	{
		ROS_INFO("target not found.");
		kinect_not_found_flag     = true;
		kinect_scan_finished_flag = true;
		ROS_INFO("then");
	}

	// if(notice_message.id==3 && notice_message.data[0]==13)//kinect scan failed
	// {
	//  //       id_data_msgs::ID_Data id_data;
	//  //       id_data.id=3;
	//  //       for(int count=0;count<8;count++) id_data.data[count]=0;
	//  //       id_data.data[0]=1;
	//  //       notice_publisher.publish(id_data);

	//     row[obj_num]=row[obj_cnt-1];
	//     column[obj_num]=column[obj_cnt-1];
	//     obj_num++;
	//     kinect_reset_flag=true;
	//     ROS_WARN("Received missing current column flag.Save data
	//     No.%d,Row:%d,Col%d",obj_cnt,row[obj_cnt-1],column[obj_cnt-1]);
	//     kinect_scan_finished_flag=true;

	// }
	// 3,arm control section
	if (notice_message.id == 4 && notice_message.data[0] == 14) // arm control msg received flag
	{
		arm_msg_rec_flag = true;
	}
	if (notice_message.id == 4 && notice_message.data[0] == 15) // arm fetch finished flag
	{
		object_list.erase(object_list.find(notice_message.data[1]));
		arm_act_finished_flag = true;
	}
}

void notice_pub_sub::notice_sub_spinner(char set)
{
	if (set == 1)
		notice_spinner->start();
	if (set == 0)
		notice_spinner->stop();
}

// function declaration

int main_MsgConform_ActFinishedWait(id_data_msgs::ID_Data *notice_data_test, bool *msg_rec_flag, bool *finished_flag,
                                    notice_pub_sub *notice_test);
void error_deal(int error_index);

int main(int argc, char **argv)
{
	ros::init(argc, argv, "fetch_process");

	// read target object list from object_list.txt
	ifstream object_list_file("/home/robot/object_list.txt");
	if (!object_list_file.is_open())
	{
		ROS_ERROR("Failed to open object list file");
		return -1;
	}

	ROS_INFO("Objects to be fetch: ");
	string obj_str;
	int    obj_num;
	while (getline(object_list_file, obj_str)) {
		sscanf(obj_str.c_str(), "%d", &obj_num);
		object_list.insert(obj_num);
		ROS_INFO_STREAM("    " << objects[obj_num]);
	}
	object_list_file.close();

	// read place sequence length
	ifstream place_sequence_file("/home/robot/place_sequence.txt");
	if (!place_sequence_file.is_open())
	{
		ROS_INFO("Failed to open place sequence file");
		return -1;
	}
	string place_length_str;
	getline(place_sequence_file, place_length_str);
	sscanf(place_length_str.c_str(), "%d", &place_length);
	ROS_INFO_STREAM("Place length: " << place_length);
	place_sequence_file.close();

	for (int i = 3; i <= place_length + 2; i++) {
		for (set<int>::iterator it = object_list.begin(); it != object_list.end(); it++) {
			place_obj_sequence.insert(make_pair(i, *it));
		}
	}

	notice_pub_sub        notice_test;
	id_data_msgs::ID_Data notice_data;

	ROS_INFO("timer start...");
	ros::Time start = ros::Time::now();

	for (multimap<int, int>::iterator it = place_obj_sequence.begin(); it != place_obj_sequence.end(); it++) {
		ROS_INFO_STREAM("place: " << it->first << " object: " << it->second);

		int place  = it->first;
		int object = it->second;

		if (object_list.find(object) == object_list.end())
			continue;

		// 1,inform dashgo move to the column of object JOY position.
		ROS_INFO("1,inform mobile base move to the way-point for sweep/suck objects.");
		notice_data_clear(&notice_data);
		notice_data.id      = 2;
		notice_data.data[0] = 1;
		notice_data.data[1] = place;
		error_index =
		    main_MsgConform_ActFinishedWait(&notice_data, &nav_msg_rec_flag, &nav_finished_flag, &notice_test);
		error_deal(error_index);

		// 2,informs kinect to scan grid shelves
		// sleep(3);
		ROS_INFO("2,informs kinect to scan grid shelves");
		notice_data_clear(&notice_data);
		notice_data.id      = 3;
		notice_data.data[0] = 1;
		notice_data.data[1] = object;
		error_index = main_MsgConform_ActFinishedWait(&notice_data, &kinect_msg_rec_flag, &kinect_scan_finished_flag,
		                                              &notice_test);
		error_deal(error_index);

		if (kinect_not_found_flag)
		{
			// ROS_INFO("here");
			continue;
		}

		// if(kinect_reset_flag)
		// {
		//     id_data_msgs::ID_Data back_move;
		//     notice_data_clear(&back_move);
		//     back_move.id=2;
		//     back_move.data[0]=6;
		//     back_move.data[1]=50;
		//     notice_test.notice_pub_sub_publisher(back_move);
		//     command_move_finished_flag=false;
		//     while(ros::ok())
		//     {
		//         notice_test.notice_sub_spinner(1);
		//         if(command_move_finished_flag)
		//         {
		//             command_move_finished_flag=false;
		//             ROS_INFO("Mobile base achieved move command!");
		//             break;
		//         }
		//     }

		//     kinect_reset_flag=false;
		//     continue;
		// }

		// 3,informs kinova arm to fetch object
		ROS_INFO("3.1,informs kinova arm to fetch object");
		notice_data_clear(&notice_data);
		notice_data.id      = 4;
		notice_data.data[0] = 1;
		notice_data.data[1] = object;
		notice_data.data[2] = pose_x;
		notice_data.data[3] = pose_y;
		notice_data.data[4] = pose_z;
		error_index =
		    main_MsgConform_ActFinishedWait(&notice_data, &arm_msg_rec_flag, &arm_act_finished_flag, &notice_test);
		error_deal(error_index);
		// arm keep pose
		// ROS_INFO("3.2,Kinova Start being into Keep Pose ... ");
		// notice_data_clear(&notice_data);
		// notice_data.id=4;
		// notice_data.data[0]=2;
		// error_index=main_MsgConform_ActFinishedWait(&notice_data,&arm_msg_rec_flag,&arm_act_finished_flag,&notice_test);
		// error_deal(error_index);
		//
		//
		if ((ros::Time::now() - start).toSec() > time_limit)
		{
			ROS_INFO("time running up!");
			break;
		}

		/*
		        // while(set_ontime<2){};
		        // set_ontime=0;
		        //5,inform kinova arm to release the object.
		        ROS_INFO("5,inform kinova arm to release the object.");
		        notice_data_clear(&notice_data);
		        notice_data.id=4;
		        notice_data.data[0]=3;
		        error_index=main_MsgConform_ActFinishedWait(&notice_data,&arm_msg_rec_flag,&arm_act_finished_flag,&notice_test);
		        error_deal(error_index);

		        //6,inform dashgo move to the task start position.
		        ROS_INFO("6,inform dashgo move to the task start position.");
		        notice_data_clear(&notice_data);
		        notice_data.id=2;
		        notice_data.data[1]=1;
		        error_index=main_MsgConform_ActFinishedWait(&notice_data,&nav_msg_rec_flag,&nav_finished_flag,&notice_test);
		        error_deal(error_index);
		*/
		// if(0==column[loop_sys_cnt] && 0==row[loop_sys_cnt])
		// {
		//     ROS_INFO("Grasp tasks FINISHED!\n ");
		//     break;
		// }
	}

	// 5. move up the slider
	ROS_INFO("5. inform slider to move up.");
	notice_data_clear(&notice_data);
	notice_data.id      = 5;
	notice_data.data[0] = 8;
	notice_test.notice_pub_sub_publisher(notice_data);

	ros::Duration(0.1).sleep();

	start = ros::Time::now();

	// 4,inform dashgo move to the object release position.
	ROS_INFO("4,inform dashgo move to the object release position.");
	notice_data_clear(&notice_data);
	notice_data.id      = 2;
	notice_data.data[0] = 1;
	notice_data.data[1] = 2;
	error_index = main_MsgConform_ActFinishedWait(&notice_data, &nav_msg_rec_flag, &nav_finished_flag, &notice_test);
	error_deal(error_index);

	// sleep for a while
	// ros::Duration(3.0).sleep();

	while ((ros::Time::now() - start).toSec() <= waittime) ros::Duration(0.1).sleep();

	// 6. release all objects in
	ROS_INFO("6.Release all objects.");
	notice_data_clear(&notice_data);
	notice_data.id      = 6;
	notice_data.data[0] = 8;
	notice_test.notice_pub_sub_publisher(notice_data);

	return 0;
}

void notice_data_clear(id_data_msgs::ID_Data *test)
{
	test->id = 0;
	for (int i = 0; i < 8; i++) test->data[i] = 0;
}

int main_MsgConform_ActFinishedWait(id_data_msgs::ID_Data *notice_data_test, bool *msg_rec_flag, bool *finished_flag,
                                    notice_pub_sub *notice_test)
{
	id_data_msgs::ID_Data notice_data;
	int                   loop_hz = 10;
	ros::Rate             loop_rate(loop_hz);

	notice_data_clear(&notice_data);
	notice_data.id = notice_data_test->id;
	for (int i = 0; i < 8; i++) notice_data.data[i] = notice_data_test->data[i];
	notice_test->notice_pub_sub_publisher(notice_data);
	// data receive judge
	int wait_count = 0;
	while (ros::ok()) {

		if (*msg_rec_flag == true)
		{
			*msg_rec_flag = false;
			break;
		}

		wait_count++;
		if (wait_count % 10 == 0) // send msg again after waiting 1s
		{
			switch (notice_data.id)
			{
				case 2:
					ROS_ERROR("Mobile base didn't receive msg,Retrying...");
					break;
				case 3:
					ROS_ERROR("Kinect didn't receive msg,Retrying...");
					break;
				case 4:
					ROS_ERROR("Kinova arm didn't receive msg,Retrying...");
					break;
				default:
					break;
			}
			//
			// 1209
			notice_test->notice_pub_sub_publisher(notice_data);
		}
		if (wait_count >= 100)
		{
			error_index = notice_data.id;
			wait_count  = 0;
			goto next;
		}
		notice_test->notice_sub_spinner(1);
		loop_rate.sleep();
	}
	// navigation action finish judge
	while (ros::ok()) {
		if (*finished_flag == true)
		{
			*finished_flag = false;
			break;
		}

		notice_test->notice_sub_spinner(1);
		loop_rate.sleep();
	}

next:
	return error_index;
}

void error_deal(int error_index)
{
	switch (error_index)
	{
		case 2:
		{
			ROS_ERROR("Mobile base doesn't work normally!");
			break;
		}
		case 3:
		{
			ROS_ERROR("Kinect doesn't work normally!");
			break;
		}
		case 4:
		{
			ROS_ERROR("Kinova Arm doesn't work normally!");
			break;
		}
		default:
			break;
	}
}
