/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-09 11:54:54
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-09 12:03:14
 */
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->btn2, SIGNAL(clicked()),
        this, SLOT(on_btn_clicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn_clicked()
{
   ui->lab->setText("change label");
}
