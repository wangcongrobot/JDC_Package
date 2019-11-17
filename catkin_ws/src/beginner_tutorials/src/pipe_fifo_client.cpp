#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ros/ros.h>

#include <ctime>
//debug note:
//1,pipe_fifo_datasend() is block mode,the process can not do other deal untill
//the function send data successfully.its' frequency is not stable.
//2,pipe_fifo_dataread() is block mode too.
//3,the mode of read and write function is determined by open mode of server_fifo
//and client fifo.

#define random(x) (rand()%x)

using namespace std;

#define SERVER_FIFO_NAME "/tmp/serv_fifo"
#define CLIENT_FIFO_NAME "/tmp/client_fifo"

#define BUFFER_SIZE 8

struct message
{
    pid_t client_pid;
    int data[BUFFER_SIZE + 1];
    void init_struct(void){client_pid=0;memset(data,0,sizeof(int)*BUFFER_SIZE);}
};

//function declaration
int pipe_fifo_server_init(const char  *server_pipename,int server_fifo_fd);
int pipe_fifo_client_init(const char  *client_pipename,int client_fifo_fd);
message pipe_fifo_datasend(int server_fifo_fd,message msg,bool display_on);
message pipe_fifo_dataread(int client_fifo_fd,bool display_on);
int random_number(int rand_max);
int delay_rand_time();


int main(int argc,char **argv)
{
    ros::init(argc,argv,"pipe_client");
    ros::NodeHandle test_handle;//useless
    int loop_hz=1;
    ros::Rate loop_rate(loop_hz);

    int server_fifo_fd;
    int client_fifo_fd;
    message msg={0};


    srand((int)time(0));//the seed of random number producing

    //以只写方式打开server端FIFO，这个名字是公共知晓的
    server_fifo_fd=pipe_fifo_server_init(SERVER_FIFO_NAME,server_fifo_fd);


    client_fifo_fd=pipe_fifo_client_init(CLIENT_FIFO_NAME,client_fifo_fd);


    while(ros::ok())
    {

        msg.client_pid = 1;
        msg.data[0]=1;
        pipe_fifo_datasend(server_fifo_fd,msg,true);
        delay_rand_time();

        pipe_fifo_dataread(client_fifo_fd,true);
        loop_rate.sleep();
    }

    //关闭server端FIFO
    close(server_fifo_fd);
    close(client_fifo_fd);
    return EXIT_SUCCESS;
}


//Pipe FIFO:inter-process communication,function defination
int pipe_fifo_server_init(const char  *server_pipename,int server_fifo_fd)
{
    server_fifo_fd = open(server_pipename, O_WRONLY);
    if (server_fifo_fd == -1)
    {
        fprintf(stderr, "Sorry, no server\n");
        return EXIT_FAILURE;
    }

}

int pipe_fifo_client_init(const char  *client_pipename,int client_fifo_fd)
{
    //创建client端FIFO
    if(access(client_pipename,F_OK) == -1)
    {
        if (mkfifo(client_pipename, 0777) == -1)
        {
            fprintf(stderr, "Sorry, can not creat pipe client\n");
            return EXIT_FAILURE;
        }

    }

    client_fifo_fd = open(client_pipename, O_RDONLY);
    if (client_fifo_fd == -1)
    {
        fprintf(stderr, "Sorry, no client\n");
        return EXIT_FAILURE;
    }
    return client_fifo_fd;
}

message pipe_fifo_dataread(int client_fifo_fd,bool display_on)
{
    int read_res=0;
    message msg;
    msg.init_struct();
    if (client_fifo_fd != -1)
    {
        read_res=read(client_fifo_fd, &msg, sizeof(struct message));
        if (read_res== sizeof(struct message))
        {
            if(display_on)
            {
                printf("RECV ID:%d\tData:",msg.client_pid);
                for(int i=1;i<=8;i++)
                {
                    printf ("%d\t",msg.data[i-1]);
                    if(i==8) printf("\n");
                }
            }
        }

    }
    return msg;
}

message pipe_fifo_datasend(int server_fifo_fd,message msg,bool display_on)
{
    //将数据写入sever端FIFO
    if(display_on)
    {
        printf("SEND ID:%d\tData:",msg.client_pid);
        for(char i=0;i<8;i++)
        {
            printf("%d\t",msg.data[i]);
            if(i==7)printf("\n");
        }
    }
    write(server_fifo_fd, &msg, sizeof(msg));

    return msg;
}

int random_number(int max_rand)
{

    return int(random(max_rand));

}

int delay_rand_time()
{
    int t=random_number(10000);
    printf("Delay time:%d\t\n",t);
    usleep(t);
    return t;
}









