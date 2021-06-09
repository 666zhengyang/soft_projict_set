#include <QCoreApplication>
#include <QThread>
#include <QSemaphore>

const int DataSize = 30;//要生产的产品个数
const int BufferSize = 5;//仓库大小
int buffer[BufferSize];//全局仓库

//控制生产者信号量
QSemaphore freeSpace(BufferSize);
//控制消费者信号量
QSemaphore usedSpace(0);

//生产者线程
class threadProducer:public QThread{
protected:
    void run(void){
        for(int i=0;i<DataSize;i++){
            freeSpace.acquire();//P:-1
            buffer[i%BufferSize]  = i+1;
            qDebug("producer:%d",buffer[i%BufferSize]);
            //生产完一个产品，仓库中多了一个可以消费的产品
            //控制消费者信号量加1
            usedSpace.release();//V:+1
        }
    }
};
//消费者线程
class threadConsumer:public QThread{
protected:
    void run(void){
        for(int i=0;i<DataSize;i++){
            usedSpace.acquire();//P:-1
            qDebug("consumer:%d",buffer[i%BufferSize]);
            //消费掉一个产品，仓库中多出一个空闲位置
            //生产者可以多生产一个产品，控制生产者信号
            //量加1
            freeSpace.release();//V:+1
            msleep(100);
        }
    }
};
int main(int argc,char** argv)
{
    //创建一个无ui界面的应用程序
    QCoreApplication app(argc,argv);

    threadProducer producer;
    threadConsumer consumer;
    producer.start();
    consumer.start();

    producer.wait();
    consumer.wait();

    return 0;
}






