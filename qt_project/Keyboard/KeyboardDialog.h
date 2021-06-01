#ifndef KEYBOARDDIALOG_H
#define KEYBOARDDIALOG_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class KeyboardDialog;
}

class KeyboardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KeyboardDialog(QWidget *parent = 0);
    ~KeyboardDialog();
private:
    //按键按下时被执行
    void keyPressEvent(QKeyEvent *event);
    //按键抬起时被执行
    void keyReleaseEvent(QKeyEvent *event);
private:
    Ui::KeyboardDialog *ui;
};

#endif // KEYBOARDDIALOG_H
