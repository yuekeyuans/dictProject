/********************************************************************************
** Form generated from reading UI file 'menuitemwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUITEMWIDGET_H
#define UI_MENUITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuItemWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *title;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QFrame *line;
    QVBoxLayout *content_layout;
    QLabel *content;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;

    void setupUi(QWidget *MenuItemWidget)
    {
        if (MenuItemWidget->objectName().isEmpty())
            MenuItemWidget->setObjectName(QString::fromUtf8("MenuItemWidget"));
        MenuItemWidget->resize(400, 102);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MenuItemWidget->sizePolicy().hasHeightForWidth());
        MenuItemWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(MenuItemWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        title = new QLabel(MenuItemWidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setScaledContents(false);
        title->setIndent(10);

        horizontalLayout->addWidget(title);

        horizontalSpacer = new QSpacerItem(40, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox = new QCheckBox(MenuItemWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);


        verticalLayout_2->addLayout(horizontalLayout);

        line = new QFrame(MenuItemWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color:rgb(200, 200, 200)"));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(line);

        content_layout = new QVBoxLayout();
        content_layout->setObjectName(QString::fromUtf8("content_layout"));
        content = new QLabel(MenuItemWidget);
        content->setObjectName(QString::fromUtf8("content"));
        content->setTextFormat(Qt::RichText);
        content->setIndent(10);

        content_layout->addWidget(content);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        content_layout->addItem(verticalSpacer);

        line_2 = new QFrame(MenuItemWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setStyleSheet(QString::fromUtf8("color:rgb(200,200,200)"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        content_layout->addWidget(line_2);


        verticalLayout_2->addLayout(content_layout);


        retranslateUi(MenuItemWidget);

        QMetaObject::connectSlotsByName(MenuItemWidget);
    } // setupUi

    void retranslateUi(QWidget *MenuItemWidget)
    {
        MenuItemWidget->setWindowTitle(QCoreApplication::translate("MenuItemWidget", "Form", nullptr));
        title->setText(QCoreApplication::translate("MenuItemWidget", "title", nullptr));
        checkBox->setText(QString());
        content->setText(QCoreApplication::translate("MenuItemWidget", "content", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MenuItemWidget: public Ui_MenuItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUITEMWIDGET_H
