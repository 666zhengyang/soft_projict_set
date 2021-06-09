/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *lab;
    QPushButton *btn;
    QPushButton *btn2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(660, 510);
        lab = new QLabel(Widget);
        lab->setObjectName(QStringLiteral("lab"));
        lab->setGeometry(QRect(130, 150, 71, 20));
        btn = new QPushButton(Widget);
        btn->setObjectName(QStringLiteral("btn"));
        btn->setGeometry(QRect(110, 210, 106, 29));
        btn2 = new QPushButton(Widget);
        btn2->setObjectName(QStringLiteral("btn2"));
        btn2->setGeometry(QRect(240, 210, 106, 29));

        retranslateUi(Widget);
        QObject::connect(btn, SIGNAL(clicked()), lab, SLOT(close()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        lab->setText(QApplication::translate("Widget", "hello qt", Q_NULLPTR));
        btn->setText(QApplication::translate("Widget", "closelab", Q_NULLPTR));
        btn2->setText(QApplication::translate("Widget", "changelab", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
