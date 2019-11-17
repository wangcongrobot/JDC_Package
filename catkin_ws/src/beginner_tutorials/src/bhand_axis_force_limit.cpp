#include <ros/ros.h>
#include <stdio.h>
#include <dlfcn.h>
#include <libpcan.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "id_data_msgs/ID_Data.h"//using for notie event
#include "ros/callback_queue.h"
#include "string"

using namespace std;
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

#define FTSENSORID (8)
#define FTDATAPROPERTY (54)



//GLOBALS
void *libm_handle = NULL;//define pointer used for file acess of libpcan.so
HANDLE pcan_handle =NULL;//void *pcan_handle
id_data_msgs::ID_Data axis_force_msg;
bool force_display_on=true;
float force_threshold=4.0;
float torque_threshold=10.0;
double force_danger=15.0;
double torque_danger=30.0;
double left_torque_x_threshold=-1.0;
double right_torque_x_threshold=1.0;

//globals
bool close_hand_flag=false;
bool open_hand_flag=false;
float torque_x_float,torque_y_float,torque_z_float;
float force_x_float,force_y_float,force_z_float;

void notice_data_clear(id_data_msgs::ID_Data *test);


int wavePuck(int bus,int id);
int compile(
   int property        /** The property being compiled (use the enumerations in btcan.h) */,
   long longVal        /** The value to set the property to */,
   unsigned char *data /** A pointer to a character buffer in which to build the data payload */,
   int *dataLen        /** A pointer to the total length of the data payload for this packet */,
   int isForSafety        /** A flag indicating whether this packet is destined for the safety circuit or not */);
int setPropertySlow(int bus, int id, int property, int verify, long value);

//define function pointer,there is a one-to-one mapping between target function and your defined function
funCAN_Init_TYPE        funCAN_Init;
funLINUX_CAN_Open_TYPE  funLINUX_CAN_Open;
funCAN_VersionInfo_TYPE funCAN_VersionInfo;
funCAN_Close_TYPE       funCAN_Close;
funLINUX_CAN_Read_TYPE  funLINUX_CAN_Read;
funCAN_Status_TYPE      funCAN_Status;
funnGetLastError_TYPE   funnGetLastError;
funCAN_Write_TYPE       funCAN_Write;

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

    notice_pub_sub::notice_display(notice_message,true);

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
//function declaration
int  read_loop(HANDLE h,ros::Publisher pub,bool display_on,bool publish_on);
void print_message(TPCANMsg *m);
void print_message_ex(TPCANRdMsg *mr);
void do_exit(void *file,HANDLE h,int error);
void signal_handler(int signal);
void init();
void publish_forcedata(TPCANRdMsg *mr, ros::Publisher axis_force_pub, bool display_on);
void barett_hand_init();

