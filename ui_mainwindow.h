/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openDict;
    QAction *closeDict;
    QAction *importDict;
    QAction *exportDict;
    QAction *actionmarkdown;
    QAction *actionimportexport;
    QAction *actionexport;
    QAction *createDict;
    QAction *addItem;
    QAction *deleteItem;
    QAction *actionDefaultPage;
    QAction *actionpdb;
    QAction *actionexcel;
    QAction *actionhtml;
    QAction *actiondicthtml;
    QAction *actionsugarDict;
    QAction *actioncompactDict;
    QAction *actionImportExcel;
    QAction *actionguide;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *searchBoxLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *menuContainer;
    QVBoxLayout *functionLayout;
    QStackedWidget *stackWidget;
    QMenuBar *menuBar;
    QMenu *dictMenu;
    QMenu *menu_item;
    QMenu *menu_import;
    QMenu *menu_export;
    QMenu *menu_5;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(629, 360);
        openDict = new QAction(MainWindow);
        openDict->setObjectName(QString::fromUtf8("openDict"));
        closeDict = new QAction(MainWindow);
        closeDict->setObjectName(QString::fromUtf8("closeDict"));
        importDict = new QAction(MainWindow);
        importDict->setObjectName(QString::fromUtf8("importDict"));
        exportDict = new QAction(MainWindow);
        exportDict->setObjectName(QString::fromUtf8("exportDict"));
        actionmarkdown = new QAction(MainWindow);
        actionmarkdown->setObjectName(QString::fromUtf8("actionmarkdown"));
        actionimportexport = new QAction(MainWindow);
        actionimportexport->setObjectName(QString::fromUtf8("actionimportexport"));
        actionexport = new QAction(MainWindow);
        actionexport->setObjectName(QString::fromUtf8("actionexport"));
        createDict = new QAction(MainWindow);
        createDict->setObjectName(QString::fromUtf8("createDict"));
        addItem = new QAction(MainWindow);
        addItem->setObjectName(QString::fromUtf8("addItem"));
        deleteItem = new QAction(MainWindow);
        deleteItem->setObjectName(QString::fromUtf8("deleteItem"));
        actionDefaultPage = new QAction(MainWindow);
        actionDefaultPage->setObjectName(QString::fromUtf8("actionDefaultPage"));
        actionpdb = new QAction(MainWindow);
        actionpdb->setObjectName(QString::fromUtf8("actionpdb"));
        actionexcel = new QAction(MainWindow);
        actionexcel->setObjectName(QString::fromUtf8("actionexcel"));
        actionhtml = new QAction(MainWindow);
        actionhtml->setObjectName(QString::fromUtf8("actionhtml"));
        actiondicthtml = new QAction(MainWindow);
        actiondicthtml->setObjectName(QString::fromUtf8("actiondicthtml"));
        actionsugarDict = new QAction(MainWindow);
        actionsugarDict->setObjectName(QString::fromUtf8("actionsugarDict"));
        actioncompactDict = new QAction(MainWindow);
        actioncompactDict->setObjectName(QString::fromUtf8("actioncompactDict"));
        actionImportExcel = new QAction(MainWindow);
        actionImportExcel->setObjectName(QString::fromUtf8("actionImportExcel"));
        actionguide = new QAction(MainWindow);
        actionguide->setObjectName(QString::fromUtf8("actionguide"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, -1, 0);
        searchBoxLayout = new QHBoxLayout();
        searchBoxLayout->setSpacing(6);
        searchBoxLayout->setObjectName(QString::fromUtf8("searchBoxLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
        menuContainer = new QHBoxLayout();
        menuContainer->setSpacing(6);
        menuContainer->setObjectName(QString::fromUtf8("menuContainer"));

        verticalLayout->addLayout(menuContainer);


        searchBoxLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(searchBoxLayout);

        functionLayout = new QVBoxLayout();
        functionLayout->setSpacing(3);
        functionLayout->setObjectName(QString::fromUtf8("functionLayout"));
        stackWidget = new QStackedWidget(centralWidget);
        stackWidget->setObjectName(QString::fromUtf8("stackWidget"));

        functionLayout->addWidget(stackWidget);


        horizontalLayout_2->addLayout(functionLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 629, 23));
        dictMenu = new QMenu(menuBar);
        dictMenu->setObjectName(QString::fromUtf8("dictMenu"));
        menu_item = new QMenu(menuBar);
        menu_item->setObjectName(QString::fromUtf8("menu_item"));
        menu_import = new QMenu(menuBar);
        menu_import->setObjectName(QString::fromUtf8("menu_import"));
        menu_export = new QMenu(menuBar);
        menu_export->setObjectName(QString::fromUtf8("menu_export"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QString::fromUtf8("menu_5"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(false);
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(dictMenu->menuAction());
        menuBar->addAction(menu_item->menuAction());
        menuBar->addAction(menu_import->menuAction());
        menuBar->addAction(menu_export->menuAction());
        menuBar->addAction(menu_5->menuAction());
        dictMenu->addAction(createDict);
        dictMenu->addAction(openDict);
        dictMenu->addAction(closeDict);
        dictMenu->addSeparator();
        dictMenu->addAction(actionDefaultPage);
        dictMenu->addSeparator();
        menu_item->addAction(addItem);
        menu_item->addAction(deleteItem);
        menu_import->addAction(actionImportExcel);
        menu_export->addAction(actionpdb);
        menu_export->addAction(actionexcel);
        menu_export->addAction(actionhtml);
        menu_export->addAction(actiondicthtml);
        menu_5->addAction(actionmarkdown);
        menu_5->addAction(actionimportexport);
        menu_5->addAction(actionguide);

        retranslateUi(MainWindow);

        stackWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        openDict->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\345\255\227\345\205\270", nullptr));
        closeDict->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\345\255\227\345\205\270", nullptr));
        importDict->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\345\255\227\345\205\270", nullptr));
        exportDict->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\345\255\227\345\205\270", nullptr));
        actionmarkdown->setText(QCoreApplication::translate("MainWindow", "\346\240\207\350\256\260\350\257\255\350\250\200", nullptr));
        actionimportexport->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\345\257\274\345\207\272", nullptr));
        actionexport->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
        createDict->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\345\255\227\345\205\270", nullptr));
        addItem->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\346\235\241\347\233\256", nullptr));
        deleteItem->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\235\241\347\233\256", nullptr));
        actionDefaultPage->setText(QCoreApplication::translate("MainWindow", "\351\273\230\350\256\244\351\241\265", nullptr));
        actionpdb->setText(QCoreApplication::translate("MainWindow", "pdb \346\272\220\346\226\207\344\273\266", nullptr));
        actionexcel->setText(QCoreApplication::translate("MainWindow", "excel \350\241\250\346\240\274", nullptr));
        actionhtml->setText(QCoreApplication::translate("MainWindow", "html \347\275\221\351\241\265", nullptr));
        actiondicthtml->setText(QCoreApplication::translate("MainWindow", "dicthtml \345\255\227\345\205\270", nullptr));
        actionsugarDict->setText(QCoreApplication::translate("MainWindow", "sugarDict", nullptr));
        actioncompactDict->setText(QCoreApplication::translate("MainWindow", "compact dict", nullptr));
        actionImportExcel->setText(QCoreApplication::translate("MainWindow", "excel", nullptr));
        actionguide->setText(QCoreApplication::translate("MainWindow", "\347\250\213\345\272\217\346\214\207\345\215\227", nullptr));
        dictMenu->setTitle(QCoreApplication::translate("MainWindow", "\345\255\227\345\205\270", nullptr));
        menu_item->setTitle(QCoreApplication::translate("MainWindow", "\346\235\241\347\233\256", nullptr));
        menu_import->setTitle(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245", nullptr));
        menu_export->setTitle(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
        menu_5->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
