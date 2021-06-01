
#include "TimeDialog.h"

TimeDialog::TimeDialog()
{
    setWindowTitle("时间");
    //创建标签
    m_labTime = new QLabel(this);
    //设置label边框效果
    m_labTime->setFrameStyle(
        QFrame::Panel|QFrame::Sunken);
    //设置label文本居中对齐
    m_labTime->setAlignment(
        Qt::AlignHCenter|Qt::AlignVCenter);
    //创建获取时间的按钮对象
    m_btnTime = 
        new QPushButton("获取时间",this);

    //创建垂直布局器，用于调整大小和位置
    QVBoxLayout* layout = 
        new QVBoxLayout(this);
    layout->addWidget(m_labTime);
    layout->addWidget(m_btnTime);
    setLayout(layout);

    //连接按钮的clicked信号和自定义的槽
    connect(m_btnTime,SIGNAL(clicked()),
            this,SLOT(timeClicked()));
}
void TimeDialog::timeClicked()
{
    //currentTime():获取当前时间(QTime)
    //toString():QTime-->QString
    QString str = QTime::currentTime().toString("hh:mm::ss");
    //显示时间
    m_labTime->setText(str);
}








