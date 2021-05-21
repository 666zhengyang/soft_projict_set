#include "time_module.h"

time_t Time::GetSecond(void)
{
    time(&_second);
}

tm* Time::GetLocal(void)
{
    _time_loacl = localtime(&_second);
    return _time_loacl;
}

tm* Time::GetGmtime(void)
{
    _time_gm = gmtime(&_second);
    return _time_gm;
}

void Time::TimeSyncStart()
{
    system("/home/hp/work/time_module/time.sh start");
}

void Time::TimeSyncStop()
{
    system("/home/hp/work/time_module/time.sh stop");
}