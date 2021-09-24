/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-27 19:44:47
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-08-12 17:15:08
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
#include <time.h>

long long get_time_of_ns()
{
    struct timespec time_now = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &time_now);
    long long time_ns = time_now.tv_sec*1e9 + time_now.tv_nsec;
}

typedef struct Data {
    int list[10]; // 数据
    long long currentTime; // 当前时间戳
}Data;

int tcp_client() {
    Data data;
    int list[10] = {11,12,13,14,15,16,17,18,19,20};
    for (int i = 0; i < 10; i++) {
        data.list[i] = list[i];
    }
    data.currentTime = get_time_of_ns();
    
    struct sockaddr_in serv_addr;
    char buf[1024];
        // 创建一个socket设备
    int clnt_sock = socket(AF_INET,SOCK_STREAM,0);
    if (clnt_sock == -1) {
        perror("socket");
        return -1;
    }
        // 需要初始化serv
    char *ip = (char *)"192.168.1.126";
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
        // serv_addr.sin_addr.s_addr = htonl(ip);
    serv_addr.sin_port = htons(6666);
        // 在socket上发起连接向服务器
    int c = connect(clnt_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (c==-1) {
        perror("connect");
        return -1;
    }
        // int i = 0;
    while(1) {   
        data.currentTime = get_time_of_ns();  
        // printf("data->currentTime:%lld\n", data.currentTime);
        write(clnt_sock, (void*)&data, sizeof(Data));
        // 阻塞等待服务器的响应消息
        // int r = read(clnt_sock,buf,128);
        // if(strcmp(buf,"EXIT")==0)
        // break;
        // 将响应消息输出到显示器
        // write(1,buf,r);
        // i++;
        // printf("\n");      
    }
        // 关闭本次连接
    close(clnt_sock);
}

int main()
{
    tcp_client();
    return 0;
}