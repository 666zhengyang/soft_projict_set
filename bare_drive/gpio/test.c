/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-15 11:38:06
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-15 11:44:21
 */

#define reg_gpio_ctrl *(volatile int *)(ToVirtual(GPIO_REG_CTRL))
#define reg_gpio_data *(volatile int *)(ToVirtual(GPIO_REG_DATA))

void LightInit(void)
{
    // reg_gpio_ctrl |= (1 << n); // gpio output

}

void LightON(void)
{
    // reg_gpio_data |= (1 << n); // gpio output high 
}

void LigthOff(void)
{
    // reg_gpio_data &= ~(1 << n); // gpio output low 
}

 // Tovirtual  MMU mac addr to vir addr  