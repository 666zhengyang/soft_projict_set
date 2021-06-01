#include <QApplication>
#include <QLabel>

int main(int argc,char** argv)
{
    //创建qt应用程序
    QApplication app(argc,argv);
    //创建标签组件
    QLabel label("Hello World!");
    //显示标签
    label.show();
    //让应用程序进入事件循环
    return app.exec();
}




