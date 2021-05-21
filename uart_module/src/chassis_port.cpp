/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: curry30
 * @Date: 2020-11-17 14:44:15
 * @LastEditors: curry30
 * @LastEditTime: 2021-02-26 15:29:37
 */
#include "chassis_port.h"

// #define CHASSIS_TEST_MODE 1

namespace joyrobot
{

#define MAX_PACKET_SIZE 64
#define PACKET_A_LENGTH 26
#define PACKET_B_LENGTH 28

pthread_t hearbeat_tid;
pthread_t data_recv_tid;

    void hexDump2str(const char *buf, int len, char *destData, int destLen);

    static void *chassis_data_parse(void *arg)
    {
        pthread_detach(pthread_self());
        printf("chassis_data_parse start!\n");
        ChassisPort *chassis_port = (ChassisPort *)arg;
        // ASSERT(chassis_port != NULL);
        // while (kThreadRunning == chassis_port->status())
        int bytes_read = -1;
        while (1 == chassis_port->GetPortStatus())
        {
            unsigned char data[MAX_PACKET_SIZE] = {0};
            bytes_read = chassis_port->ReceiveData(data);
            if (bytes_read > 0)
            {
                // pr_dbg("receive data,read count:%d\n",bytes_read);
                printf("receive data,read count:%d\n", bytes_read);
                // printf("receive data :%s\n", data);
                chassis_port->ParseData(data);
                bytes_read = -1;
            }
        }

        return NULL;
    }

    static void *chassis_hearbeat(void *arg)
    {
        pthread_detach(pthread_self());
        ChassisPort *chassis_port = (ChassisPort *)arg;
        // ASSERT(chassis_port != NULL);
        // while (kThreadRunning == chassis_port->status())
        static bool hearbeat_flag = 1;
        printf("send feed plate watchdog cmd start!\n");
        while (1 == chassis_port->GetPortStatus())
        {
            int ret = -1;
#ifdef CHASSIS_TEST_MODE
            static int count = 1;
            //ret = chassis_port->Feed_Plate_Watchdog();
            ret = chassis_port->Set_TestCount(count);
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            count++;
#else
            ret = chassis_port->Feed_Plate_Watchdog();
            // printf("send feed plate watchdog cmd success!\n");
            //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            //sleep(2); 
            usleep(20 * 1000);
#endif
        }
        return NULL;
    }

    int ChassisPort::SendData(const char *data, unsigned int size)
    {
        int ret = -1;
        pthread_mutex_lock(&mutex_uart);
        ret = uart_send(uart_dev_, data, size);
        pthread_mutex_unlock(&mutex_uart);
        return ret;
    }

    int ChassisPort::ParseData(unsigned char *data)
    {
        unsigned char sum = 0;
        static int count = 0;
        RecvOdomData odomData;

        if (data[0] != 0XFF)
        {
            
            //pr_err("line:%d.Invalid data, 0x%02X\n",__LINE__,data[0]);
            printf("line:%d.Invalid data, 0x%02X\n", __LINE__,data[0] );
            return -1;
        }
        
        // 0xFE 26 byte
        if (data[1] == 0xFE)
        {

            for (int i = 0; i < PACKET_A_LENGTH - 1; i++)
            {
                sum += data[i];
            }

            if (sum != data[PACKET_A_LENGTH - 1])
            {
                //pr_dbg("ParseData fffe data sum compare error.\n");
                printf("ParseData fffe data sum compare error.\n");
                return -1;
            }

            odomData.leftWhellcode = (unsigned int)(data[5] << 24 | data[4] << 16 | data[3] << 8 | data[2]);
            odomData.rightWhellcode = (unsigned int)(data[9] << 24 | data[8] << 16 | data[7] << 8 | data[6]);
            odomData.yaw = (unsigned short)(data[11] << 8 |data[10]);
            odomData.roll = (unsigned short)(data[13] << 8 | data[12]);
            odomData.pitch = (unsigned short)(data[15] << 8 | data[14]);
            odomData.accelerationX = (unsigned short)(data[17] << 8 | data[16]);
            odomData.accelerationY = (unsigned short)(data[19] << 8 | data[18]);
            odomData.accelerationZ = (unsigned short)(data[21] << 8 | data[20]);

#ifdef CHASSIS_TEST_MODE
            unsigned int count = int(data[24] << 16 | data[23] << 8 | data[22]);
            if(count <= 0)
                //pr_dbg("chassis port get data != send data\n");
            //pr_dbg("rec: count:%d\n",count);
#endif
            odomData.rightWhellcode = 12345;
            odomData.leftWhellcode = 23456;
            odomData.roll = 33;
            odomData.yaw = 44;
            odomData.pitch = 55;
            odomData.accelerationX = 77;
            odomData.accelerationY = 88;
            odomData.accelerationZ = 99;

            if (data_func[UPLOAD_DATA0] != NULL)
            {
                data_func[UPLOAD_DATA0]((void *)&odomData);
            }

        } else if (data[1] == 0xFF) {
            for (int i = 0; i < PACKET_B_LENGTH - 1; i++)
            {
                sum += data[i];
            }

            if (sum != data[PACKET_B_LENGTH - 1])
            {
                //pr_dbg("ParseData ffff data sum compare error.\n");
                printf("ParseData ffff data sum compare error.\n");
                return -1;
            }

            if (data_func[UPLOAD_DATA1] != NULL)
            {
                data_func[UPLOAD_DATA1](data);
            }

        } else {
            //pr_err("line:%d.Invalid data, 0x%02X\n", __LINE__,data[1]);
            printf("ParseData fffe data sum compare error.\n");
            return -1;
        }

        count += 1;
        // pr_dbg("aleady get count:%d\n", count);
        // pr_dbg("Receive a data: %s\n", data);

        printf ("aleady get count:%d\n", count);
        //printf ("Receive a data: %s\n", data);
        return 0;
    }

