/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-29 14:03:55
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-29 14:07:51
 */
#ifndef _BSP_KEY_H
#define _BSP_KEY_H
#include "imx6ul.h"

/* 定义按键值 */
enum keyvalue{
	KEY_NONE   = 0,
	KEY0_VALUE,
	KEY1_VALUE,
	KEY2_VALUE,
};

/* 函数声明 */
void key_init(void);
int key_getvalue(void);


#endif
