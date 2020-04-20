/********************************************************************************
** Form generated from reading UI file 'additem.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEM_H
#define UI_ADDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addItem
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *saveButton;

    void setupUi(QWidget *addItem)
    {
        if (addItem->objectName().isEmpty())
            addItem->setObjectName(QString::fromUtf8("addItem"));
        addItem->resize(400, 300);
        verticalLayout = new QVBoxLayout(addItem);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, -1, -1);
        lineEdit = new QLineEdit(addItem);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        saveButton = new QPushButton(addItem);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout->addWidget(saveButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(addItem);

        QMetaObject::connectSlotsByName(addItem);
    } // setupUi

    void retranslateUi(QWidget *addItem)
    {
        addItem->setWindowTitle(QCoreApplication::translate("addItem", "Form", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("addItem", "\350\257\267\350\276\223\345\205\245\346\235\241\347\233\256\345\220\215\347\247\260", nullptr));
        saveButton->setText(QCoreApplication::translate("addItem", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addItem: public Ui_addItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEM_H
