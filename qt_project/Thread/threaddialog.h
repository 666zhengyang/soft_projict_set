#ifndef THREADDIALOG_H
#define THREADDIALOG_H

#include <QDialog>
#include "workthread.h"

namespace Ui {
class ThreadDialog;
}

class ThreadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThreadDialog(QWidget *parent = 0);
    ~ThreadDialog();

private slots:
    void on_startButton_clicked();
    void on_stopButton_clicked();

private:
    Ui::ThreadDialog *ui;
    WorkThread threadA;
    WorkThread threadB;
};

#endif // THREADDIALOG_H



