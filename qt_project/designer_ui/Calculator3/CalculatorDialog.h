#ifndef CALCULATORDIALOG_H
#define CALCULATORDIALOG_H

#include <QDialog>
//#include "ui_CalculatorDialog.h"
namespace Ui {
class CalculatorDialog;
}

class CalculatorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalculatorDialog(QWidget *parent = 0);
    ~CalculatorDialog();
private slots:
    void enableCalcButton(void);
    void calcClicked(void);

private:
    //ui->界面类中代码
    Ui::CalculatorDialog *ui;
};

#endif // CALCULATORDIALOG_H



