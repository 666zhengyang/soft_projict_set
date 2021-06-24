/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-10 12:19:46
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-10 18:12:15
 */
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>


int main(char argc, char * argv[])
{    
    int fd;
    int ret;
    char buf[64];
    char rcvbuf[64];
    
    char *dev_path = "/dev/hello";
    
    fd = open(dev_path, O_RDWR);
    if (fd < 0)
    {
        perror("fail to open file");
        return -1;
    }
    
    /* read data */
    ret = read(fd, buf, sizeof(buf));
    if (ret < 0)
    {
        printf("read err!");
        return -1;
    }
    printf("buf = %s\n", buf);
    
    char bufsnd[64] = "hello keneral!";
    /* write data */
    ret = write(fd, bufsnd, sizeof(bufsnd));
    if (ret < 0)
    {
        printf("read err!");
        return -1;
    }
    
    /* read data */
    ret = read(fd, rcvbuf, sizeof(rcvbuf));
    if (ret < 0)
    {
        printf("read err!");
        return -1;
    }
    printf("rcvbuf = %s\n", rcvbuf);
    
    close(fd);
    return 0;
}
