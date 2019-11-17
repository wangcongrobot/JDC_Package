#include <cstdio>
#include <iostream>
#include <ros/ros.h>
#include <string>

#include "id_data_msgs/ID_Data.h"
#include "serial/serial.h"

#include <sys/types.h>

#include "ros/callback_queue.h"
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

unsigned int send_count = 0;

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

unsigned char suckerCommand[3] = {0xAA, 0xBB, 0X30}; // sucker on/off
unsigned char magnetCommand[4] = {0xaa, 0xbb, 0X40}; // magnet:control bucket
unsigned char sliderCommand[4] = {0xaa, 0xbb, 0X50}; // slider up/down

unsigned char recv_buf[100] = {};

// globals
bool sucker_on_flag   = false;
bool sucker_off_flag  = false;
bool slider_up_flag   = false;
bool slider_down_flag = false;
bool magnet_on_flag   = false;
bool magnet_off_flag  = false;
// bool slider_pos_low = true;

void my_sleep(unsigned long milliseconds)
{
#ifdef _WIN32
	Sleep(milliseconds); // 100 ms
#else
	usleep(milliseconds * 1000); // 100 ms
#endif
}

void enumerate_ports()
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while (iter != devices_found.end()) {
		serial::PortInfo device = *iter++;

		printf("(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(), device.hardware_id.c_str());
	}
}

void print_usage()
{
	cerr << "Usage: test_serial {-e|<serial port address>} ";
	cerr << "<baudrate> [test string]" << endl;
}

class notice_pub_sub
{
  public:
	boost::function<void(const id_data_msgs::ID_Data::ConstPtr &)> notice_pub_sub_msgCallbackFun;

	notice_pub_sub();
	void notice_pub_sub_listener();
	void notice_pub_sub_publisher(id_data_msgs::ID_Data id_data);
	void notice_display(id_data_msgs::ID_Data notice_msg, bool set);
	void notice_sub_spinner(char set);
	void notice_data_clear(id_data_msgs::ID_Data *test);

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
	notice_ops = ros::SubscribeOptions::create<id_data_msgs::ID_Data>("/notice", 1, notice_pub_sub_msgCallbackFun,
	                                                                  ros::VoidPtr(), &notice_callbackqueue);
	notice_subscriber = notice_handle.subscribe(notice_ops);
	notice_spinner    = new ros::AsyncSpinner(1, &notice_callbackqueue);

	notice_publisher = notice_handle.advertise<id_data_msgs::ID_Data>("/notice", 1);
}

void notice_pub_sub::notice_pub_sub_publisher(id_data_msgs::ID_Data id_data) { notice_publisher.publish(id_data); }

