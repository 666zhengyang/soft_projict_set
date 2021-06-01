/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-27 19:44:47
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-01 16:13:17
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

int tcp_client() {
    struct sockaddr_in serv_addr;
    char buf[128];
    char *msg = (char*)"this is a info from client\n";
    //创建一个socket设备
    int clnt_sock = socket(AF_INET,SOCK_STREAM,0);
    if (clnt_sock == -1) {
        perror("socket");
        return -1;
    }
    //需要初始化serv
    char *ip = (char *)"192.168.1.126";
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    // serv_addr.sin_addr.s_addr = htonl(ip);
    serv_addr.sin_port = htons(6666);
    //在socket上发起连接向服务器
    int c = connect(clnt_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (c==-1) {
        perror("connect");
        return -1;
    }
    //int i = 0;
    // while(1) {     
        write(clnt_sock, msg, strlen(msg)+1);
        //阻塞等待服务器的响应消息
        int r = read(clnt_sock,buf,128);
        if(strcmp(buf,"EXIT")==0)
               //  break;
        //将响应消息输出到显示器
        // write(1,buf,r);
       // i++;
        // printf("\n");      
    // }
    //关闭本次连接
    close(clnt_sock);
}

int main()
{
    tcp_client();
    return 0;
}