    int ChassisPort::ReceiveData(unsigned char *data)
    {
        int bytes_read = -1;
       // unsigned char buffer[MAX_PACKET_SIZE] = {0};
        unsigned char sum = 0;

        if (data == NULL) {
            // pr_err("error:%s,%d",__func__,__LINE__);
            printf("error:%s,%d",__func__,__LINE__);
            return -1;
        }

        bytes_read = uart_recv(uart_dev_, &data[0], 1, 20);

        if (bytes_read <= 0)
        {
            ////pr_dbg("can't get uart data\n");
            printf("can't get uart data\n");
            return bytes_read;
        }

        if (data[0] == 0xff)
        {
            bytes_read = -1;
            bytes_read = uart_recv(uart_dev_, &data[1], 1, 20);
            if (bytes_read >=1) {
                if (data[1] == 0xfe)
                {
                    bytes_read = -1;
                    bytes_read = uart_recv(uart_dev_, &data[2], (PACKET_A_LENGTH - 2), 20);
                    if (bytes_read < (PACKET_A_LENGTH - 2))
                    {
                        // bzero(&buffer[0], sizeof(buffer));
                       // pr_info("fffe can't get enough data.read %d bytes,try again!\n",bytes_read);
                       // bzero(&buffer[0], sizeof(buffer));
                       // printf("fffe can't get enough data.read %d bytes,try again!\n",bytes_read);
                        int ret = -1;
                        ret = uart_recv(uart_dev_, &data[2 + bytes_read], (PACKET_A_LENGTH - 2) - bytes_read, 20);
                        if((bytes_read + ret) != (PACKET_A_LENGTH - 2) )
                        {
                            //pr_err("fffe can't get enough data.total %d bytes!\n",bytes_read + ret);
                            printf("fffe can't get enough data.total %d bytes!\n",bytes_read + ret);
                            return -1;
                        }

                    }

                    for (int i = 0; i < PACKET_A_LENGTH -1; i++)
                    {
                        sum += data[i];
                    }

                    if (sum != data[PACKET_A_LENGTH - 1])
                    {
                        //pr_err("fffe head data sum compare error.sum:%02X,data:%02X\n",
                            // sum, data[PACKET_A_LENGTH-1]);
                        printf("fffe head data sum compare error.sum:%02X,data:%02X\n",
                             sum, data[PACKET_A_LENGTH-1]);
                        return -1;
                    }

                    for (int i = 0; i < PACKET_A_LENGTH ; i++)
                    {
                       if (i == 0) {
                           printf("the fffe type data is: ");    
                       }
                       printf("%02X ",data[i]);
                       if (i == PACKET_A_LENGTH - 1) {
                           printf("\n");
                       }
                    }
                } else if (data[1] == 0xff) {
                    bytes_read = -1;
                    bytes_read = uart_recv(uart_dev_, &data[2], (PACKET_B_LENGTH - 2), 20);
                    if (bytes_read < (PACKET_B_LENGTH - 2))
                    {
                        // pr_info("ffff can't get enough data.read %d bytes,try again!\n",bytes_read);
                       // printf("ffff can't get enough data.read %d bytes,try again!\n", bytes_read);
                        int ret = -1;
                        ret = uart_recv(uart_dev_, &data[2 + bytes_read], (PACKET_B_LENGTH - 2) - bytes_read, 20);
                        bytes_read += ret;
                        if(bytes_read != (PACKET_B_LENGTH - 2))
                        {
                            //pr_err("ffff can't get enough data.total %d bytes!\n",bytes_read + ret);
                            printf("ffff can't get enough data.total %d bytes!\n",bytes_read + ret);
                            return -1;
                        }
                    }
                    printf("bytes_read is %d \n", bytes_read);
                    for (int i = 0; i < PACKET_B_LENGTH - 1; i++)
                    {
                        sum += data[i];
                    }

                    for (int i = 0; i < PACKET_B_LENGTH ; i++)
                    {
                       if (i == 0) {
                           printf("the ffff type data is: ");    
                       }
                       printf("%02X ",data[i]);
                       if (i == PACKET_B_LENGTH - 1) {
                           printf("\n");
                       }
                    }

                    if (sum != data[PACKET_B_LENGTH - 1])
                    {
                        //pr_err("ffff head data sum compare error.sum:%02X,data:%02X\n",
                           // sum, data[PACKET_B_LENGTH-1]);
                        printf ("ffff head data sum compare error.sum:%02X,data:%02X\n",sum, data[PACKET_B_LENGTH-1]);
                        return -1;
                    }
                } else {
                    //pr_err("can't get correct head 0x%02X%02X\n",data[0],data[1]);
                    printf("can't get correct head 0x%02X%02X\n",data[0], data[1]);
                    return -1;
                }
            } else {
                //pr_err("can't get enough head.[%02X]\n", data[0]);
                printf("can't get enough head.[%02X]\n", data[0]);
                return -1;
            }
        } else {
            //pr_err("invalid head 0x%02X\n",data[0]);
            printf("invalid head 0x%02X\n",data[0]);
            return -1;
        }

        if (0)//(data[1] == 0xff)
        {
            char *debugInfo = new char[MAX_PACKET_SIZE * 20];
            hexDump2str((char *)data, MAX_PACKET_SIZE, debugInfo, MAX_PACKET_SIZE * 20);
            //pr_info("<--------------stm32 come data:\n%s", debugInfo);
           // pr_info("\n");
            delete[] debugInfo;
        }
        return bytes_read + 2;
    }

