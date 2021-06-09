/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-01 14:52:02
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-09 15:22:38
 */
#ifndef __TIMEDIALOG_H
#define __TIMEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QVBoxLayout>
#include "ui_TimeDialog.h"

class TimeDialog
    :public QDialog,
     public Ui::TimeDialog{
    Q_OBJECT
public:
    TimeDialog(void);
private slots:
    //获取时间的槽函数
    void timeClicked(void);
/*private:
    QLabel* m_labTime;
    QPushButton* m_btnTime;*/
};
#endif//__TIMEDIALOG_H




