#include <ros/ros.h>
#include <stdio.h>
#include <dlfcn.h>
#include <libpcan.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "beginner_tutorials/ForceData.h"

/*
 *
Author  :Hekai SIA
Date    :2016,10,12
Usage   :acquire the message on can bus,and publish the id and data of the message as a ros
        :topic.
E-mail  :hekai@sia.cn;susthekai@qq.com
Debug note:
1,the can_test process can not be ended when press ctrl+c, and the do_exit() can not be run.
2,when run the command-"rostopic echo /ArrayForceDEV",there are some negtive value even if i
added abs function when i copy the data from can message.
result:i use the int8 errorly, and the riginal data was unsigned char,i correct it as int16.

WARNING:Please resect the author the work,Don't use it as business application.
*
*/


//define mapping function according to target function in libpcan.h
typedef DWORD   (*funCAN_Init_TYPE)(HANDLE hHandle, WORD wBTR0BTR1, int nCANMsgType);
typedef HANDLE  (*funLINUX_CAN_Open_TYPE)(const char *szDeviceName, int nFlag);
typedef DWORD   (*funCAN_VersionInfo_TYPE)(HANDLE hHandle, LPSTR lpszTextBuff);
typedef DWORD   (*funCAN_Close_TYPE)(HANDLE hHandle);
typedef DWORD   (*funLINUX_CAN_Read_TYPE)(HANDLE hHandle, TPCANRdMsg* pMsgBuff);
typedef DWORD   (*funCAN_Status_TYPE)(HANDLE hHandle);
typedef int     (*funnGetLastError_TYPE)(void);
typedef DWORD   (*funCAN_Write_TYPE)(HANDLE hHandle, TPCANMsg* pMsgBuff);

//the target device name
#define DEFAULT_NODE "/dev/pcan0"

//GLOBALS
void *libm_handle = NULL;//define pointer used for file acess of libpcan.so
HANDLE pcan_handle =NULL;//void *pcan_handle


beginner_tutorials::ForceData force_msg;

//function declaration
int  read_loop(HANDLE h,ros::Publisher pub,bool display_on,bool publish_on);
void print_message(TPCANMsg *m);
void print_message_ex(TPCANRdMsg *mr);
void do_exit(void *file,HANDLE h,int error);
void signal_handler(int signal);
void init();
void publish_forcedata(TPCANRdMsg *mr,ros::Publisher force_pub);
void barett_hand_init();

//define function pointer,there is a one-to-one mapping between target function and your defined function
funCAN_Init_TYPE        funCAN_Init;
funLINUX_CAN_Open_TYPE  funLINUX_CAN_Open;
funCAN_VersionInfo_TYPE funCAN_VersionInfo;
funCAN_Close_TYPE       funCAN_Close;
funLINUX_CAN_Read_TYPE  funLINUX_CAN_Read;
funCAN_Status_TYPE      funCAN_Status;
funnGetLastError_TYPE   funnGetLastError;
funCAN_Write_TYPE       funCAN_Write;

