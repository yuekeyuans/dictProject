/********************************************************************************
** Form generated from reading UI file 'createdictdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEDICTDIALOG_H
#define UI_CREATEDICTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CreateDictDialog
{
public:
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *path;
    QPushButton *openFile;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *name;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CreateDictDialog)
    {
        if (CreateDictDialog->objectName().isEmpty())
            CreateDictDialog->setObjectName(QString::fromUtf8("CreateDictDialog"));
        CreateDictDialog->resize(361, 111);
        verticalLayout = new QVBoxLayout(CreateDictDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(CreateDictDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        path = new QLineEdit(CreateDictDialog);
        path->setObjectName(QString::fromUtf8("path"));
        path->setEnabled(false);

        horizontalLayout_3->addWidget(path);

        openFile = new QPushButton(CreateDictDialog);
        openFile->setObjectName(QString::fromUtf8("openFile"));

        horizontalLayout_3->addWidget(openFile);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(CreateDictDialog);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        name = new QLineEdit(CreateDictDialog);
        name->setObjectName(QString::fromUtf8("name"));
        name->setEnabled(false);

        horizontalLayout_2->addWidget(name);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);

        buttonBox = new QDialogButtonBox(CreateDictDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(CreateDictDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), CreateDictDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CreateDictDialog);
    } // setupUi

    void retranslateUi(QDialog *CreateDictDialog)
    {
        CreateDictDialog->setWindowTitle(QCoreApplication::translate("CreateDictDialog", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("CreateDictDialog", "\346\226\207\344\273\266\344\275\215\347\275\256\357\274\232", nullptr));
        openFile->setText(QCoreApplication::translate("CreateDictDialog", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        label->setText(QCoreApplication::translate("CreateDictDialog", "\345\255\227\345\205\270\345\220\215\347\247\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateDictDialog: public Ui_CreateDictDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEDICTDIALOG_H
