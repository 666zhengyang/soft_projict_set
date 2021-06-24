/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-27 19:44:47
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-23 11:43:09
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
#include <sys/types.h>
#include <sys/fcntl.h>

int tcp_client() {
    int send_fd;
    struct sockaddr_in serv_addr;
    char buf[1024];
    // 创建一个socket设备
    int clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (clnt_sock == -1) {
        perror("socket");
        return -1;
    }
    //  需要初始化serv
    char *ip = (char *)"192.168.1.161";
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    //  serv_addr.sin_addr.s_addr = htonl(ip);
    serv_addr.sin_port = htons(6667);
    //  在socket上发起连接向服务器
    int c = connect(clnt_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (c==-1) {
        perror("connect!");
        return -1;
    }
    // int i = 0;
    char file[30];
    int length, target;
    while (1) {   
        while (length = read(clnt_sock, file, sizeof(file)) > 0);
        if (strstr(file, ".txt") != NULL) {
            target = open(file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
            if (target <= 0) {
                perror("open failed!");
            }
        }  
        while(length = read(clnt_sock, buf, sizeof(buf)) > 0)
        write(target, buf, length); 
        printf("creat file successful!");
        break;
    }

    // 关闭本次连接
    close(clnt_sock);
    close(target);
}

int main()
{
    tcp_client();
    return 0;
}