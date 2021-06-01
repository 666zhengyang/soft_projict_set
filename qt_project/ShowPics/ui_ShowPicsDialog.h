/********************************************************************************
** Form generated from reading UI file 'ShowPicsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWPICSDIALOG_H
#define UI_SHOWPICSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ShowPicsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_btnPrev;
    QPushButton *m_btnNext;

    void setupUi(QDialog *ShowPicsDialog)
    {
        if (ShowPicsDialog->objectName().isEmpty())
            ShowPicsDialog->setObjectName(QStringLiteral("ShowPicsDialog"));
        ShowPicsDialog->resize(416, 347);
        QFont font;
        font.setPointSize(18);
        ShowPicsDialog->setFont(font);
        verticalLayout = new QVBoxLayout(ShowPicsDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(ShowPicsDialog);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_btnPrev = new QPushButton(ShowPicsDialog);
        m_btnPrev->setObjectName(QStringLiteral("m_btnPrev"));

        horizontalLayout->addWidget(m_btnPrev);

        m_btnNext = new QPushButton(ShowPicsDialog);
        m_btnNext->setObjectName(QStringLiteral("m_btnNext"));

        horizontalLayout->addWidget(m_btnNext);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ShowPicsDialog);

        QMetaObject::connectSlotsByName(ShowPicsDialog);
    } // setupUi

    void retranslateUi(QDialog *ShowPicsDialog)
    {
        ShowPicsDialog->setWindowTitle(QApplication::translate("ShowPicsDialog", "\345\233\276\345\233\276\347\247\200", Q_NULLPTR));
        m_btnPrev->setText(QApplication::translate("ShowPicsDialog", "\344\270\212\344\270\200\345\274\240", Q_NULLPTR));
        m_btnNext->setText(QApplication::translate("ShowPicsDialog", "\344\270\213\344\270\200\345\274\240", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ShowPicsDialog: public Ui_ShowPicsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWPICSDIALOG_H
