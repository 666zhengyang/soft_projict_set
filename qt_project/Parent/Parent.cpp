/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-01 14:09:43
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-02 16:18:55
 */
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QlineEdit>

int main(int argc,char** argv)
{
    QApplication app(argc,argv);

    //创建父窗口对象
    QWidget parent;
    //调整父窗口大小
    parent.resize(500,500);

    //创建标签并停靠在父窗口上
    QLabel label("我是标签",&parent);
    //创建按钮并停靠在父窗口上
    QPushButton button("我是按钮",&parent);

    //调整按钮和标签位置
    label.move(20,20);
    button.move(20,170);

    //显示父窗口，它上面包含组件也会一起显示
    parent.show();

    return app.exec();
}




