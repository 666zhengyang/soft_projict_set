/*
 * @Descripttion: Copyright (C) SHENZHEN JoyLife Robot Co.
 * @version: v0.01
 * @Author: zhengyang
 * @Date: 2021-06-08 14:43:34
 * @LastEditors: zhengyang
 * @LastEditTime: 2021-06-09 20:23:01
 */
#include "calc.h"

MyCalc::MyCalc(void)
{
    resize(1000, 1000);
    setWindowTitle("calc");
    
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->move(220, 800);
    m_slider->setRange(0,100);

    m_spinbox = new QSpinBox(this);
    m_spinbox->move(120, 800);
    m_spinbox->setRange(0, 100);

    QFont ft;
    ft.setPointSize(8);
    
    m_test_label = new QLabel("calc_test_label", this);
    m_test_label->setFont(ft);

    m_close_label = new QPushButton("close_label", this);

    m_timerlab = new QLabel(this);
    //设置label边框效果
    m_timerlab->setFrameStyle(
        QFrame::Panel|QFrame::Sunken);
    //设置label文本居中对齐
    m_timerlab->setAlignment(
        Qt::AlignHCenter|Qt::AlignVCenter);
    m_pTimer = new QTimer;
    m_pTimer->setTimerType(Qt::PreciseTimer); // 3.设置定时器对象精确度模式
    m_pTimer->start(1000);// 5. 开启定时器
    m_timerlab->move(500, 500);
    
    m_test_label->move(100 , 500);
    m_close_label->move(100, 600);
    
    m_label = new QLabel("+", this);
    m_pushButton = new QPushButton(QString::fromLocal8Bit("等号"), this);
    m_leftEdit = new  QLineEdit(this);
    m_leftEdit->setAlignment(Qt::AlignRight);
    m_leftEdit->setValidator(new QDoubleValidator(this));

    m_rightEdit = new  QLineEdit(this);
    m_rightEdit->setAlignment(Qt::AlignRight);
    m_rightEdit->setValidator(new QDoubleValidator(this));
    
    m_resultEdit =  new  QLineEdit(this);
    m_resultEdit->setAlignment(Qt::AlignRight);
    m_resultEdit->setReadOnly(true);//只读

    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_leftEdit);
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_rightEdit);
    m_layout->addWidget(m_pushButton);
    m_layout->addWidget(m_resultEdit);

    setLayout(m_layout);

    m_labTime = new QLabel(this);
    //设置label边框效果
    m_labTime->setFrameStyle(
        QFrame::Panel|QFrame::Sunken);
    //设置label文本居中对齐
    m_labTime->setAlignment(
        Qt::AlignHCenter|Qt::AlignVCenter);
    //创建获取时间的按钮对象
    m_btnTime = new QPushButton("获取时间",this);
    m_labTime->move(0, 100);
    m_btnTime->move(0, 300);

    // 信号和槽连接
    // 左右操作数文本改变时，
    // 发送信号textChanged()
    // this表示当前父窗口指针
    // 如果信号接受对象是当前父窗口，那么
    // connect的第三个参数一定是this
    connect(m_leftEdit,
        SIGNAL(textChanged(QString)),
        this,SLOT(EnableCalcButton()));
    connect(m_rightEdit,
        SIGNAL(textChanged(QString)),
        this,SLOT(EnableCalcButton()));
    //点击等号按钮发送信号clicked
    connect(m_pushButton, SIGNAL(clicked()),
        this,SLOT(CalcClicked()));

    connect(m_close_label, SIGNAL(clicked()), m_test_label, SLOT(close(void)));

        //滑块滑动选值框数值随之改变
    connect(m_slider,
            SIGNAL(valueChanged(int)),
            m_spinbox,SLOT(setValue(int)));

    //选值框数值改变滑动也要随之滑动
    connect(m_spinbox,
            SIGNAL(valueChanged(int)),
            m_slider,SLOT(setValue(int)));

        //连接按钮的clicked信号和自定义的槽
    connect(m_btnTime,SIGNAL(clicked()),
            this,SLOT(TimeClicked()));
    
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(TimeOut_Slots()));
}

void MyCalc::EnableCalcButton(void)
{
    bool bleftOk;
    bool brightOk;
    m_leftEdit->text().toDouble(&bleftOk);
    m_rightEdit->text().toDouble(&brightOk);
    // 检查左右操作数是否为有效的数字
    // text():获取组件的文本(QString)
    // toDouble:QString转换为double，参数保存
    // 转换是否成功
    // 当左右操作数都为有效数字使能等号按钮
    // 否则设置禁用
    m_resultEdit->setEnabled(bleftOk && brightOk);
}

void MyCalc::CalcClicked(void)
{
    // qDebug() << "test2";
    // 计算结果
    double res = m_leftEdit->text().toDouble()
        + m_rightEdit->text().toDouble();
    //将计算结果数字转换为QString在显示
    //number():double--》QString
    QString str = QString::number(res,'g',15);
    m_resultEdit->setText(str);
    close();
}

void MyCalc::TimeClicked(void)
{
    QString str = QTime::currentTime().toString("hh:mm::ss");
    m_labTime->setText(str);
}

void MyCalc::TimeOut_Slots(void)
{
    QString str = QTime::currentTime().toString("hh:mm::ss");
    m_timerlab->setText(str);
}