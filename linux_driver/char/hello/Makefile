#定义一些变量，增加代码的阅读性和扩展性
#`uname -r`这种写法就是执行uname -r这个shell命令，从而构造这个绝对路径，因为每个人的计算机的绝对路径都不一样，这样提高通用性，对于我的主机，这个路径相当于/lib/modules/4.4.0-31-generic/build
KERNEL_PATH := /lib/modules/`uname -r`/build
PWD := $(shell pwd)

#这个名字表示:要生产的模块的名字，最终会生成hello.ko
MODULE_NAME := hello
   
#表示要生成hello.ko要依靠中间文件hello.o  kbuild系统会将源码hello.c编译成hello.o
obj-m := $(MODULE_NAME).o
   
#当执行make命令默认会寻找第一个目标，即all
all:
	$(MAKE) -C $(KERNEL_PATH) M=$(PWD)
   
#执行make clean要执行的操作，将编译生成的中间文件删掉
clean:
	rm -rf .*.cmd *.o *.mod.c *.order *.symvers  *.ko