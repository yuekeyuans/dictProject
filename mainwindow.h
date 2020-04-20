#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>

#include "data/router.h"
#include "data/setting.h"
#include "helppage.h"
#include "loaddict.h"
#include "additem.h"
#include "defaultpage.h"
#include "importExport/export.h"
#include "importExport/import.h"
#include <QApplication>
#include "sidebar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void _createNewDict();
    void _openDict(QString);
    void _closeDict();
    void _reshapeSubmenu(QString name = "");

private:

    bool initUi();

    //new
    void initMainPage();
    void initDefaultPage();
    void initDictPage();
    void initHelpPage();
    void initItemPage();
    void initImportExport();
    void initSideBar();
    void initMenu();


    Ui::MainWindow *ui;
    QList<Router> routers;
    QMap<int, QString>* sortAction;
    QList<QPair<int, QString>>* items;

    DefaultPage* _defaultPage;
    HelpPage* _helpPage;
    LoadDict* _loadDict;
    addItem* _addItem;
    SideBar* _sideBar;

    Import* imports;
    Export* exports;

    Setting* globalSetting;
    QList<QAction*> menuActions;

    bool loadFinish;

private slots:
    //跳转页面
    void _jump(const QString&, const QString& = "", const QString& = "");
    // 跳转 html
    void _jumpPage(QString);
signals:
    void emitLoadDict();
    void emitDictChanged();

    // sidebar
    void emitUpdateSideBarItems();
};

#endif // MAINWINDOW_H

