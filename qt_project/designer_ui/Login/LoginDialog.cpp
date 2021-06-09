#include "LoginDialog.h"
#include <QPushButton>
LoginDialog::LoginDialog(void)
{
    setupUi(this);

    //点击Ok按钮发送信号：accepted
    connect(m_btnBox,SIGNAL(accepted()),
            this,SLOT(onAccepted()));
    //点击Cancle按钮发送信号:rejected
    connect(m_btnBox,SIGNAL(rejected()),
            this,SLOT(onRejected()));
    //将Ok改成确定，Cancel改成取消
    m_btnBox->button(QDialogButtonBox::Ok
            )->setText("确定");
    m_btnBox->button(QDialogButtonBox::Cancel
            )->setText("取消");
}
void LoginDialog::onAccepted(void)
{
    //如果用于名和密码是tarena/123456则提示
    //登陆成功，否则提示登陆失败
    if(m_username->text() == "tarena" && 
        m_password->text() == "123456"){
        qDebug("登陆成功！");
        close();//关闭登陆窗口
        qDebug("显示主界面...");
    }
    else{
        //创建消息提示框
        QMessageBox msgBox(
            QMessageBox::Critical,//图标
            windowTitle(),//标题
            "用户名或密码错误!",//提示消息
            QMessageBox::Ok,//按钮
            this);//父窗口指针
        //Ok-->确定
        msgBox.setButtonText(
                QMessageBox::Ok,"确定");

        //显示消息提示框,并进入事件循环
        //点击Ok按钮会自动退出事件循环
        msgBox.exec();
    }
}
void LoginDialog::onRejected(void)
{
    //添加确定退去的提示
    QMessageBox msgBox(
        QMessageBox::Question,
        windowTitle(),
        "确定要退出吗？",
        QMessageBox::No|QMessageBox::Yes,
        this);
    //No->取消，Yes->确定
    msgBox.setButtonText(
            QMessageBox::No,"取消");
    msgBox.setButtonText(
            QMessageBox::Yes,"确定");

    //显示提示框，点击上面的Yes或No都会退出
    //但是exec返回结果不同，如果点击Yes返回
    //QMessageBox::Yes
    if(msgBox.exec() == QMessageBox::Yes){
        close();
    }
}