    ChassisPort::ChassisPort(const char *uart_dev, int baud_rate)
    {
        uart_dev_ = -1;
        uart_dev_ = uart_open(uart_dev, baud_rate);
        // mutex_uart = PTHREAD_MUTEX_INITIALIZER;
        pthread_mutex_init(&mutex_uart, NULL);
        // ASSERT(uart_dev_ >= 0);
    }

    ChassisPort::~ChassisPort()
    {
        if (uart_dev_ >= 0)
        {
            uart_close(uart_dev_);
            uart_dev_ = -1;
        }
        // data_recv_service_->join();
        // pthread_join(hearbeat_tid, NULL);
        pthread_mutex_destroy(&mutex_uart);
        printf("test end!\n");
    }

    void ChassisPort::start(ChassisPort * chassisPortIns)
    {
        Upstation_Initialized();  // send init cmd to chassis
        printf("Upstation_Initialized init sucess!\n");
        SetPortStatus(1);
        pthread_create(&hearbeat_tid, NULL, chassis_hearbeat, chassisPortIns);
        // printf("pthread_create create sucess!\n");
        pthread_create(&data_recv_tid, NULL, chassis_data_parse, chassisPortIns);
        //  heartbeat_service_ = std::make_shared<Thread>("cha_hearbeat", chassis_hearbeat, this,0);
        // data_recv_service_ = std::make_shared<Thread>("chassis_port", chassis_data_parse, this,0);
        sleep(60);
    }

    void ChassisPort::stop(void)
    {
        SetPortStatus(0);
        pthread_join(data_recv_tid, NULL);
        // data_recv_service_->set_status(kThreadStopping);
    }

    int ChassisPort::Upstation_Initialized()
    {
        int ret = -1;
        unsigned char cmd_string_start[8] = {0XFF, 0XFC, 0XCC, 0XFF, 0XFF, 0XFF, 0XFF, 0x00};
        int length = sizeof(cmd_string_start) / sizeof(cmd_string_start[0]);
        for (int i = 0; i < (length - 1); i++)
        {
            cmd_string_start[length - 1] += cmd_string_start[i];
        }
        ret = SendData((const char *)cmd_string_start, length);
        if (ret == length)
        {
            return 0;
        }
        return -1;
    }