void notice_pub_sub::notice_display(id_data_msgs::ID_Data notice_msg, bool set)
{

	if (set)
	{
		printf("REC Notice message,ID: %d,Data: ", notice_msg.id);
		for (char i = 0; i < 8; i++) {
			printf("%d ", notice_msg.data[i]);
		}
		printf("\n");
	}
}
void notice_pub_sub::notice_msgCallback(const id_data_msgs::ID_Data::ConstPtr &notice_msg)
{

	id_data_msgs::ID_Data notice_message;
	notice_message.id = 0;
	for (char i = 0; i < 8; i++) notice_message.data[i] = 0;

	notice_message.id = notice_msg->id;
	for (char i = 0; i < 8; i++) notice_message.data[i] = notice_msg->data[i];

	notice_pub_sub::notice_display(notice_message, true);

	if (notice_message.id == 1 && notice_message.data[0] == 8) // sucker on flag
	{
		sucker_on_flag = true;
		notice_data_clear(&notice_message);
		notice_message.id      = 1;
		notice_message.data[0] = 14;
		notice_publisher.publish(notice_message);
	}
	if (notice_message.id == 1 && notice_message.data[0] == 9) // sucker off flag
	{
		sucker_off_flag = true;
		notice_data_clear(&notice_message);
		notice_message.id      = 1;
		notice_message.data[0] = 14;
		notice_publisher.publish(notice_message);
	}
	if (notice_message.id == 5 && notice_message.data[0] == 8) // slider up flag
	{
		slider_up_flag = true;
		notice_data_clear(&notice_message);
		notice_message.id      = 1;
		notice_message.data[0] = 14;
		notice_publisher.publish(notice_message);
	}
	if (notice_message.id == 5 && notice_message.data[0] == 9) // slider down flag
	{
		slider_down_flag = true;
		notice_data_clear(&notice_message);
		notice_message.id      = 1;
		notice_message.data[0] = 14;
		notice_publisher.publish(notice_message);
	}
	if (notice_message.id == 6 && notice_message.data[0] == 8) // magnet open flag
	{
		magnet_on_flag = true;
		notice_data_clear(&notice_message);
		notice_message.id      = 1;
		notice_message.data[0] = 14;
		notice_publisher.publish(notice_message);
	}
	if (notice_message.id == 6 && notice_message.data[0] == 9) // magnet open flag
	{
		magnet_off_flag = true;
		notice_data_clear(&notice_message);
		notice_message.id      = 1;
		notice_message.data[0] = 14;
		notice_publisher.publish(notice_message);
	}
}

void notice_pub_sub::notice_sub_spinner(char set)
{
	if (set == 1)
		notice_spinner->start();
	if (set == 0)
		notice_spinner->stop();
}

