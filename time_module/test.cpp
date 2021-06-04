/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-05-21 20:14:59
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-04 17:30:24
 */
#include "time_module.h"
#include "stdio.h"


/*
    #include <time.h>
int clock_gettime(clockid_t clk_id, struct timespec* tp);

可以根据需要，获取不同要求的精确时间

参数

clk_id : 检索和设置的clk_id指定的时钟时间。
CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,
中间时刻如果系统时间被用户改成其他,则对应的时间相应改变
　　CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响
　　CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间
　　CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间
 //   秒     time_t tv_sec;
 //  纳秒     long tv_nsec; 
struct timespec
{
    time_t tv_sec; 
    long tv_nsec; 
}*/

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
