/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-30 11:58:41
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-30 12:11:22
 */
#ifndef _BSP_SPI_H
#define _BSP_SPI_H
#include "imx6ul.h"

/* 函数声明 */
void spi_init(ECSPI_Type *base);
unsigned char spich0_readwrite_byte(ECSPI_Type *base, unsigned char txdata);

#endif

