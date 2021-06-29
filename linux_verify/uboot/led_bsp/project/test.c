/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-29 10:13:44
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-29 20:51:38
 */

#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_timer.h"
#include "bsp_uart.h"

#define KEY_TEST_ENABLE 0
#define KEY_EXIT_TEST_ENABLE 0
#define TIMER_EXIT_TEST_ENABLE 0
#define KEY_FILTER_TEST_ENABLE 0
#define TIMER_DELAY_TEST_ENABLE 0
#define UART_PUT_GET_TEST_ENABLE 0
#define UART_PRINT_TEST_ENABLE 1
/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{

#if KEY_TEST_ENABLE
	int i = 0;
	int keyvalue = 0;
	unsigned char led_state = OFF;
	unsigned char beep_state = OFF;
	
	imx6u_clkinit();	/* 初始化系统时钟 			*/
	clk_enable();		/* 使能所有的时钟 			*/
	led_init();			/* 初始化led 			*/
	beep_init();		/* 初始化beep	 		*/
	key_init();			/* 初始化key 			*/

	while(1)			
	{	
		keyvalue = key_getvalue();
		if(keyvalue)
		{
			switch ((keyvalue))
			{
				case KEY0_VALUE:
					beep_state = !beep_state;
					beep_switch(beep_state);
					break;
			}
		}

		i++;
		if(i==50)
		{
			i = 0;
			led_state = !led_state;
			led_switch(LED0, led_state);
		}
		delay(10);
	}

#endif

#if KEY_EXIT_TEST_ENABLE
	 unsigned char state = OFF;
	int_init(); 		/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();	/* 初始化系统时钟 			*/
	clk_enable();		/* 使能所有的时钟 			*/
	led_init();			/* 初始化led 			*/
	beep_init();		/* 初始化beep	 		*/
	key_init();			/* 初始化key 			*/
	exit_init();		/* 初始化按键中断			*/
	while(1)			
	{	
		state = !state;
		led_switch(LED0, state);
		delay(500);
	}
#endif

#if TIMER_EXIT_TEST_ENABLE
	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	key_init();					/* 初始化key 			*/
	epit1_init(0, 66000000/2);	/* 初始化EPIT1定时器，1分频
								 * 计数值为:66000000/2，也就是
								 * 定时周期为500ms。
								 */
	while(1)			
	{	
		delay(500);
	}
#endif

#if KEY_FILTER_TEST_ENABLE
	unsigned char state = OFF;
	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	filterkey_init();			/* 带有消抖功能的按键 */

	while(1)			
	{	
		state = !state;
		led_switch(LED0, state);
		delay(500);
	}
#endif 

#if TIMER_DELAY_TEST_ENABLE
	unsigned char state = OFF;
	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();				/* 初始化延时 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/

	while(1)			
	{	
		state = !state;
		led_switch(LED0, state);
		delayms(500);
	}
#endif 

#if UART_PUT_GET_TEST_ENABLE
	unsigned char a=0;
	unsigned char state = OFF;

	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();				/* 初始化延时 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	uart_init();				/* 初始化串口，波特率115200 */

	while(1)				
	{	
		puts("请输入1个字符:");
		a=getc();
		putc(a);	//回显功能
		puts("\r\n");

		//显示输入的字符
		puts("您输入的字符为:");
		putc(a);
		puts("\r\n\r\n");
		
		state = !state;
		led_switch(LED0,state);
	}
#endif 

#if UART_PRINT_TEST_ENABLE 
	unsigned char state = OFF;
	int a , b;

	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();				/* 初始化延时 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	uart_init();				/* 初始化串口，波特率115200 */
	
	while(1)					
	{	
		printf("输入两个整数，使用空格隔开:");
		scanf("%d %d", &a, &b);					 		/* 输入两个整数 */
		printf("\r\n数据%d + %d = %d\r\n\r\n", a, b, a+b);	/* 输出两个数相加的和 */

		state = !state;
		led_switch(LED0,state);
	}
#endif

	return 0;
}