#include <QApplication>
#include <QLabel>
#include <QPushButton>

int main(int argc,char** argv)
{
    QApplication app(argc,argv);

    QLabel label("我是标签");
    QPushButton button("我是按钮");

    label.show();
    button.show();

    //点击按钮关闭标签
    QObject::connect(&button,
        SIGNAL(clicked(void)),
        &label,SLOT(close(void)));
    //练习：实现点击按钮关闭当前的
    //QT应用程序.
    /*QObject::connect(&button,
        SIGNAL(clicked()),
        &app,SLOT(closeAllWindows()));*/
    QObject::connect(&button,
        SIGNAL(clicked()),
        &app,SLOT(quit()));

    return app.exec();
}




