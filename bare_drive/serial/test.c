/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-15 11:33:37
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-15 11:37:21
 */
serial.h 

extern void SerialInit(void);
extern void SerialSend(const char buf*, int count);
extern void SerialRecv(char buf*, int count);

serial.c 

void SerialInit(void)
{
    
}

SerialSend(const char buf*, int count)
{
    
}

SerialRecv(char buf*, int count)
{
    
}

void SerialIsr(void)
{
    serialInt = 1;
}