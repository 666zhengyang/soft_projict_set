/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-29 17:44:55
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-29 17:45:42
 */

#ifndef _BSP_TIMER_H
#define _BSP_TIMER_H
#include "imx6ul.h"

/* 函数声明 */
void epit1_init(unsigned int frac, unsigned int value);
void epit1_irqhandler(void);

#endif