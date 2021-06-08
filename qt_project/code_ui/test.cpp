/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-01 14:09:43
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-08 16:28:32
 */
#include <QApplication>
#include "calc.h"

int main(int argc,char** argv)
{
    // 创建qt应用程序
    QApplication app(argc, argv);
    MyCalc calc;
    QPushButton close_app("close_app", &calc);
    close_app.move(400, 600);

    QObject::connect(&close_app, SIGNAL(clicked()), &app, SLOT(quit()));
    calc.show();
    // 让应用程序进入事件循环
    return app.exec();
}




