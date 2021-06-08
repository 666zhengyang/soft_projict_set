/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-08 14:43:38
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-08 17:36:35
 */
#ifndef __CALC_H
#define __CALC_H

#include <QWidget>
#include <QLabel>
#include <QPushButton> 
#include <QLineEdit>
#include <QHBoxLayout>//水平布局器
#include <QVBoxLayout>
#include <QDoubleValidator>//验证器
#include <QTextCodec>
#include <QFont>
#include <QTime>
#include <QSlider>
#include <QSpinBox>

class MyCalc:public QWidget
{
    Q_OBJECT //Moc
public: 
    MyCalc(void);
    
private slots:
    //使能等号按钮的槽函数
    void EnableCalcButton(void);
    //计算和显示结果的槽函数
    void CalcClicked(void);  
    void TimeClicked(void);    

private:
    QLabel* m_labTime;
    QPushButton* m_btnTime;
    QLabel* m_test_label;
    QLabel* m_label;
    QPushButton* m_close_label;
    QPushButton* m_pushButton;
    QLineEdit* m_leftEdit;
    QLineEdit* m_rightEdit;
    QLineEdit* m_resultEdit;
    QHBoxLayout* m_layout;
    QVBoxLayout* m_layout2;
    QSlider* m_slider;
    QSpinBox* m_spinbox;
};

#endif//__CALC_H
