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




