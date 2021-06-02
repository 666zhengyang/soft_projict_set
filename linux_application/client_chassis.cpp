/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-27 19:44:47
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-01 16:38:49
 */
#include "client_chassis.h"

static int clnt_sock;
static bool state = false;

int tcp_client_init()
{
    struct sockaddr_in serv_addr;
    //创建一个socket设备
    clnt_sock = socket(AF_INET,SOCK_STREAM, 0);
    if (clnt_sock == -1) {
        perror("socket");
        return -1;
    }
    //需要初始化serv
    char *ip = (char *)"192.168.1.126";
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(6666);
    int c =  -1;
    //在socket上发起连接向服务器
    while (c==-1) {
        c = connect(clnt_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        usleep(1000);
    }
    state = true;
}

int tcp_client() {
    if (state == true) {
        char buf[128];
        char *msg = (char*)"this is a info from client\n";
        write(clnt_sock, msg, strlen(msg)+1);
    } 
}

int tcp_client_deinit()
{
    close(clnt_sock);
}
