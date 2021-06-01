#ifndef __CALCULATORDIALOG_H
#define __CALCULATORDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>//水平布局器
#include <QDoubleValidator>//验证器

//当前类继承了父窗口QDialog,那么它就
//也是一个父窗口类
class CalculatorDialog:public QDialog{
    Q_OBJECT//Moc
public:
    CalculatorDialog(void);
private slots:
    //使能等号按钮的槽函数
    void enableCalcButton(void);
    //计算和显示结果的槽函数
    void calcClicked(void);
private:
    QLineEdit* m_editX;//左操作数
    QLineEdit* m_editY;//右操作数
    QLineEdit* m_editZ;//显示结果
    QLabel* m_label;//显示"+"
    QPushButton* m_btnCalc;//等号"="
};

#endif//__CALCULATORDIALOG_H









