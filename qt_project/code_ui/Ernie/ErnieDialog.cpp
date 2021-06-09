#include "ErnieDialog.h"
#include "ui_ErnieDialog.h"

ErnieDialog::ErnieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErnieDialog)
{
    ui->setupUi(this);
    //初始化状态标记
    isStarted = false;
    //加载图片到容器m_vecPhotos
    loadPhotos("./photos");
    //初始化索引
    m_index = 0;
    //设置随机种子
    qsrand(QTime::currentTime().msec());
}

ErnieDialog::~ErnieDialog()
{
    delete ui;
}
//开始按钮对应的槽函数
void ErnieDialog::on_pushButton_clicked()
{
    if(isStarted == false){
        //开启摇奖
        isStarted = true;
        ui->pushButton->setText("停止摇奖");
        //开启定时器,50毫秒
        m_idtPhoto = startTimer(50);
    }
    else{
        //停止摇奖
        isStarted = false;
        ui->pushButton->setText("开始摇奖");
        //关闭定时器
        killTimer(m_idtPhoto);
    }
}
//加载指定目录下的照片
void ErnieDialog::loadPhotos(const QString& path)
{
    //创建目录对象
    QDir dir(path);
    //遍历当前目录下图片
    foreach(QString file,dir.entryList(QDir::Files)){
        //qDebug() << file;
        //根据文件名创建对应的图片对象:./photos/xx.jpg
        QImage image(path+"/"+file);
        //保存图片到容器
        m_vecPhotos << image;
    }
    //递归遍历子目录
    foreach(QString subDir,
        dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot)){
        loadPhotos(path+"/"+subDir);
    }
}
//定时器事件，每次定时器到时后被触发
void ErnieDialog::timerEvent(QTimerEvent *)
{
    //随机获取一个图片索引
    m_index = qrand() % m_vecPhotos.size();
    //触发绘图操作
    update();
}
//绘图事件
void ErnieDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rcPhoto = ui->frame->frameRect();
    rcPhoto.translate(ui->frame->pos());
    painter.drawImage(rcPhoto,m_vecPhotos[m_index]);
}






