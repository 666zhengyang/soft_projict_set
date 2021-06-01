#include "ShowPicsDialog.h"
#include "ui_ShowPicsDialog.h"

ShowPicsDialog::ShowPicsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowPicsDialog)
{
    ui->setupUi(this);
    m_index = 0;
}

ShowPicsDialog::~ShowPicsDialog()
{
    delete ui;
}
//上一张按钮对应的槽函数
void ShowPicsDialog::on_m_btnPrev_clicked()
{
    if(--m_index < 0){
        m_index = 9;
    }
    update();//更新界面，触发绘图事件
}
//下一张按钮对应的槽函数
void ShowPicsDialog::on_m_btnNext_clicked()
{
    if(++m_index > 9){
        m_index = 0;
    }
    update();
}
//绘图事件的虚函数
void ShowPicsDialog::paintEvent(QPaintEvent *)
{
    qDebug("test");
    //1)创建画家对象
    QPainter painter(this);
    //2）获取要绘制图片所在矩形
    QRect rcImage = ui->frame->frameRect();
    //平移坐标，让rcImage和painter使用相同坐标
    rcImage.translate(ui->frame->pos());

    //3) 准备要绘制的图片对象,":"表示资源路径
    //":/images/m_index.jpg:"
    QImage image(":/images/" +
                 QString::number(m_index) + ".jpg");
    //4）将image画到rcImage矩形中
    painter.drawImage(rcImage,image);
}












