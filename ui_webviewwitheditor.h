/********************************************************************************
** Form generated from reading UI file 'webviewwitheditor.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBVIEWWITHEDITOR_H
#define UI_WEBVIEWWITHEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WebViewWithEditor
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *container;
    QHBoxLayout *operators;
    QToolButton *prevEntry;
    QToolButton *nextEntry;
    QSpacerItem *horizontalSpacer;
    QToolButton *viewMode;
    QToolButton *scaleUp;
    QToolButton *scaleDown;

    void setupUi(QWidget *WebViewWithEditor)
    {
        if (WebViewWithEditor->objectName().isEmpty())
            WebViewWithEditor->setObjectName(QString::fromUtf8("WebViewWithEditor"));
        WebViewWithEditor->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(WebViewWithEditor);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        container = new QHBoxLayout();
        container->setObjectName(QString::fromUtf8("container"));

        verticalLayout->addLayout(container);

        operators = new QHBoxLayout();
        operators->setObjectName(QString::fromUtf8("operators"));
        prevEntry = new QToolButton(WebViewWithEditor);
        prevEntry->setObjectName(QString::fromUtf8("prevEntry"));
        prevEntry->setToolTipDuration(0);
        prevEntry->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/res/img/Previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        prevEntry->setIcon(icon);

        operators->addWidget(prevEntry);

        nextEntry = new QToolButton(WebViewWithEditor);
        nextEntry->setObjectName(QString::fromUtf8("nextEntry"));
        nextEntry->setToolTipDuration(0);
        nextEntry->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/res/img/Next.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextEntry->setIcon(icon1);

        operators->addWidget(nextEntry);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        operators->addItem(horizontalSpacer);

        viewMode = new QToolButton(WebViewWithEditor);
        viewMode->setObjectName(QString::fromUtf8("viewMode"));
        viewMode->setToolTipDuration(-3);
        viewMode->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/res/img/view.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/res/img/view_on.png"), QSize(), QIcon::Normal, QIcon::On);
        viewMode->setIcon(icon2);
        viewMode->setCheckable(false);

        operators->addWidget(viewMode);

        scaleUp = new QToolButton(WebViewWithEditor);
        scaleUp->setObjectName(QString::fromUtf8("scaleUp"));
        scaleUp->setToolTipDuration(0);
        scaleUp->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/res/img/scaleup.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/res/img/scale_up.png"), QSize(), QIcon::Normal, QIcon::On);
        scaleUp->setIcon(icon3);

        operators->addWidget(scaleUp);

        scaleDown = new QToolButton(WebViewWithEditor);
        scaleDown->setObjectName(QString::fromUtf8("scaleDown"));
        scaleDown->setToolTipDuration(0);
        scaleDown->setStyleSheet(QString::fromUtf8("border:none;"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/res/img/scaledown.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/res/img/scale_down.png"), QSize(), QIcon::Normal, QIcon::On);
        scaleDown->setIcon(icon4);

        operators->addWidget(scaleDown);


        verticalLayout->addLayout(operators);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(WebViewWithEditor);

        QMetaObject::connectSlotsByName(WebViewWithEditor);
    } // setupUi

    void retranslateUi(QWidget *WebViewWithEditor)
    {
        WebViewWithEditor->setWindowTitle(QCoreApplication::translate("WebViewWithEditor", "Form", nullptr));
#if QT_CONFIG(tooltip)
        prevEntry->setToolTip(QCoreApplication::translate("WebViewWithEditor", "\344\270\212\344\270\200\344\270\252\350\257\215\346\235\241", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        prevEntry->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        prevEntry->setWhatsThis(QCoreApplication::translate("WebViewWithEditor", "\344\270\212\344\270\200\344\270\252\350\257\215\346\235\241", nullptr));
#endif // QT_CONFIG(whatsthis)
        prevEntry->setText(QCoreApplication::translate("WebViewWithEditor", "...", nullptr));
#if QT_CONFIG(tooltip)
        nextEntry->setToolTip(QCoreApplication::translate("WebViewWithEditor", "\344\270\213\344\270\200\344\270\252\350\257\215\346\235\241", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        nextEntry->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(whatsthis)
        nextEntry->setWhatsThis(QCoreApplication::translate("WebViewWithEditor", "\344\270\213\344\270\200\344\270\252\350\257\215\346\235\241", nullptr));
#endif // QT_CONFIG(whatsthis)
        nextEntry->setText(QCoreApplication::translate("WebViewWithEditor", "...", nullptr));
#if QT_CONFIG(tooltip)
        viewMode->setToolTip(QCoreApplication::translate("WebViewWithEditor", "\346\237\245\347\234\213", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        viewMode->setWhatsThis(QCoreApplication::translate("WebViewWithEditor", "\346\237\245\347\234\213", nullptr));
#endif // QT_CONFIG(whatsthis)
        viewMode->setText(QString());
#if QT_CONFIG(tooltip)
        scaleUp->setToolTip(QCoreApplication::translate("WebViewWithEditor", "\346\224\276\345\244\247\351\241\265\351\235\242", nullptr));
#endif // QT_CONFIG(tooltip)
        scaleUp->setText(QCoreApplication::translate("WebViewWithEditor", "\346\224\276\345\244\247", nullptr));
#if QT_CONFIG(tooltip)
        scaleDown->setToolTip(QCoreApplication::translate("WebViewWithEditor", "\347\274\251\345\260\217\351\241\265\351\235\242", nullptr));
#endif // QT_CONFIG(tooltip)
        scaleDown->setText(QCoreApplication::translate("WebViewWithEditor", "\347\274\251\345\260\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WebViewWithEditor: public Ui_WebViewWithEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBVIEWWITHEDITOR_H
