/********************************************************************************
** Form generated from reading UI file 'TimeDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMEDIALOG_H
#define UI_TIMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TimeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *m_labTime;
    QPushButton *m_btnTime;

    void setupUi(QDialog *TimeDialog)
    {
        if (TimeDialog->objectName().isEmpty())
            TimeDialog->setObjectName(QStringLiteral("TimeDialog"));
        TimeDialog->resize(229, 178);
        QFont font;
        font.setPointSize(20);
        TimeDialog->setFont(font);
        verticalLayout = new QVBoxLayout(TimeDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_labTime = new QLabel(TimeDialog);
        m_labTime->setObjectName(QStringLiteral("m_labTime"));
        m_labTime->setFrameShape(QFrame::Panel);
        m_labTime->setFrameShadow(QFrame::Sunken);
        m_labTime->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_labTime);

        m_btnTime = new QPushButton(TimeDialog);
        m_btnTime->setObjectName(QStringLiteral("m_btnTime"));

        verticalLayout->addWidget(m_btnTime);


        retranslateUi(TimeDialog);

        QMetaObject::connectSlotsByName(TimeDialog);
    } // setupUi

    void retranslateUi(QDialog *TimeDialog)
    {
        TimeDialog->setWindowTitle(QApplication::translate("TimeDialog", "\346\227\266\351\227\264", Q_NULLPTR));
        m_labTime->setText(QString());
        m_btnTime->setText(QApplication::translate("TimeDialog", "\350\216\267\345\217\226\346\227\266\351\227\264", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TimeDialog: public Ui_TimeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMEDIALOG_H