int main(int argc, char *argv[])
{
    ros::init(argc,argv,"CAN_Test");
    ros::NodeHandle handle_test;
    init();
    //load libpcan.so using dlopen function,return handle for further use
    libm_handle = dlopen("libpcan.so", RTLD_LAZY );
    if (!libm_handle){
        printf("Open Error:%s.\n",dlerror());//if file can't be loaded,return null,get reason using dlerror function
        return 0;
    }

    char *errorInfo;//error information pointer
    //one-to-one mapping using dlsym function,if return null,mapping would be failed
    funCAN_Init         =(funCAN_Init_TYPE)         dlsym(libm_handle,"CAN_Init");
    funLINUX_CAN_Open   =(funLINUX_CAN_Open_TYPE)   dlsym(libm_handle,"LINUX_CAN_Open");
    funCAN_Close        =(funCAN_Close_TYPE)        dlsym(libm_handle,"CAN_Close");
    funCAN_VersionInfo  =(funCAN_VersionInfo_TYPE)  dlsym(libm_handle,"CAN_VersionInfo");
    funLINUX_CAN_Read   =(funLINUX_CAN_Read_TYPE)   dlsym(libm_handle,"LINUX_CAN_Read");
    funCAN_Status       =(funCAN_Status_TYPE)       dlsym(libm_handle,"CAN_Status");
    funnGetLastError    =(funnGetLastError_TYPE)    dlsym(libm_handle,"nGetLastError");
    funCAN_Write        =(funCAN_Write_TYPE)        dlsym(libm_handle,"CAN_Write");

    errorInfo = dlerror();//get error using dlerror function,and clear the error list in memory
    if (errorInfo != NULL){
        printf("Dlsym Error:%s.\n",errorInfo);
        return 0;
    }

    char txt[VERSIONSTRING_LEN];            //store information of can version
    unsigned short wBTR0BTR1 = CAN_BAUD_1M; //set the communicate baud rate of can bus
    int nExtended = CAN_INIT_TYPE_ST;       //set can message int standard model
    const char  *szDevNode = DEFAULT_NODE;  //define const pointer point to device name
    pcan_handle = funLINUX_CAN_Open(szDevNode, O_RDWR );//use mapping function

    //judge whether the call is success.if pcan_handle=null,the call would be failed
    if(pcan_handle){
        printf("CAN Bus test: %s have been opened\n", szDevNode);
        errno = funCAN_VersionInfo(pcan_handle, txt);
        if (!errno)
            printf("CAN Bus test: driver version = %s\n", txt);
        else {
            perror("CAN Bus test: CAN_VersionInfo()");
        }
        if (wBTR0BTR1) {
                errno = funCAN_Init(pcan_handle, wBTR0BTR1, nExtended);
                if (errno) {
                    perror("CAN Bus test: CAN_Init()");
                }
                else
                    printf("Device Info: %s; CAN_BAUD_1M; CAN_INIT_TYPE_ST\n", szDevNode);
            }
    }
    else
        printf("CAN Bus test: can't open %s\n", szDevNode);

    //test of can send data
    barett_hand_init();
    printf("--------\n");
    //set bhand on initial zero postures
    TPCANMsg test_data1,test_data2;
    test_data1.ID=0xcb;
    test_data1.LEN=6;
    test_data1.MSGTYPE=MSGTYPE_STANDARD;
    test_data1.DATA[0]=0xba;
    test_data1.DATA[1]=0x00;
    test_data1.DATA[2]=0x00;
    test_data1.DATA[3]=0x00;
    test_data1.DATA[4]=0x00;
    test_data1.DATA[5]=0x00;
    funCAN_Write(pcan_handle,&test_data1);
    ros::Duration(4).sleep();
    //set bhand on the other posture.
    test_data2.ID=0xcb;
    test_data2.LEN=6;
    test_data2.MSGTYPE=MSGTYPE_STANDARD;
    test_data2.DATA[0]=0xba;
    test_data2.DATA[1]=0x00;
    test_data2.DATA[2]=0x40;
    test_data2.DATA[3]=0x0d;
    test_data2.DATA[4]=0x03;
    test_data2.DATA[5]=0x00;
    funCAN_Write(pcan_handle,&test_data2);
    //ros::Duration(4).sleep();
    printf("--------\n");

    //initial a talker to publish the force data and can id.
    ros::NodeHandle force_handle;
    ros::Publisher force_pub=force_handle.advertise<beginner_tutorials::ForceData>("ArrayForcePUB",1);//advertise a topic named "ArrayForceDEV"
    ros::Rate loop_rate(1000);
    //data receive test
    while(ros::ok())
    {   //HANDLE h,ros::Publisher pub, bool display_on,bool publish_on
        read_loop(pcan_handle,force_pub,true,true);
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}


//read from CAN forever - until manual break
int read_loop(HANDLE h,ros::Publisher pub, bool display_on,bool publish_on)
{
    TPCANRdMsg m;
    __u32 status;

    if (funLINUX_CAN_Read(h, &m)) {
        perror("receivetest: LINUX_CAN_Read()");
        return errno;
    }

    if (display_on)
        print_message_ex(&m);
    if (publish_on)
        publish_forcedata(&m,pub);

    // check if a CAN status is pending
    if (m.Msg.MSGTYPE & MSGTYPE_STATUS) {
        status = funCAN_Status(h);
        if ((int)status < 0) {
            errno = funnGetLastError();
            perror("receivetest: CAN_Status()");
            return errno;
        }

        printf("receivetest: pending CAN status 0x%04x read.\n",
               (__u16)status);
    }
    return 0;
}

void publish_forcedata(TPCANRdMsg *mr,ros::Publisher force_pub)
{
    force_msg.id=mr->Msg.ID;
    for(__u8 i=0;i<8;i++)
    force_msg.data[i]=mr->Msg.DATA[i];
    force_pub.publish(force_msg);

}


void print_message(TPCANMsg *m)
{
    int i;

    //print RTR, 11 or 29, CAN-Id and datalength
    printf("receivetest: %c %c 0x%08x %1d ",
            ((m->MSGTYPE & MSGTYPE_RTR) ? 'r' : 'm') -
                ((m->MSGTYPE ) ? 0x20 : 0),
            (m->MSGTYPE & MSGTYPE_EXTENDED) ? 'e' : 's',
             m->ID,
             m->LEN);

    //don't print any telegram contents for remote frames
    if (!(m->MSGTYPE & MSGTYPE_RTR))
        for (i = 0; i < m->LEN; i++)
            printf("%02x ", m->DATA[i]);
          //printf("%3d ", m->DATA[i]);//decimal format print.
    printf("\n");
}

void print_message_ex(TPCANRdMsg *mr)
{
    printf("%u.%3u ", mr->dwTime, mr->wUsec);
    print_message(&mr->Msg);
}

// exit handler
void do_exit(void *file,HANDLE h,int error)
{
    //Must close h handle firstly,then close file using dlclose
    if (h) {
        funCAN_Close(h);
    }
    printf("\nCAN Bus test: finished (%d).\n\n", error);
    //after call the target function in ELF object,close it using dlclose
    dlclose(file);
    exit(error);
}

// the signal handler for manual break Ctrl-C
void signal_handler(int signal)
{
    do_exit(libm_handle,pcan_handle,0);
}

// what has to be done at program start
void init()
{
    /* install signal handlers */
    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);
}

