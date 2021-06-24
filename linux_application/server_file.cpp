/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-01 15:53:43
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-23 12:06:48
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
#include <sys/types.h>
#include <sys/fcntl.h>

using namespace std;

#define FILE_NAME_MAX_SIZE 512

int tcp_server()
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    
     //创建一个通讯设备
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
    serv_addr.sin_port = htons(6667);
    
    //将sfd绑定到本地的ip地址和端口号
    int rs = bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(rs == -1) {
        perror("bind");
        return -1;
    }
    //设置sockfd为被动监听状态
    listen(serv_sock, 5);
    socklen_t clnt_addr_size = sizeof(clnt_addr);

    //从未决连接队列中取出一个，进行处理
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1) {
        perror("accept");
        return -1;
    }

    //Input the file name  
    char filename[FILE_NAME_MAX_SIZE];  
    bzero(filename, FILE_NAME_MAX_SIZE);  
    printf("Please input the file name you wana to send:");  
    scanf("%s",&filename);  
    getchar();  
  
    while(1) {
        lseek(send_fd, 0L, 0);
        write(clnt_sock, path, sizeof(path));
        length = read(send_fd, buf, sizeof(buf));
        // while(length = read(send_fd, buf, sizeof(buf) > 0))
        // {
            printf("file buf is %s", buf);
            write(clnt_sock, buf, length);
        // }
            
        printf("transfer successful!");
        break;
    }
    // 关闭本次连接
    close(send_fd);
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

int main()
{
    tcp_server();
    return 0;
}