void bhand_position_control(long f1_pos,long f2_pos,long f3_pos,long sp_pos);
void bhand_axis_force_warning(notice_pub_sub *notice_test,float force_x,float force_y,float force_z,float torque_x,float torque_y,float torque_z);
//
int sys_count=0;
int main(int argc,char **argv)
{
    ros::init(argc,argv,"bhand_axis_force");
    ros::NodeHandle handle_test;
    init();

    string dev_name;
    ros::param::get("~dev_name",dev_name);
    ROS_INFO("PCAN Device:%s",dev_name.c_str());

    int bhand_open_pos=5;
    ros::param::get("~bhand_open_pos",bhand_open_pos);
    ROS_INFO("Bhand open position :%d",bhand_open_pos);

    int bhand_close_pos=13;
    ros::param::get("~bhand_close_pos",bhand_close_pos);
    ROS_INFO("Bhand close position :%d",bhand_close_pos);

    ros::param::get("~force_display_on",force_display_on);
    ROS_INFO("ForceData display:%s",force_display_on==false?"false":"true");

    ros::param::get("~force_threshold",force_threshold);
    ROS_INFO("Force threshold  :%f",force_threshold);
    ros::param::get("~torque_threshold",torque_threshold);
    ROS_INFO("Torque threshold  :%f",torque_threshold);

    ros::param::get("~force_danger",force_danger);
    ROS_WARN(" Force dangerous threshold :%f",force_danger);
    ros::param::get("~torque_danger",torque_danger);
    ROS_WARN("Torque dangerous threshold :%f",torque_danger);

    ros::param::get("~left_torque_x_threshold",left_torque_x_threshold);
    ROS_WARN(" left torque x threshold :%f",left_torque_x_threshold);
    ros::param::get("~right_torque_x_threshold",right_torque_x_threshold);
    ROS_WARN("right torque x threshold :%f",right_torque_x_threshold);

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

    if(dev_name.c_str() !="")
        pcan_handle = funLINUX_CAN_Open(dev_name.c_str(), O_RDWR | O_NONBLOCK);
    else
    {
        pcan_handle = funLINUX_CAN_Open(szDevNode, O_RDWR | O_NONBLOCK);//use mapping function
        dev_name=DEFAULT_NODE;
    }

    //pcan_handle = funLINUX_CAN_Open(szDevNode, O_RDWR | O_NONBLOCK );//use mapping function

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
    bhand_position_control(bhand_open_pos*10000,bhand_open_pos*10000,bhand_open_pos*10000,0);//position: (0--2.5)*10 0000
    sleep(5);//waiting for bhand ready...

    ros::NodeHandle axis_force_handle;
    ros::Publisher axis_force_pub=axis_force_handle.advertise<id_data_msgs::ID_Data>("/notice",1);//advertise axis force to the topic named "/notice"
    ros::Rate loop_rate(100);
    //data receive test

    //wake puck
    wavePuck(0,8);
    //tare
    setPropertySlow(0,FTSENSORID,FTDATAPROPERTY,0,0);


    TPCANMsg test_data;
    //query the axis sensor.
    test_data.ID=0x008;
    test_data.LEN=1;
    test_data.MSGTYPE=MSGTYPE_STANDARD;
    test_data.DATA[0]=0x36;

    notice_pub_sub notice_test;
    id_data_msgs::ID_Data notice_data_pub;
    while(ros::ok())
    {
        sys_count++;
        if(sys_count%20==0)funCAN_Write(pcan_handle,&test_data);//query the axis sensor.
        read_loop(pcan_handle,axis_force_pub,false,true);
        bhand_axis_force_warning(&notice_test,force_x_float,force_y_float,force_z_float,torque_x_float,torque_y_float,torque_z_float);
        //HANDLE h,ros::Publisher pub, bool display_on,bool publish_on
        if(close_hand_flag)
        {
            open_hand_flag=false;
            bhand_position_control(bhand_close_pos*10000,bhand_close_pos*10000,bhand_close_pos*10000,0);//position: (0-2.5)*10 0000
            sleep(2);

            notice_data_clear(&notice_data_pub);
            notice_data_pub.id=1;
            notice_data_pub.data[0]=2;
            notice_test.notice_pub_sub_pulisher(notice_data_pub);
            close_hand_flag=false;
         }

        if(open_hand_flag)
        {
            close_hand_flag=false;
            bhand_position_control((bhand_open_pos-2)*10000,(bhand_open_pos-2)*10000,(bhand_open_pos-2)*10000,0);//position: (0-2.5)*10 0000
            sleep(2);
            bhand_position_control(bhand_open_pos*10000,bhand_open_pos*10000,bhand_open_pos*10000,0);//position: (0-2.5)*10 0000
            sleep(1);
            notice_data_clear(&notice_data_pub);
            notice_data_pub.id=1;
            notice_data_pub.data[0]=2;
            notice_test.notice_pub_sub_pulisher(notice_data_pub);
            open_hand_flag=false;
            ROS_INFO("Open hand successfully!\n");
        }

        notice_test.notice_sub_spinner(1);
        loop_rate.sleep();
    }




	return 0;
}

int wavePuck(int bus,int id)
{

    TPCANMsg msgOut;
    DWORD err;

    // Generate the outbound message
    msgOut.ID = id;
    msgOut.MSGTYPE = MSGTYPE_STANDARD;
    msgOut.LEN = 4;
    msgOut.DATA[0] = 0x85; // Set Status
    msgOut.DATA[1] = 0x00;
    msgOut.DATA[2] = 0x02; // Status = Ready
    msgOut.DATA[3] = 0x00;

    // Send the message
    //err = CAN_Write( &msgOut );
    err=funCAN_Write(pcan_handle,&msgOut);
    sleep(1);

    return(err);
}

int compile(
   int property        /** The property being compiled (use the enumerations in btcan.h) */,
   long longVal        /** The value to set the property to */,
   unsigned char *data /** A pointer to a character buffer in which to build the data payload */,
   int *dataLen        /** A pointer to the total length of the data payload for this packet */,
   int isForSafety        /** A flag indicating whether this packet is destined for the safety circuit or not */)
{
   int i;

   // Check the property
   //if(property > PROP_END)
   //{
   //   syslog(LOG_ERR,"compile(): Invalid property = %d", property);
   //   return(1);
   //}

   /* Insert the property */
   data[0] = property;
   data[1] = 0; /* To align the values for the tater's DSP */

   /* Append the value */
   for (i = 2; i < 6; i++)
   {
      data[i] = (char)(longVal & 0x000000FF);
      longVal >>= 8;
   }

   /* Record the proper data length */
   *dataLen = 6; //(dataType[property] & 0x0007) + 2;

   return (0);
}

