/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-29 10:01:44
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-29 10:02:51
 */
#ifndef __BSP_LED_H
#define __BSP_LED_H
#include "imx6ul.h"

#define LED0	0

/* 函数声明 */
void led_init(void);
void led_switch(int led, int status);
#endif