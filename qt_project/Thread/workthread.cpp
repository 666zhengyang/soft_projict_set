#include "workthread.h"

WorkThread::WorkThread()
{
}

WorkThread::~WorkThread()
{
}
void WorkThread::run(void)
{
    //获取线程句柄
    unsigned long threadID =
            (unsigned long)currentThreadId();
    while(1){
        for(int i=1;i<=20;i++){
            qDebug("%lu:i=%d",threadID,i);
            msleep(200);
        }
    }
}







