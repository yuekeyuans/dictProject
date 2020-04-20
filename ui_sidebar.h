/********************************************************************************
** Form generated from reading UI file 'sidebar.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIDEBAR_H
#define UI_SIDEBAR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SideBar
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QLineEdit *searchBox;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *addItemButton;
    QToolButton *deleteItemButton;
    QComboBox *sortBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SideBar)
    {
        if (SideBar->objectName().isEmpty())
            SideBar->setObjectName(QString::fromUtf8("SideBar"));
        SideBar->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(SideBar);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolButton = new QToolButton(SideBar);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/img/option.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);

        horizontalLayout->addWidget(toolButton);

        searchBox = new QLineEdit(SideBar);
        searchBox->setObjectName(QString::fromUtf8("searchBox"));

        horizontalLayout->addWidget(searchBox);


        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(SideBar);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout->addWidget(listWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addItemButton = new QToolButton(SideBar);
        addItemButton->setObjectName(QString::fromUtf8("addItemButton"));
        addItemButton->setMinimumSize(QSize(20, 20));
        addItemButton->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(addItemButton);

        deleteItemButton = new QToolButton(SideBar);
        deleteItemButton->setObjectName(QString::fromUtf8("deleteItemButton"));
        deleteItemButton->setMinimumSize(QSize(20, 20));
        deleteItemButton->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(deleteItemButton);

        sortBox = new QComboBox(SideBar);
        sortBox->setObjectName(QString::fromUtf8("sortBox"));
        sortBox->setMinimumSize(QSize(0, 20));
        sortBox->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(sortBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(SideBar);

        QMetaObject::connectSlotsByName(SideBar);
    } // setupUi

    void retranslateUi(QWidget *SideBar)
    {
        SideBar->setWindowTitle(QCoreApplication::translate("SideBar", "Form", nullptr));
#if QT_CONFIG(statustip)
        toolButton->setStatusTip(QCoreApplication::translate("SideBar", "\346\220\234\347\264\242\351\200\211\351\241\271", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        toolButton->setWhatsThis(QCoreApplication::translate("SideBar", "\346\220\234\347\264\242\351\200\211\351\241\271", nullptr));
#endif // QT_CONFIG(whatsthis)
        toolButton->setText(QString());
        addItemButton->setText(QCoreApplication::translate("SideBar", "+", nullptr));
        deleteItemButton->setText(QCoreApplication::translate("SideBar", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SideBar: public Ui_SideBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIDEBAR_H
