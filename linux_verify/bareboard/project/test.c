/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-29 10:13:44
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-07-07 09:32:33
 */

#include "bsp_led_register.h"
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_timer.h"
#include "bsp_uart.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"
#include "bsp_rtc.h"
#include "bsp_ap3216c.h"
#include "bsp_spi.h"
#include "bsp_icm20608.h"
#include "bsp_gt9147.h"
#include "bsp_ft5xx6.h"
#include "bsp_backlight.h"

#define LED_REGISTER_TEST_ENABLE 0
#define KEY_TEST_ENABLE 0
#define KEY_EXIT_TEST_ENABLE 0
#define TIMER_EXIT_TEST_ENABLE 0
#define KEY_FILTER_TEST_ENABLE 0
#define TIMER_DELAY_TEST_ENABLE 0
#define UART_PUT_GET_TEST_ENABLE 0
#define UART_PRINT_TEST_ENABLE 0
#define LCD_TEST_ENABLE 1
#define RTC_TEST_ENABLE 0
#define IIC_TEST_ENABLE 0
#define SPI_TEST_ENABLE 0
#define IIC_INT_TEST_ENABLE 0
#define BACKLIGHT_TEST_ENABLE 0

/*
 * @description	: 指定的位置显示整数数据
 * @param - x	: X轴位置
 * @param - y 	: Y轴位置
 * @param - size: 字体大小
 * @param - num : 要显示的数据
 * @return 		: 无
 */
void integer_display(unsigned short x, unsigned short y, unsigned char size, signed int num)
{
	char buf[200];
	
	lcd_fill(x, y, x + 50, y + size, tftlcd_dev.backcolor);
	
	memset(buf, 0, sizeof(buf));
	if(num < 0)
		sprintf(buf, "-%d", -num);
	else 
		sprintf(buf, "%d", num);
	lcd_show_string(x, y, 50, size, size, buf); 
}


/*
 * @description	: 指定的位置显示小数数据,比如5123，显示为51.23
 * @param - x	: X轴位置
 * @param - y 	: Y轴位置
 * @param - size: 字体大小
 * @param - num : 要显示的数据，实际小数扩大100倍，
 * @return 		: 无
 */
void decimals_display(unsigned short x, unsigned short y, unsigned char size, signed int num)
{
	signed int integ; 	/* 整数部分 */
	signed int fract;	/* 小数部分 */
	signed int uncomptemp = num; 
	char buf[200];

	if(num < 0)
		uncomptemp = -uncomptemp;
	integ = uncomptemp / 100;
	fract = uncomptemp % 100;

	memset(buf, 0, sizeof(buf));
	if(num < 0)
		sprintf(buf, "-%d.%d", integ, fract);
	else 
		sprintf(buf, "%d.%d", integ, fract);
	lcd_fill(x, y, x + 60, y + size, tftlcd_dev.backcolor);
	lcd_show_string(x, y, 60, size, size, buf); 
}

