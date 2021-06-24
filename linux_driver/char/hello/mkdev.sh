#!/bin/sh 
###
 # @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 # @version: v0.01
 # @Author: zhengyang
 # @Date: 2021-06-11 09:16:18
 # @LastEditors: zhengyang
 # @LastEditTime: 2021-06-11 09:29:24
### 
module="hello" 
device="hello" 
mode="664" 
# invoke insmod with all arguments we got 
# and use a pathname, as newer modutils don't look in . by default 
/sbin/insmod ./$module.ko $* || exit 1 
# remove stale nodes 
rm -f /dev/${device}[0-3] 
major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices) 
mknod /dev/${device} c $major 0 
#mknod /dev/${device}1 c $major 1 
#mknod /dev/${device}2 c $major 2 
#mknod /dev/${device}3 c $major 3 
# give appropriate group/permissions, and change the group. 
# Not all distributions have staff, some have "wheel" instead. 
group="staff" 
grep -q '^staff:' /etc/group || group="wheel" 
chgrp $group /dev/${device}
chmod $mode /dev/${device}