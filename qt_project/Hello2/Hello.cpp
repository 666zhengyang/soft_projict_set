#include <QApplication>
#include <QLabel>
#include <QTextCodec>

int main(int argc,char** argv)
{
    //创建qt应用程序
    QApplication app(argc,argv);
    
    //1)创建gbk的编码对象
    QTextCodec* coder =
        QTextCodec::codecForName("GBK");
    //2)将中文字符串先转换为unicode编码
    //再显示
    QString str = 
        coder->toUnicode("你好 QT！");

    //创建标签组件
    QLabel label(str);

    //显示标签
    label.show();
    //让应用程序进入事件循环
    return app.exec();
}




