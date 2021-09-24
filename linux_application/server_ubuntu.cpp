/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-01 15:53:43
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-08-09 11:41:13
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

using namespace std;

typedef struct
{
    uint8_t irleft_homecode;               //保险杠左接收头
    uint8_t irright_homecode;              //保险杠右接收头
    uint8_t irfl_homecode;                  //正前方左接收头
    uint8_t irfr_homecode;                  //正前方右接收头
    uint16_t left_ground_detect;            //左地检
    uint16_t lm_ground_detect;              //左中地检
    uint16_t rm_ground_detect;              //右中地检
    uint16_t right_ground_detect;           //右地检
    uint16_t forward_look;                  //前视信号
    uint16_t right_wall;                    //右沿墙信号
    uint8_t  ir_signal;                     //红外信号
}ChassisSignal;

ChassisSignal* signal_data;

int tcp_server()
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    
    // char message[] = "Hello World!";
    char buf[sizeof(ChassisSignal)] = {};
    
    // 创建一个通讯设备
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) 
    {
        cout << "serv_sock create failed" << endl;
        perror("socket");
        return -1;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(6666);
    
    //将sfd绑定到本地的ip地址和端口号
    int rs = bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(rs == -1){
        perror("bind");
        return -1;
    }
    //设置sockfd为被动监听状态
    listen(serv_sock,5);
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    //从未决连接队列中取出一个，进行处理
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1){
        perror("accept");
        return -1;
    }

    while(1) {
        // 获取客户端的请求数据
        int r = read(clnt_sock, (void*)buf, sizeof(ChassisSignal));
        if (r > 0) {
            signal_data = (ChassisSignal* )buf;
            printf("ChassisSignal.irleft_homecode is %d ! \n", signal_data->irleft_homecode);
            printf("ChassisSignal.irright_homecode is %d ! \n", signal_data->irright_homecode);
            printf("ChassisSignal.irfl_homecode is %d ! \n", signal_data->irfl_homecode);
            printf("ChassisSignal.irfr_homecode is %d ! \n", signal_data->irfr_homecode);
            printf("ChassisSignal.left_ground_detect is %d ! \n", signal_data->left_ground_detect);
            printf("ChassisSignal.lm_ground_detect is %d ! \n", signal_data->lm_ground_detect);
            printf("ChassisSignal.rm_ground_detect is %d ! \n", signal_data->rm_ground_detect);
            printf("ChassisSignal.right_ground_detect is %d ! \n", signal_data->right_ground_detect);
            printf("ChassisSignal.forward_look is %d ! \n", signal_data->forward_look);
            printf("ChassisSignal.right_wall is %d ! \n", signal_data->right_wall);
            printf("ChassisSignal.ir_signal is %d ! \n", signal_data->ir_signal);
            // 响应给客户
            // write(clnt_sock,buf,r); 
        }
        memset(signal_data, 0 , sizeof(ChassisSignal));
    }
    //关闭本次连接
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

int main()
{
    tcp_server();
    return 0;
}