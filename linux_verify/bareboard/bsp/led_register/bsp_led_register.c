/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-30 15:13:23
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-30 15:32:25
 */
#include "bsp_led_register.h"

/*
 * @description : 使能 I.MX6U 所有外设时钟
 * @param : 无  * @return : 无 */
void clk_register_enable(void)
{
    CCM_CCGR0 = 0xffffffff;
    CCM_CCGR1 = 0xffffffff;
    CCM_CCGR2 = 0xffffffff;
    CCM_CCGR3 = 0xffffffff;
    CCM_CCGR4 = 0xffffffff;
    CCM_CCGR5 = 0xffffffff;
    CCM_CCGR6 = 0xffffffff;
}

void led_register_init(void)
{
    /* 1、初始化 IO 复用, 复用为 GPIO1_IO03 */
    SW_MUX_GPIO1_IO03 = 0x5;

    /* 2、配置 GPIO1_IO03 的 IO 属性 
        *bit 16:0 HYS 关闭
        *bit [15:14]: 00 默认下拉
        *bit [13]: 0 kepper 功能
        *bit [12]: 1 pull/keeper 使能
        *bit [11]: 0 关闭开路输出
        *bit [7:6]: 10 速度 100Mhz
        *bit [5:3]: 110 R0/6 驱动能力
        *bit [0]: 0 低转换率
    */
    SW_PAD_GPIO1_IO03 = 0X10B0;

    /* 3、初始化 GPIO, GPIO1_IO03 设置为输出 */
    GPIO1_GDIR = 0X0000008;

    /* 4、设置 GPIO1_IO03 输出低电平，打开 LED0 */
    GPIO1_DR = 0X0;
}

void led_register_on(void)
{
    // 将 GPIO1_DR 的 bit3 清零
    GPIO1_DR &= ~(1<<3);
}

void led_register_off(void)
{
    // 将 GPIO1_DR 的 bit3 置 1
    GPIO1_DR |= (1<<3);
}

void delay_register_short(volatile unsigned int n)
{
    while(n--){};
}

void delay_register(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0x7ff);
    }
}

void led_register_test()
{
    clk_register_enable();
    led_register_init();
    while(1)
    {
        led_register_off();
        delay_register(500);

        led_register_on();
        delay_register(500);
    }
}