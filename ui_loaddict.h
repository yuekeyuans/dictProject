/********************************************************************************
** Form generated from reading UI file 'loaddict.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADDICT_H
#define UI_LOADDICT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadDict
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *container;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *title;
    QPushButton *save;

    void setupUi(QWidget *LoadDict)
    {
        if (LoadDict->objectName().isEmpty())
            LoadDict->setObjectName(QString::fromUtf8("LoadDict"));
        LoadDict->resize(400, 300);
        horizontalLayout = new QHBoxLayout(LoadDict);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        container = new QVBoxLayout();
        container->setObjectName(QString::fromUtf8("container"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        title = new QLineEdit(LoadDict);
        title->setObjectName(QString::fromUtf8("title"));
        title->setEnabled(false);

        horizontalLayout_2->addWidget(title);

        save = new QPushButton(LoadDict);
        save->setObjectName(QString::fromUtf8("save"));

        horizontalLayout_2->addWidget(save);


        container->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(container);


        retranslateUi(LoadDict);

        QMetaObject::connectSlotsByName(LoadDict);
    } // setupUi

    void retranslateUi(QWidget *LoadDict)
    {
        LoadDict->setWindowTitle(QCoreApplication::translate("LoadDict", "Form", nullptr));
        save->setText(QCoreApplication::translate("LoadDict", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoadDict: public Ui_LoadDict {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADDICT_H
