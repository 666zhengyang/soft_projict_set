#ifndef ERNIEDIALOG_H
#define ERNIEDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QDir>
#include <QVector>
#include <QTime>
#include <QDebug>

namespace Ui {
class ErnieDialog;
}

class ErnieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErnieDialog(QWidget *parent = 0);
    ~ErnieDialog();

private slots:
    //开始按钮对应的槽函数
    void on_pushButton_clicked();
private:
    //加载指定目录下的照片
    void loadPhotos(const QString& path);
    //定时器事件，每次定时器到时后被触发
    void timerEvent(QTimerEvent *);
    //绘图事件
    void paintEvent(QPaintEvent *);

private:
    Ui::ErnieDialog *ui;
    //容器，用于保存所有的图片对象
    QVector <QImage> m_vecPhotos;
    int m_index;//访问图片索引
    int m_idtPhoto;//切换图片的定时器
    bool isStarted;//状态标记，true开始摇奖，false停止摇奖
};

#endif // ERNIEDIALOG_H






