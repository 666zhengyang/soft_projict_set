#include "threaddialog.h"
#include "ui_threaddialog.h"

ThreadDialog::ThreadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThreadDialog)
{
    ui->setupUi(this);
}

ThreadDialog::~ThreadDialog()
{
    delete ui;
}
//开始按钮的槽函数
void ThreadDialog::on_startButton_clicked()
{
    //开启两个子线程
    threadA.start();
    threadB.start();
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}
//停止按钮的槽函数
void ThreadDialog::on_stopButton_clicked()
{
    //终止两个子线程
    threadA.terminate();
    threadA.wait();
    threadB.terminate();
    threadB.wait();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}







