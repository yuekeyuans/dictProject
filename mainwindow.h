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
#include "DictSideBar/sidebar.h"
#include <QStackedWidget>
#include <QSplitter>
#include <Windows.h>
#include <winreg.h>
#include <ShlObj_core.h>
#include <tchar.h>
#include "link-anchor/linkanchorwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void RegisterShellFileType(
        QString ext_name, QString type_name, QString description);
    void openDict(QString path);

public slots:
        void slotCreateDict();
    void slotOpenDict(QString);
    void slotCloseDict();
    void slotReshapeMenu(QString name = "");
    void slotViewModeChanged();

private:

    bool initUi();

    //new
    void initMainPage();
    void initDefaultPage();
    void initDictPage();
    void initItemPage();
    void initImportExport();
    void initSideBar();
    void initMenu();

    QSplitter* splitter{nullptr};
    QStackedWidget* stackedWidget;
    QAction* viewMode{nullptr};
    QAction* homePage{nullptr};

    Ui::MainWindow *ui{nullptr};
    QList<Router> routers;

    DefaultPage* _defaultPage{nullptr};
    LoadDict* _loadDict{nullptr};
    addItem* _addItem{nullptr};
    SideBar* _sideBar{nullptr};

    Import* imports{nullptr};
    Export* exports{nullptr};

    Setting* globalSetting{nullptr};

    QIcon check{":/res/img/check.png"};
    QIcon view_on{":/res/img/view-ons.png"};
    QIcon view_off{":/res/img/view-off.png"};
    bool loadFinish{false};
    bool isViewMode{false};

private slots:
    //跳转页面
    void _jump(const QString&, QString = "", QString = "");

signals:
    void emitDictChanged();
    void emitViewModeChanged(bool);
};

#endif // MAINWINDOW_H

