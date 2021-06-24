/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-11 17:18:11
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-11 17:19:16
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    if(argc != 4)  //因为要操作三个LED，如果传入的参数不是四个，程序打印帮助信息
    {
        printf("The count of arguments is wrong\nUsage: \n");
        printf("%s LED1_state LED2_state LED3_state\n", argv[1]);
        printf("\t%s 1 0 1\n means: turn on the LED1 and LED3; turn off the LED2", argv[1]);

        return -1;
    }

    int fd = open("/dev/seventh_driver", O_RDWR);  //打开驱动文件
    if(fd < 0){
        printf("open ERROR\n");
        return -2;
    }

    printf("open successfully. the file description is %d\n", fd);  


        //参数处理
    int val[3]; 
    int i = 0;
    for(;i < argc - 1; i++)
    {
        val[i] = strcmp(argv[i + 1], "0") == 0? 1: 0;   //直接使用字符串比较，把对应参数转换为int类型
        
        printf("LED %d : %d", i ,val[i]);
    }
        printf("\n");

        //将处理好的参数写入到设备文件（调用驱动程序的write函数）
    write(fd, val, 12); 
    
    return 0;
}