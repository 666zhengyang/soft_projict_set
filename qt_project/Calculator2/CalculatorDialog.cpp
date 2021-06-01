#include "CalculatorDialog.h"
#include <QDebug>//打印调试
//构造函数
CalculatorDialog::CalculatorDialog(void)
{
    //调用基类中setupUi完成界面初始化
    setupUi(this);

    //设置窗口标题
    //setWindowTitle("加法计算器");
    //创建左操作数对象
    //m_editX = new QLineEdit(this);
    //设置输入文本的对齐方式:右对齐
    //m_editX->setAlignment(Qt::AlignRight);
    //设置验证器，只能输入数字
    m_editX->setValidator(
            new QDoubleValidator(this));
    //创建右操作数对象
    //m_editY = new QLineEdit(this);
    //m_editY->setAlignment(Qt::AlignRight);
    m_editY->setValidator(
            new QDoubleValidator(this));
    //创建加号
    //m_label = new QLabel("+",this);
    //创建等号按钮
    //m_btnCalc = new QPushButton("=",this);
    //禁用等号按钮(灰色不能点击)
    //m_btnCalc->setEnabled(false);

    //创建显示结果
    //m_editZ = new QLineEdit(this);
    //m_editZ->setAlignment(Qt::AlignRight);
    //m_editZ->setReadOnly(true);//只读
/*
    //创建水平布局器
    QHBoxLayout* layout = 
        new QHBoxLayout(this);
    //向布局器中添加组件(从左到右)
    layout->addWidget(m_editX);
    layout->addWidget(m_label);
    layout->addWidget(m_editY);
    layout->addWidget(m_btnCalc);
    layout->addWidget(m_editZ);
    //设置布局器，它可以自动调整每个
    //组件的大小和位置
    setLayout(layout);
*/
    //信号和槽连接
    //左右操作数文本改变时，
    //发送信号textChanged()
    //this表示当前父窗口指针
    //如果信号接受对象是当前父窗口，那么
    //connect的第三个参数一定是this
    connect(m_editX,
        SIGNAL(textChanged(QString)),
        this,SLOT(enableCalcButton()));
    connect(m_editY,
        SIGNAL(textChanged(QString)),
        this,SLOT(enableCalcButton()));
    //点击等号按钮发送信号clicked
    connect(m_btnCalc,SIGNAL(clicked()),
        this,SLOT(calcClicked()));
}
//使能等号按钮的槽函数
void CalculatorDialog::enableCalcButton()
{
    //qDebug("test1");
    bool bXOk;
    bool bYOk;
    //检查左右操作数是否为有效的数字
    //text():获取组件的文本(QString)
    //toDouble:QString转换为double，参数保存
    //转换是否成功
    m_editX->text().toDouble(&bXOk);
    m_editY->text().toDouble(&bYOk);
    
    //当左右操作数都为有效数字使能等号按钮
    //否则设置禁用
    m_btnCalc->setEnabled(bXOk && bYOk);
}
//计算和显示结果的槽函数
void CalculatorDialog::calcClicked()
{
    //qDebug() << "test2";
    //计算结果
    double res = m_editX->text().toDouble()
        + m_editY->text().toDouble();
    //将计算结果数字转换为QString在显示
    //number():double--》QString
    QString str = QString::number(res,'g',15);
    //设置显示结果
    //setText(QString):设置组件文件内容
    m_editZ->setText(str);
}