    int ChassisPort::Feed_Plate_Watchdog() //heartbeat
    {
        int ret = -1;
        unsigned char cmd_string_feed_plate_watchdog[8] = {0XFF, 0XFC, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0x00};
        int length = sizeof(cmd_string_feed_plate_watchdog) / sizeof(cmd_string_feed_plate_watchdog[0]);
        for (int i = 0; i < (length - 1); i++)
        {
            cmd_string_feed_plate_watchdog[length - 1] += cmd_string_feed_plate_watchdog[i];
        }
        ret = SendData((const char *)cmd_string_feed_plate_watchdog, length);
        if (ret == length)
        {
            return 0;
        }
        return -1;
    }

    int ChassisPort::Set_Plate_Sleep()
    {
        int ret = -1;
        unsigned char cmd_string_plate_sleep[] = {0XFF, 0XFC, 0XBB, 0XDD, 0XFF, 0XFF, 0XFF, 0x00};
        int length = sizeof(cmd_string_plate_sleep) / sizeof(cmd_string_plate_sleep[0]);
        for (int i = 0; i < (length - 1); i++)
        {
            cmd_string_plate_sleep[length - 1] += cmd_string_plate_sleep[i];
        }
        ret = SendData((const char *)cmd_string_plate_sleep, length);
        if (ret == length)
        {
            return 0;
        }
        return -1;
    }

    int ChassisPort::Set_Plate_Wake()
    {
        int ret = -1;
        unsigned char cmd_string_plate_sleep[] = {0XFF, 0XFC, 0XBB, 0XDD, 0X00, 0XFF, 0XFF, 0x00};
        int length = sizeof(cmd_string_plate_sleep) / sizeof(cmd_string_plate_sleep[0]);
        for (int i = 0; i < (length - 1); i++)
        {
            cmd_string_plate_sleep[length - 1] += cmd_string_plate_sleep[i];
        }
        ret = SendData((const char *)cmd_string_plate_sleep, length);
        if (ret == length)
        {
            return 0;
        }
        return -1;
    }

    int ChassisPort::Set_Plate_cmd_with_data(unsigned char *data,unsigned char length)
    {
        int ret = -1;

        ret = SendData((const char *)data, length);
        if (ret == length)
        {
            return 0;
        }
        return -1;
    }

    int ChassisPort::Set_Plate_Mode(unsigned char mode)
    {
        int length = 0;
        int ret = -1;
        unsigned char  cmd_string_start[8] = {0XFF, 0XFC, 0XBB, 0XAA, 0XFF, 0XFF, 0XFF, 0x00};
        unsigned char  cmd_string_stop[8] = {0XFF, 0XFC, 0XBB, 0X00, 0XFF, 0XFF, 0XFF, 0x00};  //暂停工作,收到指令后，风机、中刷电机、边扫电机全部关闭，传感器等不关闭，暂停状态等待用户操作。
        unsigned char  cmd_string_charge[8] = {0xFF, 0xFC, 0XBB, 0xFF, 0xFF, 0xFF, 0xFF, 0x00}; //回充电座:收到该指令后，底盘开始回充电座。


        if (mode == CTRL_MODE_STOP)
        {
            //command_type = COMMAND_STOP;
            length = sizeof(cmd_string_stop) / sizeof(cmd_string_stop[0]);
            for (int i = 0; i < (length - 1); i++)
            {
                cmd_string_stop[length - 1] += cmd_string_stop[i];
            }
            ret = SendData((const char *)cmd_string_stop, length);
        }
        else if (mode == CTRL_MODE_START)
        {
            length = sizeof(cmd_string_start) / sizeof(cmd_string_start[0]);
            for (int i = 0; i < (length - 1); i++)
            {
                cmd_string_start[length - 1] += cmd_string_start[i];
            }
            ret = SendData((const char *)cmd_string_start, length);
        }
        else if (mode == CTRL_MODE_FRONT)
        {
            Set_Plate_Run(200, 200);
        }
        else if (mode == CTRL_MODE_BACK)
        {
            Set_Plate_Run(-100, -100);
        }
        else if (mode == CTRL_MODE_LEFT)
        {
            Set_Plate_Run(-200, 200);
        }       
        else if (mode == CTRL_MODE_RIGHT)
        {
            Set_Plate_Run(200, 100);
        }
        else if (mode == CTRL_MODE_LEFT_FRONT)
        {
            Set_Plate_Run(200, 100);
        } 
        else if (mode == CTRL_MODE_RIGHT_FRONT)
        {
            Set_Plate_Run(200, -200);
        }
        else if (mode == CTRL_MODE_LEFT_BACK)
        {
            Set_Plate_Run(100, -200);
        } 
        else if (mode == CTRL_MODE_RIGHT_BACK)
        {
            Set_Plate_Run(-200, -100);
        } 
        else if (mode == CTRL_MODE_PAUSE)
        {
            Set_Plate_Run(0, 0);
        }
        else if (mode == CTRL_MODE_CHARGE)
        {
            length = sizeof(cmd_string_charge) / sizeof(cmd_string_charge[0]);
            for (int i = 0; i < (length - 1); i++)
            {
                cmd_string_charge[length - 1] += cmd_string_charge[i];
            }
            ret = SendData((const char *)cmd_string_charge, length);
        }
        if (ret == length)
        {
            return 0;
        }
        return -1;
    }

