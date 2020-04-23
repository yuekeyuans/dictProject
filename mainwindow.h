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
    void slotOpenDict(QString);
    void slotCloseDict();
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

    Ui::MainWindow *ui{nullptr};
    QList<Router> routers;
    QMap<int, QString>* sortAction{nullptr};
    QList<QPair<int, QString>>* items{nullptr};

    DefaultPage* _defaultPage{nullptr};
    HelpPage* _helpPage{nullptr};
    LoadDict* _loadDict{nullptr};
    addItem* _addItem{nullptr};
    SideBar* _sideBar{nullptr};

    Import* imports{nullptr};
    Export* exports{nullptr};

    Setting* globalSetting{nullptr};
    QList<QAction*>* menuActions{nullptr};

    QIcon check{":/res/img/check.png"};
    bool loadFinish{false};

private slots:
    //跳转页面
    void _jump(const QString&, QString = "", QString = "");

signals:
    void emitLoadDict();
    void emitDictChanged();
};

#endif // MAINWINDOW_H

