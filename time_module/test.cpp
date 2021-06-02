/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-21 20:14:59
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-02 11:08:32
 */
#include "time_module.h"
#include "stdio.h"

/* sudo apt-get install ntp */
long long get_time_of_ns()
{
    struct timespec time_now = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &time_now);
    long long time_ns = time_now.tv_sec*1e9 + time_now.tv_nsec;
}

int main()  
{  
    tm* time_cur;
    tm* time_gm;
    Time* timeIns = new Time();
    timeIns->GetSecond();
    time_cur = timeIns->GetLocal();
    printf("time_cur is:%s",asctime(time_cur));
    time_gm = timeIns->GetGmtime();
    printf("time_gm is:%s",asctime(time_gm));
    timeIns->TimeSyncStart();
    timeIns->TimeSyncStop();
    return 0;  
}  
