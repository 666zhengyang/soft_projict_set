/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: curry30
 * @Date: 2020-11-17 14:44:15
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-04 17:37:24
*/

#define TAG "chassis_port"

#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>
#include <stdio.h>
#include "uart.h"
#include "assert.h"

namespace joyrobot {

#define WHEEL_TRACK 0.236

typedef enum
{
    COMMAND_STOP,    // 手动： 停止,  0
    COMMAND_PAUSE,    // 暂停工作     1
    COMMAND_FORWARD,    // 手动： 向前   2
    COMMAND_BACKWARD,    // 手动： 向后   3
    COMMAND_LEFT_ROTATE,    // 手动： 左旋   4
    COMMAND_RIGHT_ROTATE,    // 手动： 右旋   5
    COMMAND_AUTO = 8,    // 开始工作      8
    
    COMMAND_AREA,
    COMMAND_RANGE,
    COMMAND_STOP_WORKING,    // 停止工作
    COMMAND_SPOT,    // 定点清扫      10
    COMMAND_LEFT_SIDEWALL,    // 左边沿边
    COMMAND_RIGHT_SIDEWALL,    // 右边沿边      12
    COMMAND_DOCKING,    // 回充电座
    COMMAND_WAITING,    //      14
    COMMAND_SUSPEND,    //      15
    COMMAND_POWER_OFF,      //      16
    COMMAND_BREAK,      //      17
    COMMAND_START_UPGRADE,
    COMMAND_STOP_UPGRADE,
    COMMAND_RESET = 0XF0,      //   240       clear error message
    COMMAND_NONE = 0XFF    // initial status
} COMMAND_TYPE;

typedef enum
{
    CTRL_MODE_STOP = 0,
    CTRL_MODE_FWALL,
    CTRL_MODE_AUTO,
    CTRL_MODE_AREA,
    CTRL_MODE_RANGE,
    CTRL_MODE_SPOT,
    CTRL_MODE_DOCK,
    CTRL_MODE_PAUSE,
    CTRL_MODE_FRONT,
    CTRL_MODE_BACK,
    CTRL_MODE_LEFT,
    CTRL_MODE_LEFT_FRONT,
    CTRL_MODE_LEFT_BACK,    
    CTRL_MODE_RIGHT,
    CTRL_MODE_RIGHT_FRONT,
    CTRL_MODE_RIGHT_BACK,
    CTRL_MODE_CHARGE,
    CTRL_MODE_START,
    CTRL_MODE_TEST,
    CTRL_MODE_ERROR,
    CTRL_MODE_PLATE_REDOCK
} CTRL_MODE;

typedef enum
{
    UPLOAD_DATA0 = 0,
    UPLOAD_DATA1,
    UPLOAD_DATA_END
} DATA_TYPE;

#ifndef __GNUC__
#define __attribute__(x)
#endif

// 0xfe
typedef struct
{
    int  leftWhellcode;                    //left Whell code value 左轮码盘值: 0X 04 03 02 01
    int  rightWhellcode;                   //left Whell code value 右轮码盘值: 0X 04 03 02 01
    short yaw;                              //Yaw航向角 short有符号
    short roll;                             //Roll翻滚角
    short pitch;                            //Pitch俯仰角
    short accelerationX;                    //加速度X
    short accelerationY;                    //加速度Y
    short accelerationZ;                    //加速度Z
}__attribute__((packed)) RecvOdomData;

typedef int (*data_callback)(void *data);
// typedef int (*odom_data_callback)(RecvOdomData *odomData);
void hexDump2str(const char *buf, int len, char *destData, int destLen);
// class ChassisPort : Service{
class ChassisPort {
 public:
    ChassisPort(const char* uart_dev, int baud_rate);
    ~ChassisPort();

    void start(ChassisPort * chassisPortIns);
    void stop(void);
    int ReceiveData(unsigned char *data);
    int ParseData(unsigned char *data);
    /*ThreadStatus status(void) {
        if (data_recv_service_)
            return data_recv_service_->status();
        else
            return kThreadRunning;
    }*/
    //cmd control func .....
    bool GetPortStatus() {
        return port_flag;
    }

    int SetPortStatus(bool flag) {
        port_flag = flag;
    }

    int Upstation_Initialized();
    int Feed_Plate_Watchdog();
    int Set_Plate_Sleep();
    int Set_Plate_Wake();
    int Set_Plate_cmd_with_data(unsigned char *data,unsigned char length);
    int Set_Plate_Mode(unsigned char mode);
    int Set_Plate_Run(float left_speed, float right_speed);
    int Set_Plate_Run_VA(double velocity, double angular);
    int Set_TestCount(unsigned int count);

    // data distribute
    void Register_Data_Upload_Callback(DATA_TYPE type,data_callback func);
    // void Register_Odom_Data_Upload_Callback(odom_data_callback func);

 private:
    // func
    int SendData(const char* data, unsigned int  size);

    // data;
    int uart_dev_;
    // prot_flag;
    bool port_flag;

    pthread_mutex_t mutex_uart;
    // Thread::SharedPtr data_recv_service_;
    // Thread::SharedPtr heartbeat_service_;
    // thread_func  data_recv_service_;
    // thread_func  heartbeat_service_;
    
    data_callback data_func[2];
    // odom_data_callback odom_data_func;
    // string status_;
};

} // namespace joyrobot

