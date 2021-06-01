#include <QApplication>
#include <QPushButton>
#include <QTextCodec>

int main(int argc,char** argv)
{
    QApplication app(argc,argv);
    
    QTextCodec* coder = 
        QTextCodec::codecForName("gbk");

    QPushButton button(
        coder->toUnicode("��ť1"));

    button.show();

    //QPushButton* qbutton = 
    //    new QPushButton("��ť2");
    //qbutton->show();

    return app.exec();
}
