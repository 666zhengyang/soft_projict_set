/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-01 15:53:43
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-08-09 11:39:02
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

typedef struct Data {
    int list[10];//数据
    long long currentTime;//当前时间戳
}Data;

int tcp_server()
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    
    // char message[] = "Hello World!";
    char buf[sizeof(Data)] = {};
    Data* data;
    
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

        //获取客户端的请求数据
        // int r=read(clnt_sock, buf,128);
        int r = read(clnt_sock, (void*)buf, sizeof(Data));
        if (r > 0)
        {
            
            data = (Data* )buf;
            printf("data->list:"); 
            for (int i = 0; i < 10; i++) {
                 printf("%d", data->list[i]);
            }
            printf("\n"); 
            printf("data->currentTime:%lld\n", data->currentTime);

        }
        memset(data, 0, sizeof(Data));   

        // 处理获取到的数据，将客户发送过来的字符串转换为大写
        /*
            int i;
            for(i=0;i<r;i++)
                buf[i]=toupper(buf[i]);
            write(1,buf,r);
        */
        
        // 响应给客户
        // write(clnt_sock,buf,r);

    }
    // 关闭本次连接
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

int main()
{
    tcp_server();
    return 0;
}