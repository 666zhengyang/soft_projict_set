#include "KeyboardDialog.h"
#include "ui_KeyboardDialog.h"
#include <iostream>
using namespace std;

KeyboardDialog::KeyboardDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardDialog)
{
    ui->setupUi(this);
}

KeyboardDialog::~KeyboardDialog()
{
    delete ui;
}
//按键按下时被执行
void KeyboardDialog::keyPressEvent(QKeyEvent *event)
{
    cout << "按键按下：" << endl;
    cout << "按键代码：" << event->key() << endl;
    //toStdString:QString-->C++:string
    cout << "按键文本：" <<
            event->text().toStdString() << endl;
}
//按键抬起时被执行
void KeyboardDialog::keyReleaseEvent(QKeyEvent *event)
{
    cout << "按键抬起：" << endl;
    cout << "按键代码：" << event->key() << endl;
    cout << "按键文本：" <<
            event->text().toStdString() << endl;
}



