//#include <ros/ros.h>
//#include "bhand_controller/Service.h"
//#include "bhand_controller/Actions.h"

//int main(int argc,char **argv)
//{
//    ros::init(argc,argv,"example_srv_bhand");
//    ros::NodeHandle nh;
//    ros::ServiceClient client;
//    client=nh.serviceClient<bhand_controller::Actions>("bhand_node/actions");

//    bhand_controller::Actions test_action;
//    test_action.request.action=1;

//    if(client.call(test_action))
//    {
//        ROS_INFO("Init the robotic hand successfully!");
//        ros::Duration(3).sleep();
//        test_action.request.action=2;
//        if(client.call(test_action))
//            ROS_INFO("Closed the robotic hand successfully!");
//        else
//            ROS_INFO("Failed to close robottic hand!");
//    }
//    else
//        ROS_INFO("Failed to Init the robotic hand!");


//    /*
//    if(ros::service::call("bhand_node/actions",dd))
//        ROS_INFO("Init the robotic hand successfully!");
//    else
//        ROS_INFO("Failed to call action service!");
//    */

//    ros::spinOnce();
//    return 0;
//}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <errno.h>

using namespace std;

#define SERVER_FIFO_NAME "/tmp/serv_fifo"

#define BUFFER_SIZE 8

struct message
{
    pid_t client_pid;
    int data[BUFFER_SIZE + 1];
};

int pipe_fifo_init(const char  *server_pipename);
void pipe_fifo_datasend(int server_fifo_fd, message msg,char display);


int main()
{
    int server_fifo_fd;
    message msg;

    server_fifo_fd=pipe_fifo_init(SERVER_FIFO_NAME);

    //data fill
    int i;   
    for(i=0;i<BUFFER_SIZE+1;i++)    msg.data[i]=0;      //clear the data buffer
    for(i=0;i<=BUFFER_SIZE-1;i++)   msg.data[i]=i*10+1;   //write data of you are to send

    while(1)
    {
        pipe_fifo_datasend(server_fifo_fd, msg,1);
        sleep(1);
    }

    //关闭server端FIFO
    close(server_fifo_fd);
    return EXIT_SUCCESS;
}


int pipe_fifo_init(const char  *server_pipename)
{
    int res;
    if(access(server_pipename,F_OK) == -1)
    {
        //管道文件不存在
        //创建命名管道
        res = mkfifo(server_pipename, 0777);
        if(res != 0)
        {
            printf("Could not create fifo %s\n", server_pipename);
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO\n", getpid());
    //以读写阻塞方式打开FIFO文件
    int server_fifo_fd = open(server_pipename, O_RDWR);
    return server_fifo_fd;


}
void pipe_fifo_datasend(int server_fifo_fd, message msg,char display)
{
    int res;
    if(display==1)
    {
        printf("PIPE %d sent:\n", msg.client_pid);//display the sending data
        for(int i=0;i<BUFFER_SIZE;i++)
        {
            printf("%3d",msg.data[i]);
            if(i==BUFFER_SIZE-1)printf("\n");
        }
    }

    res= write(server_fifo_fd, &msg, sizeof(msg));
    if(res<0)printf("\nERROR in Pipe Fifo write %d\n",res);
}