    int ChassisPort::Set_Plate_Run(float left_speed, float right_speed)
    {
        unsigned char  out_cmd[8];
        unsigned char  length = 0;
        short left_speed_int = 0;
        short right_speed_int = 0;
        int ret = -1;
        left_speed_int = (int)(left_speed * 14);
        right_speed_int = (int)(right_speed * 14);

        if (left_speed_int > 420)
        {
            left_speed_int = 420;
        }
        else if (left_speed_int < -420)
        {
            left_speed_int = -420;
        }
        if (right_speed_int > 420)
        {
            right_speed_int = 420;
        }
        else if (right_speed_int < -420)
        {
            right_speed_int = -420;
        }

        out_cmd[0] = (char)0xFF;
        out_cmd[1] = (char)0xFC;
        out_cmd[2] = (char)0xAA;
        out_cmd[3] = (char)(0xFF & left_speed_int);
        out_cmd[4] = (char)(0xFF & (left_speed_int >> 8));
        out_cmd[5] = (char)(0xFF & right_speed_int);
        out_cmd[6] = (char)(0xFF & (right_speed_int >> 8));
        out_cmd[7] = 0;

        length = sizeof(out_cmd) / sizeof(out_cmd[0]);
        for (int i = 0; i < (length - 1); i++)
        {
            out_cmd[length - 1] += out_cmd[i];
        }
        ret = SendData((const char *)out_cmd, length);
        if (ret == length)
        {
            return 0;
        }
        return -1;
    }

    int ChassisPort::Set_Plate_Run_VA(double velocity, double angular)
    {
        unsigned char out_cmd[8];
        unsigned char length = 0;
        short left_speed_int = 0;
        short right_speed_int = 0;
        int ret = -1;

        // auto left_velocity = (short) ((velocity - 0.5 * angular * WHEEL_TRACK) * 1000.0);
        // auto right_velocity = (short) ((velocity + 0.5 * angular * WHEEL_TRACK) * 1000.0);
        int left_velocity = (short) ((velocity - 0.5 * angular * WHEEL_TRACK) * 1000.0);
        int right_velocity = (short) ((velocity + 0.5 * angular * WHEEL_TRACK) * 1000.0);
        out_cmd[0] = (char)0xFF;
        out_cmd[1] = (char)0xFC;
        out_cmd[2] = (char)0xAA;
        out_cmd[3] = (char)(left_velocity & 0xff);
        out_cmd[4] = (char)((left_velocity >> 8) & 0xff);
        out_cmd[5] = (char)((right_velocity & 0xff));
        out_cmd[6] = (char)((right_velocity >> 8) & 0xff);
        out_cmd[7] = 0;

        length = sizeof(out_cmd) / sizeof(out_cmd[0]);

        for (int i = 0; i < (length - 1); i++)
        {
            out_cmd[length - 1] += out_cmd[i];
        }

        ret = SendData((const char *)out_cmd, length);

        if (ret == length)
        {
            return 0;
        }
        return -1;
    }