int setPropertySlow(int bus, int id, int property, int verify, long value)
{
    TPCANMsg msgOut, msgIn;
    DWORD err;
    int dataHeader, i;
    long response;
    //unsigned char   data[8];
    int             len;

    //syslog(LOG_ERR, "About to compile setProperty, property = %d", property);
    // Compile 'set' packet
    err = compile(property, value, msgOut.DATA, &len, 0);

    // Generate the outbound message
    msgOut.ID = id;
    msgOut.MSGTYPE = MSGTYPE_STANDARD;
    msgOut.LEN = len;



    //syslog(LOG_ERR, "After compilation data[0] = %d", data[0]);
    msgOut.DATA[0] |= 0x80; // Set the 'Set' bit

    // Send the message
    //CAN_Write( &msgOut );
    funCAN_Write(pcan_handle,&msgOut);

    //Sleep(250);

    // BUG: This will not verify properties from groups of pucks
    return(0);
}

int getPropertyFT(int bus,HANDLE h)

{


    TPCANMsg msgOut, msgInOne, msgInTwo;
    DWORD err;


    // Generate the outbound message
    msgOut.ID = FTSENSORID;
    msgOut.MSGTYPE = MSGTYPE_STANDARD;
    msgOut.LEN = 1;
    msgOut.DATA[0] = FTDATAPROPERTY; // Get the ft data

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
    sleep(5);
    ROS_INFO("BHand Init successfully!");

}

void bhand_position_control(long f1_pos,long f2_pos,long f3_pos,long sp_pos)
{
    TPCANMsg CANMsg;


    CANMsg.LEN = 6;
    CANMsg.MSGTYPE =MSGTYPE_STANDARD;

    CANMsg.DATA[0] = 0xba;
    CANMsg.DATA[1] = 0;
    CANMsg.DATA[2] = 0;
    CANMsg.DATA[3] = 0;
    CANMsg.DATA[4] = 0;
    CANMsg.DATA[5] = 0;

    CANMsg.DATA[2] =  f1_pos & 0xff;
    CANMsg.DATA[3] = (f1_pos>>8) & 0xff;
    CANMsg.DATA[4] = (f1_pos>>16) & 0xff;

    CANMsg.ID = 0xcb;
    funCAN_Write(pcan_handle,&CANMsg);
    usleep(1000);
    CANMsg.DATA[2] = f2_pos & 0xff;
    CANMsg.DATA[3] = (f2_pos>>8) & 0xff;
    CANMsg.DATA[4] = (f2_pos>>16) & 0xff;

    CANMsg.ID = 0xcc;
    funCAN_Write(pcan_handle,&CANMsg);
    usleep(1000);

    CANMsg.DATA[2] = f3_pos & 0xff;
    CANMsg.DATA[3] = (f3_pos>>8) & 0xff;
    CANMsg.DATA[4] = (f3_pos>>16) & 0xff;

    CANMsg.ID = 0xcd;
    funCAN_Write(pcan_handle,&CANMsg);
    usleep(1000);

    CANMsg.DATA[2] = sp_pos & 0xff;
    CANMsg.DATA[3] = (sp_pos>>8) & 0xff;
    CANMsg.DATA[4] = (sp_pos>>16) & 0xff;

    CANMsg.ID = 0xce;
    funCAN_Write(pcan_handle,&CANMsg);
    usleep(1000);
}

int read_loop(HANDLE h,ros::Publisher pub, bool display_on,bool publish_on)
{
    TPCANRdMsg m;
    __u32 status;

    if (funLINUX_CAN_Read(h, &m)) {
        //perror("receivetest: LINUX_CAN_Read()");
        return errno;
    }
    if(m.Msg.ID == 0x50a || m.Msg.ID == 0x50b)
    {
        if (display_on)
            print_message_ex(&m);
        if (publish_on)
            publish_forcedata(&m,pub,force_display_on);

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
    }
    return 0;
}

