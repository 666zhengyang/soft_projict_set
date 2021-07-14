/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-07-14 15:59:21
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-07-14 16:00:36
 */
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "sys/ioctl.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"
#include <poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <fcntl.h>
/*
 * @description		: main主程序
 * @param - argc 	: argv数组元素个数
 * @param - argv 	: 具体参数
 * @return 			: 0 成功;其他 失败
 */
int main(int argc, char *argv[])
{
	int fd;
	char *filename;
	unsigned short databuf[3];
	unsigned short ir, als, ps;
	int ret = 0;

	if (argc != 2) {
		printf("Error Usage!\r\n");
		return -1;
	}

	filename = argv[1];
	fd = open(filename, O_RDWR);
	if(fd < 0) {
		printf("can't open file %s\r\n", filename);
		return -1;
	}

	while (1) {
		ret = read(fd, databuf, sizeof(databuf));
		if(ret == 0) { 			/* 数据读取成功 */
			ir =  databuf[0]; 	/* ir传感器数据 */
			als = databuf[1]; 	/* als传感器数据 */
			ps =  databuf[2]; 	/* ps传感器数据 */
			printf("ir = %d, als = %d, ps = %d\r\n", ir, als, ps);
		}
		usleep(200000); /*100ms */
	}
	close(fd);	/* 关闭文件 */	
	return 0;
}

