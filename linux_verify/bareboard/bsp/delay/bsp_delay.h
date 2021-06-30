/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-29 10:08:12
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-29 19:45:57
 */

#ifndef __BSP_DELAY_H
#define __BSP_DELAY_H
#include "imx6ul.h"


/* 函数声明 */
void delay_init(void);
void delayus(unsigned    int usdelay);
void delayms(unsigned	 int msdelay);
void delay(volatile unsigned int n);
void gpt1_irqhandler(void);

#endif