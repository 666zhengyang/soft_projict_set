/********************************************************************************
** Form generated from reading UI file 'ErnieDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERNIEDIALOG_H
#define UI_ERNIEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ErnieDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QPushButton *pushButton;

    void setupUi(QDialog *ErnieDialog)
    {
        if (ErnieDialog->objectName().isEmpty())
            ErnieDialog->setObjectName(QStringLiteral("ErnieDialog"));
        ErnieDialog->resize(266, 376);
        QFont font;
        font.setPointSize(18);
        ErnieDialog->setFont(font);
        verticalLayout = new QVBoxLayout(ErnieDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(ErnieDialog);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(frame);

        pushButton = new QPushButton(ErnieDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(ErnieDialog);

        QMetaObject::connectSlotsByName(ErnieDialog);
    } // setupUi

    void retranslateUi(QDialog *ErnieDialog)
    {
        ErnieDialog->setWindowTitle(QApplication::translate("ErnieDialog", "\346\221\207\345\245\226\346\234\272", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ErnieDialog", "\345\274\200\345\247\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ErnieDialog: public Ui_ErnieDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERNIEDIALOG_H
