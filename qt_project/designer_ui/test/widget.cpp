#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->rBtnBlue,SIGNAL(clicked()),this,SLOT(set_text_font_color()));
    connect(ui->rBtnRed,SIGNAL(clicked()),this,SLOT(set_text_font_color()));
    connect(ui->rBtnBlack,SIGNAL(clicked()),this,SLOT(set_text_font_color()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_chkBoxUnder_clicked(bool checked)
{
    QFont font=ui->textBrowser->font();
    font.setUnderline(checked);
    ui->textBrowser->setFont(font);
}

void Widget::on_chkBoxItalic_clicked(bool checked)
{
    QFont font = ui->textBrowser->font();
    font.setStrikeOut(checked);
    ui->textBrowser->setFont(font);
}

void Widget::on_chkBoxBold_clicked(bool checked)
{
    QFont font = ui->textBrowser->font();
    font.setBold(checked);
    ui->textBrowser->setFont(font);
}

void Widget::set_text_font_color()
{
    QPalette plet = ui->textBrowser->palette();
    if (ui->rBtnBlue->isChecked())
        plet.setColor(QPalette::Text,Qt::blue);
    else if (ui->rBtnRed->isChecked())
       plet.setColor(QPalette::Text,Qt::red);
    else if (ui->rBtnBlack->isChecked())
        plet.setColor(QPalette::Text,Qt::black);
    else
       plet.setColor(QPalette::Text,Qt::black);
     ui->textBrowser->setPalette(plet);
}
