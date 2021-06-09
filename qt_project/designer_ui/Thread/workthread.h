#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QDebug>
//1)继承QThread
class WorkThread:public QThread
{
public:
    WorkThread();
    ~WorkThread();
protected:
    //2）重写线程的入口函数
    void run(void);
};

#endif // WORKTHREAD_H





