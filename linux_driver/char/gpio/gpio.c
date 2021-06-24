/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-11 17:20:41
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-11 17:25:55
 */

/*
    在入口函数中，初始化设备文件、映射硬件的物理地址等信息
    在open函数中，设置GPFCON寄存器，使得LED对应的引脚为输出引脚
    在write函数中，读取应用程序发送的数据，并根据数据操作GPFDAT寄存器的数据，让芯片对应引脚输出高电平或者低电平，从而来点亮或者熄灭LED
*/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <asm-arm/uaccess.h>
#include <asm/io.h>
#include <asm/arch/regs-gpio.h>
#include <asm/hardware.h>

static int dev_id = 0;
static const char *dev_name = "seventh_driver";
static struct class* seventh_class;
static struct class_device* seventh_class_device;

//定义两个变量，用于存放 GPFCON和GPFDAT两个寄存器的地址
static volatile unsigned int* gpfcon = NULL;
static volatile unsigned int* gpfdat = NULL;

static size_t seventh_write (struct file *file, const char __user *buff, size_t size, loff_t *ppos)
{
    volatile unsigned int argv[3];  //如果传入的参数数量不对，那么直接返回即可
    if(size != 12){ 
            printk("arguments count is wrong.%d\n", size); 
            return 0;
        }
        
    copy_from_user(argv, buff, size);//从用户空间获取传入的数据

    //操作GPFDAT对应寄存器的对应位
    int i = 0;
    for(; i < size / 4; i++){
        if(argv[i])  //如果传入的是0，关闭信号，将寄存器对应位改为高电平，熄灭LED
            *gpfdat |= (0x1 << (4 + i));   //操作的是4、5、6三个位，所以偏移量从4开始计算
        else//打开LED，传入的参数为1
            *gpfdat &= ~(0x1 << (4 + i)); 
    }       
    
    return 0;
}

static int seventh_open (struct inode *inode, struct file *file)
{
        //设置GPFCON寄存器之前，先将对应的位清零
    *gpfcon &= ~((0x03 << (4*2)) | (0x03 << (5*2)) | (0x03 << (6*2)));  //需要用两位来控制引脚的性质，因此位操作时需要*2
        //设置GPFCON寄存器，对应位为01，将对应引脚配置为输出
    *gpfcon |=  ((0x01 << (4*2)) | (0x01 << (5*2)) | (0x01 << (6*2)));
    return 0;
}

static struct file_operations seventh_fops = 
{
    .owner = THIS_MODULE,
    .open = seventh_open,
    .write = seventh_write,
};

//入口函数
static int __init seventh_init(void)
{
    dev_id = register_chrdev(dev_id, dev_name, &seventh_fops);

    seventh_class = class_create(THIS_MODULE, dev_name);    
    seventh_class_device = class_device_create(seventh_class, NULL, MKDEV(dev_id, 0), NULL, dev_name);
    
    gpfcon = (volatile unsigned int*)ioremap(0x56000050, 8);//将gpfcon映射到0x56000050的物理地址上，需要映射的地址由0x56000050~0x56000057一共八个字节
//其中GPFCON和GPFDAT各占4个字节
    gpfdat = gpfcon + 1;    

    printk("init\n");
    return 0;
}

//出口函数
static void __exit seventh_exit(void)
{
    unregister_chrdev(dev_id, dev_name);
    class_device_unregister(seventh_class_device);
    class_destroy(seventh_class);
    
    iounmap(gpfcon);  //解映射

    printk("exit\n");
}
module_init(seventh_init);
module_exit(seventh_exit);
MODULE_LICENSE("GPL");