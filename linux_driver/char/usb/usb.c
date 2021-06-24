#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define NUM_OF_DEVICES    2

int major = 255;

/* 两个设备，所以有两套结构体 */
/* 设备0对应的设备结构体是hello_dev[0], 设备1对应的设备结构体是hello_dev[1] */
struct hello_device {
    dev_t devno;
    struct cdev cdev;
    char data[128];
    char name[16];
}hello_dev[NUM_OF_DEVICES];

struct class * hello_class;

const char DEVNAME[] = "hello_device";

int hello_open(struct inode * ip, struct file * fp)
{
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 获取用户打开的设备对应的设备结构体 hello_dev[0] 或者 hello_dev[1] */
    struct hello_device * dev = container_of(ip->i_cdev, struct hello_device, cdev);
    
    /* open的时候，通过container_of能够获取到用户要打开的那个设备的设备结构体，所有需要把这个结构体通过file指针的
     * private_data参数传递给read/write */
    fp->private_data = dev;
    
    /* 一般用来做初始化设备的操作 */
    /* ... */
    
    return 0;
}

int hello_close(struct inode * ip, struct file * fp)
{
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 一般用来做和open相反的操作，open申请资源，close释放资源 */
    /* ... */
    
    return 0;
}

ssize_t hello_read(struct file * fp, char __user * buf, size_t count, loff_t * loff)
{
    int ret;
    
    /* 通过file指针，获取到用户要操作的设备对应的设备结构体 */
    struct hello_device * dev = fp->private_data;
    
    /* 将用户需要的数据从内核空间copy到用户空间(buf) */
    printk("%s : %d\n", __func__, __LINE__);
    if (count <=0 || count > 128)
        count = 128;
    if ((ret = copy_to_user(buf, dev->data, count)))
    {
        printk("copy_to_user err\n");
        return -1;
    }
    
    return count;
}

ssize_t hello_write(struct file * fp, const char __user * buf, size_t count, loff_t * loff)
{
    int ret;
    struct hello_device * dev = fp->private_data;
    
    /* 将用户需要的数据从内核空间copy到用户空间(buf) */
    printk("%s : %d\n", __func__, __LINE__);
    if (count <=0 || count > 128)
        count = 128;
    if ((ret = copy_from_user(dev->data, buf, count)))
    {
        printk("copy_from_user err\n");
        return -1;
    }
    
    return count;
}

/* 2. 分配file_operations结构体 */
struct file_operations hello_fops = {
    .owner = THIS_MODULE,
    .open  = hello_open,
    .release = hello_close,
    .read = hello_read,
    .write = hello_write
};

struct cdev cdev;

static int hello_init(void)
{
    int i;
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 1. 生成并注册两个设备的设备号 */
    /* 3. 分配、设置、注册两套cdev结构体 */
    for (i = 0; i < NUM_OF_DEVICES; i++)
    {
        hello_dev[i].devno = MKDEV(major, i);
        sprintf(hello_dev[i].name, "%s%d", DEVNAME, i);
        register_chrdev_region(hello_dev[i].devno, 1, hello_dev[i].name);
        
        hello_dev[i].cdev.owner = THIS_MODULE;
        cdev_add(&hello_dev[i].cdev, hello_dev[i].devno, 1);
        cdev_init(&hello_dev[i].cdev, &hello_fops);
        
        /* 初始化两个设备各自的存储空间 */
        sprintf(hello_dev[i].data, "Hi, I am hello device %d", i);
    }
    
    /* 在/sys/class目录下创建hello类，并在这个类下面创建hello_device0和hello_device1 */
    hello_class = class_create(THIS_MODULE, DEVNAME);
    for (i = 0; i < NUM_OF_DEVICES; i++)
    {
        device_create(hello_class, NULL, hello_dev[i].devno, NULL, "%s%d", DEVNAME, i);
        printk("success!\n");
    }
    return 0;
}

static void hello_exit(void)
{
    int i;
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 释放资源 */
    for (i = 0; i < NUM_OF_DEVICES; i++)
    {
        device_destroy(hello_class, hello_dev[i].devno);
        cdev_del(&hello_dev[i].cdev);
        unregister_chrdev_region(hello_dev[i].devno, 1);
    }
    class_destroy(hello_class);
}

MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);