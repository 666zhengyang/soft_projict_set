#ifndef SHOWPICSDIALOG_H
#define SHOWPICSDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QDebug>

namespace Ui {
class ShowPicsDialog;
}

class ShowPicsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowPicsDialog(QWidget *parent = 0);
    ~ShowPicsDialog();

private slots:
    //上一张按钮对应的槽函数
    void on_m_btnPrev_clicked();
    //下一张按钮对应的槽函数
    void on_m_btnNext_clicked();
private:
    //绘图事件的虚函数
    void paintEvent(QPaintEvent *);
private:
    Ui::ShowPicsDialog *ui;
    int m_index;//图片索引
};

#endif // SHOWPICSDIALOG_H


