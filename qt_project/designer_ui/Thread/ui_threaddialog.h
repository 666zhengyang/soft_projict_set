/********************************************************************************
** Form generated from reading UI file 'threaddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THREADDIALOG_H
#define UI_THREADDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ThreadDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *startButton;
    QPushButton *stopButton;

    void setupUi(QDialog *ThreadDialog)
    {
        if (ThreadDialog->objectName().isEmpty())
            ThreadDialog->setObjectName(QStringLiteral("ThreadDialog"));
        ThreadDialog->resize(294, 114);
        QFont font;
        font.setPointSize(20);
        ThreadDialog->setFont(font);
        horizontalLayout = new QHBoxLayout(ThreadDialog);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        startButton = new QPushButton(ThreadDialog);
        startButton->setObjectName(QStringLiteral("startButton"));

        horizontalLayout->addWidget(startButton);

        stopButton = new QPushButton(ThreadDialog);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setEnabled(false);

        horizontalLayout->addWidget(stopButton);


        retranslateUi(ThreadDialog);

        QMetaObject::connectSlotsByName(ThreadDialog);
    } // setupUi

    void retranslateUi(QDialog *ThreadDialog)
    {
        ThreadDialog->setWindowTitle(QApplication::translate("ThreadDialog", "ThreadDialog", 0));
        startButton->setText(QApplication::translate("ThreadDialog", "\345\274\200\345\247\213\346\211\223\345\215\260", 0));
        stopButton->setText(QApplication::translate("ThreadDialog", "\345\201\234\346\255\242\346\211\223\345\215\260", 0));
    } // retranslateUi

};

namespace Ui {
    class ThreadDialog: public Ui_ThreadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THREADDIALOG_H
