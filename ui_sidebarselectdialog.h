/********************************************************************************
** Form generated from reading UI file 'sidebarselectdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEBARSELECTDIALOG_H
#define UI_SIDEBARSELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SideBarSelectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_5;
    QRadioButton *radioButton;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SideBarSelectDialog)
    {
        if (SideBarSelectDialog->objectName().isEmpty())
            SideBarSelectDialog->setObjectName(QString::fromUtf8("SideBarSelectDialog"));
        SideBarSelectDialog->resize(398, 292);
        verticalLayout = new QVBoxLayout(SideBarSelectDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(SideBarSelectDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout->addWidget(checkBox_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout_5->addWidget(radioButton);


        verticalLayout_4->addLayout(verticalLayout_5);


        verticalLayout_2->addWidget(groupBox);

        label = new QLabel(SideBarSelectDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);


        verticalLayout->addLayout(verticalLayout_2);

        buttonBox = new QDialogButtonBox(SideBarSelectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SideBarSelectDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SideBarSelectDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SideBarSelectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SideBarSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *SideBarSelectDialog)
    {
        SideBarSelectDialog->setWindowTitle(QCoreApplication::translate("SideBarSelectDialog", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("SideBarSelectDialog", "\346\220\234\347\264\242\351\200\211\351\241\271", nullptr));
        checkBox->setText(QCoreApplication::translate("SideBarSelectDialog", "\346\220\234\347\264\242\346\240\207\351\242\230", nullptr));
        checkBox_2->setText(QCoreApplication::translate("SideBarSelectDialog", "\346\220\234\347\264\242\345\206\205\345\256\271", nullptr));
        radioButton->setText(QCoreApplication::translate("SideBarSelectDialog", "\351\232\220\350\227\217\345\206\205\345\256\271", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SideBarSelectDialog: public Ui_SideBarSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEBARSELECTDIALOG_H