void publish_forcedata(TPCANRdMsg *mr,ros::Publisher axis_force_pub,bool display_on)
{
    short int x_force,y_force,z_force;
    short int torque_x,torque_y,torque_z;


    if(0x50a==mr->Msg.ID )
    {
       x_force=mr->Msg.DATA[1];
       x_force<<=8;
       x_force|=mr->Msg.DATA[0];

       y_force=mr->Msg.DATA[3];
       y_force<<=8;
       y_force|=mr->Msg.DATA[2];

       z_force=mr->Msg.DATA[5];
       z_force<<=8;
       z_force|=mr->Msg.DATA[4];
       force_x_float=x_force/256.0;
       force_y_float=y_force/256.0;
       force_z_float=z_force/256.0;
       if(display_on) ROS_INFO(" Force x:%8.4f, y:%8.4f, z:%8.4f",force_x_float,force_y_float,force_z_float);
    }

    if(0x50b==mr->Msg.ID )
    {
       torque_x=mr->Msg.DATA[1];
       torque_x<<=8;
       torque_x|=mr->Msg.DATA[0];

       torque_y=mr->Msg.DATA[3];
       torque_y<<=8;
       torque_y|=mr->Msg.DATA[2];

       torque_z=mr->Msg.DATA[5];
       torque_z<<=8;
       torque_z|=mr->Msg.DATA[4];
       torque_x_float=torque_x/256.0;
       torque_y_float=torque_y/256.0;
       torque_z_float=torque_z/256.0;
       if(display_on) ROS_INFO("Torque x:%8.4f, y:%8.4f, z:%8.4f",torque_x_float,torque_y_float,torque_z_float);
    }

}

void bhand_axis_force_warning(notice_pub_sub *notice_test,float force_x,float force_y,float force_z,float torque_x,float torque_y,float torque_z)
{
    id_data_msgs::ID_Data notice_data_pub;
    if(fabs(force_x)>force_threshold || fabs(force_y)>force_threshold || fabs(force_z)>force_threshold)
    {
        notice_data_clear(&notice_data_pub);
        notice_data_pub.id=5;
        notice_data_pub.data[0]=13;
        //notice_test->notice_pub_sub_pulisher(notice_data_pub);
        //ROS_WARN(" Force threshhold:%8.4f BHAND COLLISION!",force_threshold);
        //ROS_INFO(" Force x:%8.4f, y:%8.4f, z:%8.4f",force_x_float,force_y_float,force_z_float);
        if(torque_x<=left_torque_x_threshold )
        {
            notice_data_clear(&notice_data_pub);
            notice_data_pub.id=5;
            notice_data_pub.data[0]=12;
            //notice_test->notice_pub_sub_pulisher(notice_data_pub);
            //ROS_WARN("LEFT arm Axis force sensor detect BHAND COLLISION!");
            usleep(10000);
        }
        if(torque_x>=right_torque_x_threshold )
        {
            notice_data_clear(&notice_data_pub);
            notice_data_pub.id=5;
            notice_data_pub.data[0]=11;
            //notice_test->notice_pub_sub_pulisher(notice_data_pub);
            //ROS_WARN("RIGHT Axis force sensor detect BHAND COLLISION!");
            usleep(10000);
        }

    }

    if(fabs(torque_x)>torque_threshold || fabs(torque_y)>torque_threshold || fabs(torque_z)>torque_threshold)
    {
        notice_data_clear(&notice_data_pub);
        notice_data_pub.id=5;
        notice_data_pub.data[0]=13;
        //notice_test->notice_pub_sub_pulisher(notice_data_pub);
        //ROS_WARN("Torque threshhold:%8.4f BHAND COLLISION!",torque_threshold);
        //ROS_INFO("Torque x:%8.4f, y:%8.4f, z:%8.4f",torque_x_float,torque_y_float,torque_z_float);
    }

    if(fabs(torque_x)>torque_danger || fabs(torque_y)>torque_danger || fabs(torque_z)>torque_danger || fabs(force_x)>force_danger || fabs(force_y)>force_danger || fabs(force_z)>force_danger)
    {
        notice_data_clear(&notice_data_pub);
        notice_data_pub.id=5;
        notice_data_pub.data[0]=14;
        notice_test->notice_pub_sub_pulisher(notice_data_pub);
        ROS_ERROR("Axis force sensor detect BHAND DANGER!");
        ROS_INFO(" Force x:%8.4f, y:%8.4f, z:%8.4f",force_x_float,force_y_float,force_z_float);
        ROS_INFO("Torque x:%8.4f, y:%8.4f, z:%8.4f",torque_x_float,torque_y_float,torque_z_float);
    }

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


void notice_data_clear(id_data_msgs::ID_Data *test)
{
    test->id=0;
    for(int i=0;i<8;i++) test->data[i]=0;
}
