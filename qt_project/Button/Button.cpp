#include <QApplication>
#include <QPushButton>
#include <QTextCodec>

int main(int argc,char** argv)
{
    QApplication app(argc,argv);
    
    QTextCodec* coder = 
        QTextCodec::codecForName("gbk");

    QPushButton button(
        coder->toUnicode("°´Å¥1"));

    button.show();

    //QPushButton* qbutton = 
    //    new QPushButton("°´Å¥2");
    //qbutton->show();

    return app.exec();
}