void barett_hand_init()
{
    TPCANMsg test_data;
    //query the bhand state.
    for(char i=0;i<=3;i++)
    {
        test_data.ID=0xcb+i;
        test_data.LEN=1;
        test_data.MSGTYPE=MSGTYPE_STANDARD;
        test_data.DATA[0]=0x05;
        funCAN_Write(pcan_handle,&test_data);
    }

    for(char i=0;i<=3;i++)
    {
        test_data.ID=0xcb+i;
        test_data.LEN=6;
        test_data.MSGTYPE=MSGTYPE_STANDARD;
        test_data.DATA[0]=0xb2;
        for(char j=1;j<6;j++)test_data.DATA[j]=0;
        funCAN_Write(pcan_handle,&test_data);
    }

    for(char i=0;i<=3;i++)
    {
        test_data.ID=0xcb+i;
        test_data.LEN=6;
        test_data.MSGTYPE=MSGTYPE_STANDARD;
        for(char j=0;j<6;j++)test_data.DATA[j]=0;
        test_data.DATA[0]=0xce;
        test_data.DATA[2]=0xfa;
        funCAN_Write(pcan_handle,&test_data);
    }

    //query the bhand state.
    for(char i=0;i<=3;i++)
    {
        test_data.ID=0xcb+i;
        test_data.LEN=1;
        test_data.MSGTYPE=MSGTYPE_STANDARD;
        test_data.DATA[0]=0x00;
        funCAN_Write(pcan_handle,&test_data);
    }
    //query the bhand state.
    for(char i=0;i<=3;i++)
    {
        test_data.ID=0xcb+i;
        test_data.LEN=1;
        test_data.MSGTYPE=MSGTYPE_STANDARD;
        test_data.DATA[0]=0x5a;
        funCAN_Write(pcan_handle,&test_data);
    }
    //query the bhand state.
    for(char i=0;i<=3;i++)
    {
        test_data.ID=0xcb+i;
        test_data.LEN=1;
        test_data.MSGTYPE=MSGTYPE_STANDARD;
        test_data.DATA[0]=0x08;
        funCAN_Write(pcan_handle,&test_data);
    }
    //init the bhand.
    for(char i=0;i<=3;i++)
    {
        test_data.ID=0xcb+i;
        test_data.LEN=4;
        test_data.MSGTYPE=MSGTYPE_STANDARD;
        test_data.DATA[0]=0x9d;
        test_data.DATA[1]=0x00;
        test_data.DATA[2]=0x0d;
        test_data.DATA[3]=0x00;
        funCAN_Write(pcan_handle,&test_data);
    }
    ros::Duration(4).sleep();

}





