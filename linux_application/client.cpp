/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-27 19:44:47
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-05-27 21:03:02
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <memory>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <time.h>
#include <sys/sem.h>

int tcp_client() {
    struct sockaddr_in serv_addr;
    char buf[128];
    char *msg1 = (char*)"this is a test1\n";
    char *msg2 = (char*)"this is a test2\n";
    char *msg3 = (char*)"this is a test3\n";
    char *msg4 = (char*)"this is a test4\n";
    char *msg5 = (char*)"this is a test5\n";
    char *msg[] = {msg1, msg2, msg3, msg4, msg5};
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
    int i = 0;
    while(1) {     
        //向服务器发送消息
        if (i == 5) {
            i = 0;
        }
        write(clnt_sock, msg[i], strlen(msg[i])+1);
        //阻塞等待服务器的响应消息
        int r = read(clnt_sock,buf,128);
        if(strcmp(buf,"EXIT")==0)
                break;
        //将响应消息输出到显示器
        write(1,buf,r);
        i++;
        // printf("\n");      
    }
    //关闭本次连接
    close(clnt_sock);
}

int main()
{
    tcp_client();
    return 0;
}