/********************************************************************************
** Form generated from reading UI file 'defaultpage.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEFAULTPAGE_H
#define UI_DEFAULTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DefaultPage
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *createNewDict;
    QHBoxLayout *horizontalLayout;
    QToolButton *openHelp;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *openDict;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *dictContainer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *DefaultPage)
    {
        if (DefaultPage->objectName().isEmpty())
            DefaultPage->setObjectName(QString::fromUtf8("DefaultPage"));
        DefaultPage->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(DefaultPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(0, 50, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        createNewDict = new QToolButton(DefaultPage);
        createNewDict->setObjectName(QString::fromUtf8("createNewDict"));

        horizontalLayout_2->addWidget(createNewDict);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        openHelp = new QToolButton(DefaultPage);
        openHelp->setObjectName(QString::fromUtf8("openHelp"));

        horizontalLayout->addWidget(openHelp);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer_3);

        openDict = new QHBoxLayout();
        openDict->setObjectName(QString::fromUtf8("openDict"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        openDict->addItem(horizontalSpacer);

        dictContainer = new QVBoxLayout();
        dictContainer->setObjectName(QString::fromUtf8("dictContainer"));
        label = new QLabel(DefaultPage);
        label->setObjectName(QString::fromUtf8("label"));

        dictContainer->addWidget(label);


        openDict->addLayout(dictContainer);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        openDict->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(openDict);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(DefaultPage);

        QMetaObject::connectSlotsByName(DefaultPage);
    } // setupUi

    void retranslateUi(QWidget *DefaultPage)
    {
        DefaultPage->setWindowTitle(QCoreApplication::translate("DefaultPage", "Form", nullptr));
        createNewDict->setText(QCoreApplication::translate("DefaultPage", "\345\210\233\345\273\272\346\226\260\345\255\227\345\205\270", nullptr));
        openHelp->setText(QCoreApplication::translate("DefaultPage", "\346\237\245\347\234\213\345\270\256\345\212\251", nullptr));
        label->setText(QCoreApplication::translate("DefaultPage", "\346\211\223\345\274\200\345\255\227\345\205\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DefaultPage: public Ui_DefaultPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEFAULTPAGE_H
