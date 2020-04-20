/********************************************************************************
** Form generated from reading UI file 'helppage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPPAGE_H
#define UI_HELPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HelpPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *container;

    void setupUi(QWidget *HelpPage)
    {
        if (HelpPage->objectName().isEmpty())
            HelpPage->setObjectName(QString::fromUtf8("HelpPage"));
        HelpPage->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(HelpPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(8, 0, -1, 0);
        container = new QVBoxLayout();
        container->setSpacing(0);
        container->setObjectName(QString::fromUtf8("container"));

        verticalLayout_2->addLayout(container);


        retranslateUi(HelpPage);

        QMetaObject::connectSlotsByName(HelpPage);
    } // setupUi

    void retranslateUi(QWidget *HelpPage)
    {
        HelpPage->setWindowTitle(QCoreApplication::translate("HelpPage", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HelpPage: public Ui_HelpPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPPAGE_H