/*
 * @description	: 使能I.MX6U的硬件NEON和FPU
 * @param 		: 无
 * @return 		: 无
 */
 void imx6ul_hardfpu_enable(void)
{
	uint32_t cpacr;
	uint32_t fpexc;

	/* 使能NEON和FPU */
	cpacr = __get_CPACR();
	cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
		   |  (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
	__set_CPACR(cpacr);
	fpexc = __get_FPEXC();
	fpexc |= 0x40000000UL;	
	__set_FPEXC(fpexc);
}

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
#if LED_REGISTER_TEST_ENABLE 
	led_register_test();
#endif

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

#if LCD_TEST_ENABLE
		/* 背景颜色索引 */
unsigned int backcolor[10] = {
	LCD_BLUE, 		LCD_GREEN, 		LCD_RED, 	LCD_CYAN, 	LCD_YELLOW, 
	LCD_LIGHTBLUE, 	LCD_DARKBLUE, 	LCD_WHITE, 	LCD_BLACK, 	LCD_ORANGE

}; 
	unsigned char index = 0;
	unsigned char state = OFF;

	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();				/* 初始化延时 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	uart_init();				/* 初始化串口，波特率115200 */
	lcd_init();					/* 初始化LCD 			*/

	tftlcd_dev.forecolor = LCD_RED;	  
	while(1)				
	{	
		lcd_clear(backcolor[index]); 	  
		lcd_show_string(10, 40, 260, 32, 32,(char*)"ALPHA IMX6U"); 	
		lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
		lcd_show_string(10, 110, 240, 16, 16,(char*)"ATOM@ALIENTEK");      					 
		lcd_show_string(10, 130, 240, 12, 12,(char*)"2019/8/14");	      					 
	    index++;
		if(index == 10)
			index = 0;      
		state = !state;
		led_switch(LED0,state);
		delayms(1000);

#if 0
		index++;
		if(index == 10)
			index = 0;
		lcd_fill(0, 300, 1023, 599, backcolor[index]);
		lcd_show_string(800,10,240,32,32,(char*)"INDEX=");  /*显示字符串				  */
		lcd_shownum(896,10, index, 2, 32); 					/* 显示数字，叠加显示	*/
		
		state = !state;
		led_switch(LED0,state);
		delayms(1000);	/* 延时一秒	*/
#endif
	}
#endif 

#if RTC_TEST_ENABLE 
	unsigned char key = 0;
	int i = 3, t = 0;
	char buf[160];
	struct rtc_datetime rtcdate;
	unsigned char state = OFF;


	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();				/* 初始化延时 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	uart_init();				/* 初始化串口，波特率115200 */
	lcd_init();					/* 初始化LCD 			*/
	rtc_init(); 				/* 初始化RTC	 		*/

	tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"ALPHA-IMX6UL RTC TEST");    /* 显示字符串 */
	lcd_show_string(50, 40, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(50, 60, 200, 16, 16, (char*)"2019/3/27");  
	tftlcd_dev.forecolor = LCD_BLUE;
	memset(buf, 0, sizeof(buf));
	
	while(1)
	{
		if(t==100)	//1s时间到了
		{
			t=0;
			printf("will be running %d s......\r", i);
			
			lcd_fill(50, 90, 370, 110, tftlcd_dev.backcolor); /* 清屏 */
			sprintf(buf, "will be running %ds......", i);
			lcd_show_string(50, 90, 300, 16, 16, buf); 
			i--;
			if(i < 0)
				break;
		}

		key = key_getvalue();
		if(key == KEY0_VALUE)
		{
			rtcdate.year = 2018;
   			rtcdate.month = 1;
    		rtcdate.day = 15;
    		rtcdate.hour = 16;
    		rtcdate.minute = 23;
    		rtcdate.second = 0;
			rtc_setdatetime(&rtcdate); /* 初始化时间和日期 */
			printf("\r\n RTC Init finish\r\n");
			break;
		}
			
		delayms(10);
		t++;
	}
	tftlcd_dev.forecolor = LCD_RED;
	lcd_fill(50, 90, 370, 110, tftlcd_dev.backcolor); /* 清屏 */
	lcd_show_string(50, 90, 200, 16, 16, (char*)"Current Time:");  			/* 显示字符串 */
	tftlcd_dev.forecolor = LCD_BLUE;

	while(1)					
	{	
		rtc_getdatetime(&rtcdate);
		sprintf(buf,"%d/%d/%d %d:%d:%d",rtcdate.year, rtcdate.month, rtcdate.day, rtcdate.hour, rtcdate.minute, rtcdate.second);
		lcd_fill(50,110, 300,130, tftlcd_dev.backcolor);
		lcd_show_string(50, 110, 250, 16, 16,(char*)buf);  /* 显示字符串 */
		
		state = !state;
		led_switch(LED0,state);
		delayms(1000);	/* 延时一秒 */
	}
#endif

#if IIC_TEST_ENABLE 
	unsigned short ir, als, ps;
	unsigned char state = OFF;

	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();				/* 初始化延时 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	led_init();					/* 初始化led 			*/
	beep_init();				/* 初始化beep	 		*/
	uart_init();				/* 初始化串口，波特率115200 */
	lcd_init();					/* 初始化LCD 			*/

	tftlcd_dev.forecolor = LCD_RED;	
	lcd_show_string(30, 50, 200, 16, 16, (char*)"ALPHA-IMX6U IIC TEST");  
	lcd_show_string(30, 70, 200, 16, 16, (char*)"AP3216C TEST");  
	lcd_show_string(30, 90, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(30, 110, 200, 16, 16, (char*)"2019/3/26");  
	
	while(ap3216c_init())		/* 检测不到AP3216C */
	{
		lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Check Failed!");
		delayms(500);
		lcd_show_string(30, 130, 200, 16, 16, (char*)"Please Check!        ");
		delayms(500);
	}	
	
	lcd_show_string(30, 130, 200, 16, 16, (char*)"AP3216C Ready!");  
    lcd_show_string(30, 160, 200, 16, 16, (char*)" IR:");	 
	lcd_show_string(30, 180, 200, 16, 16, (char*)" PS:");	
	lcd_show_string(30, 200, 200, 16, 16, (char*)"ALS:");	
	tftlcd_dev.forecolor = LCD_BLUE;	
	while(1)					
	{
		ap3216c_readdata(&ir, &ps, &als);		/* 读取数据		  	*/
		lcd_shownum(30 + 32, 160, ir, 5, 16);	/* 显示IR数据 		*/
        lcd_shownum(30 + 32, 180, ps, 5, 16);	/* 显示PS数据 		*/
        lcd_shownum(30 + 32, 200, als, 5, 16);	/* 显示ALS数据 	*/ 
		delayms(120);
		state = !state;
		led_switch(LED0,state);	
	}
#endif

#if SPI_TEST_ENABLE 

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
	unsigned char state = OFF;

	imx6ul_hardfpu_enable();	/* 使能I.MX6U的硬件浮点 			*/
	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 					*/
	delay_init();				/* 初始化延时 					*/
	clk_enable();				/* 使能所有的时钟 					*/
	led_init();					/* 初始化led 					*/
	beep_init();				/* 初始化beep	 				*/
	uart_init();				/* 初始化串口，波特率115200 */
	lcd_init();					/* 初始化LCD 					*/		

	tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"ALPHA-IMX6U SPI TEST");  
	lcd_show_string(50, 40, 200, 16, 16, (char*)"ICM20608 TEST");  
	lcd_show_string(50, 60, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(50, 80, 200, 16, 16, (char*)"2019/3/27");  
	
	while(icm20608_init())		/* 初始化ICM20608	 			*/
	{
		lcd_show_string(50, 100, 200, 16, 16, (char*)"ICM20608 Check Failed!");
		delayms(500);
		lcd_show_string(50, 100, 200, 16, 16, (char*)"Please Check!        ");
		delayms(500);
	}	

	lcd_show_string(50, 100, 200, 16, 16, (char*)"ICM20608 Ready");
	
	lcd_show_string(50, 130, 200, 16, 16, (char*)"accel x:");  
	lcd_show_string(50, 150, 200, 16, 16, (char*)"accel y:");  
	lcd_show_string(50, 170, 200, 16, 16, (char*)"accel z:");  
	lcd_show_string(50, 190, 200, 16, 16, (char*)"gyro  x:"); 
	lcd_show_string(50, 210, 200, 16, 16, (char*)"gyro  y:"); 
	lcd_show_string(50, 230, 200, 16, 16, (char*)"gyro  z:"); 
	lcd_show_string(50, 250, 200, 16, 16, (char*)"temp   :"); 

	lcd_show_string(50 + 181, 130, 200, 16, 16, (char*)"g");  
	lcd_show_string(50 + 181, 150, 200, 16, 16, (char*)"g");  
	lcd_show_string(50 + 181, 170, 200, 16, 16, (char*)"g");  
	lcd_show_string(50 + 181, 190, 200, 16, 16, (char*)"o/s"); 
	lcd_show_string(50 + 181, 210, 200, 16, 16, (char*)"o/s"); 
	lcd_show_string(50 + 181, 230, 200, 16, 16, (char*)"o/s"); 
	lcd_show_string(50 + 181, 250, 200, 16, 16, (char*)"C");
	
	tftlcd_dev.forecolor = LCD_BLUE;

	while(1)					
	{		
		icm20608_getdata();
		integer_display(50 + 70, 130, 16, icm20608_dev.accel_x_adc);
		integer_display(50 + 70, 150, 16, icm20608_dev.accel_y_adc);
		integer_display(50 + 70, 170, 16, icm20608_dev.accel_z_adc);
		integer_display(50 + 70, 190, 16, icm20608_dev.gyro_x_adc);
		integer_display(50 + 70, 210, 16, icm20608_dev.gyro_y_adc);
		integer_display(50 + 70, 230, 16, icm20608_dev.gyro_z_adc);
		integer_display(50 + 70, 250, 16, icm20608_dev.temp_adc);

		decimals_display(50 + 70 + 50, 130, 16, icm20608_dev.accel_x_act);
		decimals_display(50 + 70 + 50, 150, 16, icm20608_dev.accel_y_act);
		decimals_display(50 + 70 + 50, 170, 16, icm20608_dev.accel_z_act);
		decimals_display(50 + 70 + 50, 190, 16, icm20608_dev.gyro_x_act);
		decimals_display(50 + 70 + 50, 210, 16, icm20608_dev.gyro_y_act);
		decimals_display(50 + 70 + 50, 230, 16, icm20608_dev.gyro_z_act);
		decimals_display(50 + 70 + 50, 250, 16, icm20608_dev.temp_act);

#if 0		
		printf("accel x = %d\r\n",icm20608_dev.accel_x_adc);
		printf("accel y = %d\r\n",icm20608_dev.accel_y_adc);
		printf("accel z = %d\r\n",icm20608_dev.accel_z_adc);
		printf("gyrp  x = %d\r\n",icm20608_dev.gyro_x_adc);
		printf("gyro  y = %d\r\n",icm20608_dev.gyro_y_adc);
		printf("gyro  z = %d\r\n",icm20608_dev.gyro_z_adc);
		printf("temp    = %d\r\n",icm20608_dev.temp_adc);
#endif
		delayms(120);
		state = !state;
		led_switch(LED0,state);	
	}
#endif

#if IIC_INT_TEST_ENABLE 
	unsigned char i = 0;
	unsigned char state = OFF;

	imx6ul_hardfpu_enable();	/* 使能I.MX6U的硬件浮点 			*/
	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 					*/
	delay_init();				/* 初始化延时 					*/
	clk_enable();				/* 使能所有的时钟 					*/
	led_init();					/* 初始化led 					*/
	beep_init();				/* 初始化beep	 				*/
	uart_init();				/* 初始化串口，波特率115200 */
	lcd_init();					/* 初始化LCD 					*/		
	
	/* 初始化触摸屏					*/ 
	if(tftlcd_dev.id == ATK7016 || tftlcd_dev.id == ATK7084) {
		ft5426_init();
	} else if(tftlcd_dev.id == ATK4384|| tftlcd_dev.id == ATK4342) {
		gt9147_init();
	}

	tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"IMX6U-ALPHA TOUCH SCREEN TEST");  
	lcd_show_string(50, 40, 200, 16, 16, (char*)"TOUCH SCREEN TEST");  
	lcd_show_string(50, 60, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(50, 80, 200, 16, 16, (char*)"2019/3/27");  
	
	lcd_show_string(50, 110, 400, 16, 16,	(char*)"TP Num	:");  
	lcd_show_string(50, 130, 200, 16, 16,	(char*)"Point0 X:");  
	lcd_show_string(50, 150, 200, 16, 16,	(char*)"Point0 Y:");  
	lcd_show_string(50, 170, 200, 16, 16,	(char*)"Point1 X:");  
	lcd_show_string(50, 190, 200, 16, 16,	(char*)"Point1 Y:");  
	lcd_show_string(50, 210, 200, 16, 16,	(char*)"Point2 X:");  
	lcd_show_string(50, 230, 200, 16, 16,	(char*)"Point2 Y:");  
	lcd_show_string(50, 250, 200, 16, 16,	(char*)"Point3 X:");  
	lcd_show_string(50, 270, 200, 16, 16,	(char*)"Point3 Y:");  
	lcd_show_string(50, 290, 200, 16, 16,	(char*)"Point4 X:");  
	lcd_show_string(50, 310, 200, 16, 16,	(char*)"Point4 Y:");  
	tftlcd_dev.forecolor = LCD_BLUE;
	
	while(1)					
	{
		if(tftlcd_dev.id == ATK7016 || tftlcd_dev.id == ATK7084) {
			lcd_shownum(50 + 72, 110, ft5426_dev.point_num , 1, 16);
			lcd_shownum(50 + 72, 130, ft5426_dev.x[0], 5, 16);
			lcd_shownum(50 + 72, 150, ft5426_dev.y[0], 5, 16);
			lcd_shownum(50 + 72, 170, ft5426_dev.x[1], 5, 16);
			lcd_shownum(50 + 72, 190, ft5426_dev.y[1], 5, 16);
			lcd_shownum(50 + 72, 210, ft5426_dev.x[2], 5, 16);
			lcd_shownum(50 + 72, 230, ft5426_dev.y[2], 5, 16);
			lcd_shownum(50 + 72, 250, ft5426_dev.x[3], 5, 16);
			lcd_shownum(50 + 72, 270, ft5426_dev.y[3], 5, 16);
			lcd_shownum(50 + 72, 290, ft5426_dev.x[4], 5, 16);
			lcd_shownum(50 + 72, 310, ft5426_dev.y[4], 5, 16);
		} else if(tftlcd_dev.id == ATK4384|| tftlcd_dev.id == ATK4342) {
			lcd_shownum(50 + 72, 110, gt9147_dev.point_num , 1, 16);
			lcd_shownum(50 + 72, 130, gt9147_dev.x[0], 5, 16);
			lcd_shownum(50 + 72, 150, gt9147_dev.y[0], 5, 16);
			lcd_shownum(50 + 72, 170, gt9147_dev.x[1], 5, 16);
			lcd_shownum(50 + 72, 190, gt9147_dev.y[1], 5, 16);
			lcd_shownum(50 + 72, 210, gt9147_dev.x[2], 5, 16);
			lcd_shownum(50 + 72, 230, gt9147_dev.y[2], 5, 16);
			lcd_shownum(50 + 72, 250, gt9147_dev.x[3], 5, 16);
			lcd_shownum(50 + 72, 270, gt9147_dev.y[3], 5, 16);
			lcd_shownum(50 + 72, 290, gt9147_dev.x[4], 5, 16);
			lcd_shownum(50 + 72, 310, gt9147_dev.y[4], 5, 16);
		}
		delayms(10);
		i++;
	
		if(i == 50)
		{	
			i = 0;
			state = !state;
			led_switch(LED0,state); 
		}
	}	
#endif

#if BACKLIGHT_TEST_ENABLE
	unsigned char keyvalue = 0;
	unsigned char i = 0;
	unsigned char state = OFF;
	unsigned char duty = 0;
	
	imx6ul_hardfpu_enable();	/* 使能I.MX6U的硬件浮点 			*/
	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 					*/
	delay_init();				/* 初始化延时 					*/
	clk_enable();				/* 使能所有的时钟 					*/
	led_init();					/* 初始化led 					*/
	beep_init();				/* 初始化beep	 				*/
	uart_init();				/* 初始化串口，波特率115200 */
	lcd_init();					/* 初始化LCD 					*/
	backlight_init();			/* 初始化背光PWM			 		*/ 


	tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"ZERO-IMX6U BACKLIGHT PWM TEST");  
	lcd_show_string(50, 40, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(50, 60, 200, 16, 16, (char*)"2019/3/27");   
	lcd_show_string(50, 90, 400, 16, 16, (char*)"PWM Duty:   %");  
	tftlcd_dev.forecolor = LCD_BLUE;

	/* 设置默认占空比 10% */
	duty = 10;
	lcd_shownum(50 + 72, 90, duty, 3, 16);
	pwm1_setduty(duty);	
	
	while(1)					
	{
		keyvalue = key_getvalue();
		if(keyvalue == KEY0_VALUE)
		{
			duty += 10;				/* 占空比加10% */
			if(duty > 100)			/* 如果占空比超过100%，重新从10%开始 */
				duty = 10;
			lcd_shownum(50 + 72, 90, duty, 3, 16);
			pwm1_setduty(duty);		/* 设置占空比 */
		}
		
		delayms(10);
		i++;
		if(i == 50)
		{	
			i = 0;
			state = !state;
			led_switch(LED0,state);	
		}
	}
	return 0;
#endif

	return 0;
}