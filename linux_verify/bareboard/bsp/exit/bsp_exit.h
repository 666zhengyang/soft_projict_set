/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-29 16:58:01
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-29 16:58:28
 */
#ifndef _BSP_EXIT_H
#define _BSP_EXIT_H

#include "imx6ul.h"

/* 函数声明 */
void exit_init(void);						/* 中断初始化 */
void gpio1_io18_irqhandler(void); 			/* 中断处理函数 */

#endif