void notice_pub_sub::notice_data_clear(id_data_msgs::ID_Data *test)
{
	test->id = 0;
	for (int i = 0; i < 8; i++) test->data[i] = 0;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "serial_sucker");
	ros::NodeHandle       sucker_handle;
	ros::Rate             loop_rate(100);
	notice_pub_sub        noticeSucker;
	id_data_msgs::ID_Data notice_data_pub;

	unsigned long baud = 115200;

	string port;
	string dev_name;
	ros::param::get("~dev_name", dev_name);
	ROS_INFO("Sucker Serial Com Device:%s", dev_name.c_str());
	if (dev_name == "")
		port = "/dev/ttyUSB0";
	else
		port = dev_name;

	if (argc < 2)
	{
		ROS_INFO("Default: Device %s, Baud rate %d", port.c_str(), baud);
	}

	// Argument 1 is the serial port or enumerate flag
	if (argc > 2)
	{
		port = argv[1];
		sscanf(argv[2], "%lu", &baud);
		if (port == "-e")
		{
			enumerate_ports();
			return 0;
		}
		else if (argc < 3)
		{
			print_usage();
			return 1;
		}
	}

	// port, baudrate, timeout in milliseconds
	serial::Serial my_serial(port, baud, serial::Timeout::simpleTimeout(50));

	cout << "Is the serial port open?";
	if (my_serial.isOpen())
	{
		cout << " Yes." << endl;
		ROS_INFO("Device %s, Baud rate %d", port.c_str(), baud);
	}
	else
	{
		cout << " No." << endl;
		return 0;
	}
	int           count          = 0; // iteration times
	unsigned char suckerRelayOn  = 0x41;
	unsigned char suckerRelayOff = 0x40;
	size_t        bytes_wrote;
	while (ros::ok()) {
		if (sucker_on_flag)
		{
			suckerCommand[2] = suckerRelayOff;
			suckerCommand[2] = 0x41;                              // suck up object
			bytes_wrote      = my_serial.write(suckerCommand, 3); // send the sucker control command

			size_t bytes_wrote = my_serial.write(suckerCommand, 3); // send the sucker control command
			sucker_on_flag     = false;
			ros::Duration(1).sleep();
			noticeSucker.notice_data_clear(&notice_data_pub);
			notice_data_pub.id      = 1;
			notice_data_pub.data[0] = 2;
			noticeSucker.notice_pub_sub_publisher(notice_data_pub);
			ROS_INFO("Suck on task finished ");
		}
		if (sucker_off_flag)
		{
			suckerCommand[2] = suckerRelayOn;
			suckerCommand[2] = 0x40;                              // release object
			bytes_wrote      = my_serial.write(suckerCommand, 3); // send the sucker control command

			size_t bytes_wrote = my_serial.write(suckerCommand, 3); // send the sucker control command
			sucker_off_flag    = false;
			ros::Duration(1).sleep();
			noticeSucker.notice_data_clear(&notice_data_pub);
			notice_data_pub.id      = 1;
			notice_data_pub.data[0] = 2;
			noticeSucker.notice_pub_sub_publisher(notice_data_pub);
			ROS_INFO("Suck off task finished ");
		}
		if (slider_up_flag)
		{
			suckerCommand[2] = suckerRelayOff;
			suckerCommand[2] = 0x51;                              // suck up object
			bytes_wrote      = my_serial.write(suckerCommand, 3); // send the sucker control command

			size_t bytes_wrote = my_serial.write(suckerCommand, 3); // send the sucker control command
			slider_up_flag     = false;
			ros::Duration(1).sleep();
			noticeSucker.notice_data_clear(&notice_data_pub);
			notice_data_pub.id      = 1;
			notice_data_pub.data[0] = 2;
			noticeSucker.notice_pub_sub_publisher(notice_data_pub);
			ROS_INFO("slider_up task finished ");
		}
		if (slider_down_flag)
		{
			suckerCommand[2] = suckerRelayOn;
			suckerCommand[2] = 0x50;                              // release object
			bytes_wrote      = my_serial.write(suckerCommand, 3); // send the sucker control command

			size_t bytes_wrote = my_serial.write(suckerCommand, 3); // send the sucker control command
			slider_down_flag   = false;
			ros::Duration(1).sleep();
			noticeSucker.notice_data_clear(&notice_data_pub);
			notice_data_pub.id      = 1;
			notice_data_pub.data[0] = 2;
			noticeSucker.notice_pub_sub_publisher(notice_data_pub);
			ROS_INFO("slider_down task finished ");
		}
		if (magnet_on_flag)
		{
			suckerCommand[2] = suckerRelayOff;
			suckerCommand[2] = 0x31;                              // suck up object
			bytes_wrote      = my_serial.write(suckerCommand, 3); // send the sucker control command

			size_t bytes_wrote = my_serial.write(suckerCommand, 3); // send the sucker control command
			magnet_on_flag     = false;
			ros::Duration(3).sleep();
			noticeSucker.notice_data_clear(&notice_data_pub);
			notice_data_pub.id      = 1;
			notice_data_pub.data[0] = 2;
			noticeSucker.notice_pub_sub_publisher(notice_data_pub);
			ROS_INFO("magnet_on task finished ");
		}
		if (magnet_off_flag)
		{
			suckerCommand[2] = suckerRelayOn;
			suckerCommand[2] = 0x30;                              // release object
			bytes_wrote      = my_serial.write(suckerCommand, 3); // send the sucker control command

			size_t bytes_wrote = my_serial.write(suckerCommand, 3); // send the sucker control command
			magnet_off_flag    = false;
			ros::Duration(1).sleep();
			noticeSucker.notice_data_clear(&notice_data_pub);
			notice_data_pub.id      = 1;
			notice_data_pub.data[0] = 2;
			noticeSucker.notice_pub_sub_publisher(notice_data_pub);
			ROS_INFO("magnet_off task finished ");
		}

		size_t nread = my_serial.read(recv_buf, 100);

		if (count % 100 == 0)
		{
			cout << "Iteration: " << count << ", Bytes read: ";
			cout << nread << endl;
		}
		if (nread != 0)
			ROS_INFO_STREAM(recv_buf);

		count += 1;
		noticeSucker.notice_sub_spinner(1);
		loop_rate.sleep();
	}

	return 0;
}
