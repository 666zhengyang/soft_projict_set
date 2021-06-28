.global _start
/*entry_func*/

_start:
/*enable all clock*/
ldr r0, = 0X020C4068  /*CCGR0 reg0*/
ldr r1, = 0XFFFFFFFF
str r1, [r0]

ldr r0, = 0X020C406C  /*CCGR0 reg1*/
str r1, [r0]

ldr r0, = 0X020C4070  /*CCGR0 reg2*/
str r1, [r0]

ldr r0, = 0X020C4074  /*CCGR0 reg3*/
str r1, [r0]

ldr r0, = 0X020C4078  /*CCGR0 reg4*/
str r1, [r0]

ldr r0, = 0X020C407C  /*CCGR0 reg5*/
str r1, [r0]

ldr r0, = 0X020C4080  /*CCGR0 reg6*/
str r1, [r0]

/* 2、设置 GPIO1_IO03 复用为 GPIO1_IO03 */
ldr r0, = 0X020E0068  /* 将寄存器 SW_MUX_GPIO1_IO03_BASE 加载到 r0 中 */
ldr r1, = 0X5  /* 设置寄存器 SW_MUX_GPIO1_IO03_BASE 的 MUX_MODE 为 5 */
str r1, [r0] 

/* 3、配置 GPIO1_IO03 的 IO 属性 
 *bit 16:0 HYS 关闭
 *bit [15:14]: 00 默认下拉
 *bit [13]: 0 kepper 功能
 *bit [12]: 1 pull/keeper 使能
 *bit [11]: 0 关闭开路输出
 *bit [7:6]: 10 速度 100Mhz
 *bit [5:3]: 110 R0/6 驱动能力
 *bit [0]: 0 低转换率
 */

 ldr r0, =0X020E02F4 /*寄存器 SW_PAD_GPIO1_IO03_BASE */
 ldr r1, =0X10B0
 str r1,[r0]

/* 4、设置 GPIO1_IO03 为输出 */
ldr r0, =0X0209C004 /*寄存器 GPIO1_GDIR */
ldr r1, =0X0000008
str r1,[r0]

 /* 5、打开 LED0
 * 设置 GPIO1_IO03 输出低电平
 */
 ldr r0, =0X0209C000 /*寄存器 GPIO1_DR */
 ldr r1, =0
 str r1,[r0]

 /*描述： loop 死循环*/
 loop:
    b loop