    int ChassisPort::Set_TestCount(unsigned int count)
    {
        unsigned char out_cmd[8];
        unsigned char length = 0;
        int ret = -1;

        out_cmd[0] = (char)0xFF;
        out_cmd[1] = (char)0xFC;
        out_cmd[2] = (char)0XEE;
        out_cmd[3] = (char)(count & 0xff);
        out_cmd[4] = (char)((count >> 8) & 0xff);
        out_cmd[5] = (char)(((count >> 16) & 0xff));
        out_cmd[6] = 0;
        out_cmd[7] = 0;
#ifdef CHASSIS_TEST_MODE
        //pr_dbg("send count: %d\n",count);
#endif
        length = sizeof(out_cmd) / sizeof(out_cmd[0]);
        for (int i = 0; i < (length - 1); i++)
        {
            out_cmd[length - 1] += out_cmd[i];
        }
        ret = SendData((const char *)out_cmd, length);
        if (ret == length)
        {
            return 0;
        }
        return -1;
    }


// 0 odomdata_uploadfunc  1 sensor_uploadfunc
void ChassisPort::Register_Data_Upload_Callback(DATA_TYPE type, data_callback func)
    {
        if (type >= UPLOAD_DATA0 && type < UPLOAD_DATA_END && func != NULL)
        {
            data_func[type] = func;
        }
    }

/*----------------------------------------------------------------
【函数介绍】: 格式化字节为16进制
【入口参数】: buf 源字符数组
			  len 源字符数组buf的长度 
【返回  值】: 返回对应的十六进制的值 
【出口参数】: destData 目标数组
			  destLen  目标数组destData的长度
-----------------------------------------------------------------*/
    void hexDump2str(const char *buf, int len, char *destData, int destLen)
    {
        if (len < 1 || buf == NULL)
            return;

        const char *hexChars = "0123456789ABCDEF";
        int i = 0;
        char c = 0x00;
        char str_print_able[17];
        char str_hex_buffer[16 * 3 + 1];
        char str_line_buffer[6 + (16 * 3 + 1) + 18 + 10]; //每行:6个序号 + hex + 18个ascii字符+1回车

        memset(destData, 0, destLen);

        for (i = 0; i < (len / 16) * 16; i += 16)
        {
            memset(str_line_buffer, 0, sizeof(str_line_buffer));
            int j = 0;
            for (j = 0; j < 16; j++)
            {
                c = buf[i + j];

                // hex
                int z = j * 3;
                str_hex_buffer[z++] = hexChars[(c >> 4) & 0x0F];
                str_hex_buffer[z++] = hexChars[c & 0x0F];
                str_hex_buffer[z++] = (j < 10 && !((j + 1) % 8)) ? '_' : ' ';

                // string with space repalced
                if (c < 32 || c == '\0' || c == '\t' || c == '\r' || c == '\n' || c == '\b')
                    str_print_able[j] = '.';
                else
                    str_print_able[j] = c;
            }
            str_hex_buffer[16 * 3] = 0x00;
            str_print_able[j] = 0x00;

           //*** sprintf(str_line_buffer, "%04x  %s %s\n", i, str_hex_buffer, str_print_able);
            sprintf(str_line_buffer, "%04x  %s %s\n", i, str_hex_buffer, str_print_able);
            strcat(destData, str_line_buffer);
            if (strlen(destData) > destLen)
                return;
        }

        // 处理剩下的不够16字节长度的部分
        int leftSize = len % 16;
        if (leftSize < 1)
            return;
        int j = 0;
        int pos = i;
        for (; i < len; i++)
        {
            c = buf[i];

            // hex
            int z = j * 3;
            str_hex_buffer[z++] = hexChars[(c >> 4) & 0x0F];
            str_hex_buffer[z++] = hexChars[c & 0x0F];
            str_hex_buffer[z++] = ' ';

            // string with space repalced
            if (c < 32 || c == '\0' || c == '\t' || c == '\r' || c == '\n' || c == '\b')
                str_print_able[j] = '.';
            else
                str_print_able[j] = c;
            j++;
        }
        str_hex_buffer[leftSize * 3] = 0x00;
        str_print_able[j] = 0x00;

        //   printf("last line leftSize of buf %d\n", leftSize);
        for (j = leftSize; j < 16; j++)
        {
            int z = j * 3;
            str_hex_buffer[z++] = ' ';
            str_hex_buffer[z++] = ' ';
            str_hex_buffer[z++] = ' ';
        }
        str_hex_buffer[16 * 3] = 0x00;
        //	printf("left buf:%s\n", str_hex_buffer);
        //***  snprintf(str_line_buffer, sizeof(str_line_buffer), "%04x  %s %s\n", pos, str_hex_buffer, str_print_able);
        snprintf(str_line_buffer, sizeof(str_line_buffer), "%04x  %s %s\n", pos, str_hex_buffer, str_print_able);
        strncat(destData, str_line_buffer, sizeof(str_line_buffer));
    }
} // namespace joyrobot

