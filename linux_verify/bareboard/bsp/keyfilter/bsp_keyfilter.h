/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-29 18:02:16
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-07-30 19:19:31
 */

#ifndef _BSP_KEYFILTER_H
#define _BSP_KEYFILTER_H

/*函数声明*/
void filterkey_init(void);
void filtertimer_init(unsigned int value);
void filtertimer_stop(void);
void filtertimer_restart(unsigned int value);
void filtertimer_irqhandler(void);
void gpio1_16_31_irqhandler(void);

#endif
