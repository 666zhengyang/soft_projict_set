#ifndef __LOGINDIALOG_H
#define __LOGINDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>//提示框
#include "ui_LoginDialog.h"

class LoginDialog:public QDialog,
                public Ui::LoginDialog{
    Q_OBJECT
public:
    LoginDialog(void);
private slots:
    //处理Ok按钮
    void onAccepted(void);
    //处理取消按钮
    void onRejected(void);
};

#endif //__LOGINDIALOG_H


