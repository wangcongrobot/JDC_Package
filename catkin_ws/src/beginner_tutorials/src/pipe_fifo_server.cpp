#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ros/ros.h>

#include <ctime>
//debug note:
//1,pipe_fifo_dataread() is nonblock,the process can do other deal when it do not
//call the function.so it need be more quicker than client
//2,the mode of read and write function is determined by open mode of server_fifo
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
int pipe_fifo_server_init(const char  *server_pipename);
int pipe_fifo_client_init(const char  *client_pipename);
message pipe_fifo_dataread(int server_fifo_fd,bool display_on);
message pipe_fifo_datasend(int client_fifo_fd,message msg,bool display_on);
int random_number(int rand_max);
int delay_rand_time();


int main(int argc,char **argv)
{
    ros::init(argc,argv,"pipe_server");
    ros::NodeHandle test_handle;//useless
    int loop_hz=10;
    ros::Rate loop_rate(loop_hz);

    int client_fifo_fd;
    int server_fifo_fd;
    message msg;



    //创建了server端的FIFO有名管道，并以只读方式打开，等待client输入
    server_fifo_fd=pipe_fifo_server_init(SERVER_FIFO_NAME);


    client_fifo_fd=pipe_fifo_client_init(CLIENT_FIFO_NAME);

    int mark_num;
    int rec_sys_num;
    bool close_hand_flag=false;
    unsigned int count=0;
    srand((int)time(0));

    while(ros::ok())
    {
        printf("System run No.%d.\n",count++);

        msg.init_struct();
        msg=pipe_fifo_dataread(server_fifo_fd,true);
        if(msg.client_pid==1 && msg.data[0]==1)
        {
            close_hand_flag=true;
            printf("Close Hand Start......\n");

            mark_num=random_number(10);
            rec_sys_num=count;

        }
        if(close_hand_flag)
        {
            //delay_rand_time();
            if(count-rec_sys_num==mark_num)
            {
                close_hand_flag=false;
                msg.client_pid=1;
                msg.data[0]=2;
                pipe_fifo_datasend(client_fifo_fd,msg,true);
                printf("Close Hand Successfully.\n");
            }

        }

        loop_rate.sleep();
    }

    //关闭server,client的FIFO
    close(server_fifo_fd);
    close(client_fifo_fd);
    return EXIT_SUCCESS;
}


//Pipe FIFO:inter-process communication,function defination
int pipe_fifo_server_init(const char  *server_pipename)
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
    //以读NON阻塞方式打开FIFO文件
    int server_fifo_fd = open(server_pipename, O_RDONLY | O_NONBLOCK);
    if (server_fifo_fd == -1)
    {
        fprintf(stderr, "Server fifo failure\n");
        return EXIT_FAILURE;
    }
    return server_fifo_fd;
}

int pipe_fifo_client_init(const char  *client_pipename)
{
    int client_fifo_fd;
    client_fifo_fd = open(client_pipename, O_WRONLY);
    if (client_fifo_fd == -1)
    {
        fprintf(stderr, "Sorry, no client\n");
        return EXIT_FAILURE;
    }

    return client_fifo_fd;
}


message pipe_fifo_dataread(int server_fifo_fd,bool display_on)
{
    int read_res;
    message msg;
    msg.init_struct();
    read_res=read(server_fifo_fd, &msg, sizeof(struct message));
    if(read_res==sizeof(struct message))
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

    return msg;
}

message pipe_fifo_datasend(int client_fifo_fd,message msg,bool display_on)
{
    if(display_on)
    {
        printf("SEND ID:%d\tData:",msg.client_pid);
        for(char i=0;i<8;i++)
        {
            printf("%d\t",msg.data[i]);
            if(i==7)printf("\n");
        }
    }

    if (client_fifo_fd != -1)
    {
        write(client_fifo_fd, &msg, sizeof(struct message));
    }

    return msg;
}

int random_number(int max_rand)
{

    return int(random(max_rand));

}

int delay_rand_time()
{
    int t=random_number(10);
    printf("Delay time:%d\t\n",t);
    sleep(t);
    return t;
}
