#!/bin/bash 

make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- distclean 
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- mx6ull_14x14_ddr256_emmc_defconfig
make V=1 ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -j4

#1. make distclean
#2. make mx6ull_14x14_ddr256_nand_emmc_defconfig 
#3. make V1 -J4 4core output level 1
