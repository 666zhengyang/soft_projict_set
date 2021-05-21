/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: curry30
 * @Date: 2020-11-24 14:54:22
 * @LastEditors: curry30
 * @LastEditTime: 2021-02-26 11:42:50
 */

#define TAG "uart"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

//#include <adk/utils/logger.h>

int uart_open (const char* dev, int speed)
{
    int fd;
    int ret = -1;
    
    if ((fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
    {
        //pr_err("open %s is failed\n",dev);
        printf("open %s is failed\n", dev);
    } else {
        //pr_dbg("open %s is success\n",dev);
        printf("open %s is success\n",dev);
        ret = fcntl(fd, F_SETFL, FNDELAY);
        if (ret < 0) {
            //pr_err("uart_open ==> error code = %d\n", ret);
            printf("uart_open ==> error code = %d\n", ret);
            return ret;
        } else {
            //pr_dbg("uart_open ==> ret = %d\n", ret);
            printf("uart_open ==> ret = %d\n", ret);
        }
        uart_set_opt(fd, speed, 8, 'N', 1);
    }

    return fd;
}

void uart_close(int fd)
{
    close(fd);
}

int uart_set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;

    if (tcgetattr(fd, &oldtio) !=  0) {
        //pr_err("tcgetattr error\n");
        return -1;
    }
    memset(&newtio, 0, sizeof(newtio));

    newtio.c_cflag  |=  CLOCAL | CREAD;

    newtio.c_cflag &= ~CSIZE;
    switch(nBits)
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch(nEvent)
    {
    case 'O':
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }

    switch(nSpeed)
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }

    if (nStop == 1)
        newtio.c_cflag &=  ~CSTOPB;
    else if (nStop == 2)
        newtio.c_cflag |=  CSTOPB;

    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;

    tcflush(fd, TCIFLUSH);
    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) {
        //pr_err("com set error\n");
        return -1;
    }

    return 0;
}

/*
  ssize_t write(int fd,const void*buf,size_t count);
    参数说明：
  fd:是文件描述符（write所对应的是写，即就是1）
  buf:通常是一个字符串，需要写入的字符串
  count：是每次写入的字节数
*/
int uart_send(int fd, const char* buf, int len)
{
    int ret = 0;
    int count = 0;
    while (len > 0) {
        ret = write(fd, (char*)buf + count, len);
        if (ret < 1)
            break;
        count += ret;
        len = len - ret;
    }
    return count;
}

/*
ssize_t read(int fd,void*buf,size_t count)
参数说明：
fd:      是文件描述符
buf:     为读出数据的缓冲区；
count:   为每次读取的字节数（是请求读取的字节数，读上来的数据保
         存在缓冲区buf中，同时文件的当前读写位置向后移）
*/

/*
timeval
{
    time_t tv_sec;  //秒 [long int]
    suseconds_t tv_usec;  //微秒 [long int]
}*/

int uart_recv(int fd, unsigned char* buf, int len, int timeout_ms)
{
    fd_set rset;
    int ret;
    struct timeval t;

    FD_ZERO(&rset);
    FD_SET(fd, &rset);
    if (timeout_ms > 0) {
        t.tv_sec = 0;
        t.tv_usec = timeout_ms * 1000;//10ms
        ret = select(fd + 1, &rset, NULL, NULL, &t);
    } else {
        ret = select(fd + 1, &rset, NULL, NULL, NULL);
    }

    if (ret <= 0) {
        //pr_warn("Select uart device timeout ,error=%d\n", errno);
        return 0;
    } else {
        ret = read(fd, (unsigned char *)buf, len);
        return ret;
    }
}