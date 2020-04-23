#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additem.h"
#include <QtWidgets>
#include "webviewwitheditor.h"
#include "QMap"
#include "QTextCodec"
#include "helppage.h"
#include "loaddict.h"
#include "additem.h"
#include "extra/createdictdialog.h"
#include "data/appsqlite.h"
#include "defaultpage.h"
#include "data/entrymodel.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    globalSetting = new Setting();

    initMainPage();
    initMenu();
    initDictPage();
    initDefaultPage();
    initHelpPage();
    initSideBar();
    initItemPage();
    initImportExport();
}

void MainWindow::initMainPage(){
    ui->mainToolBar->hide();

    ui->menuContainer->addWidget (_sideBar = new SideBar(this));
    routers.append(Router("defaultPage", 0, _defaultPage = new DefaultPage(this)));
    routers.append(Router("loadDict", 1, _loadDict = new LoadDict(this)));
    routers.append(Router("help", 2, _helpPage = new HelpPage(this)));
    routers.append(Router("addItem", 3, _addItem = new addItem(this)));
    foreach (const Router r, routers){
        ui->stackWidget->addWidget(dynamic_cast<QWidget*>(r.widget));
    }
    ui->stackWidget->setCurrentIndex(routers.first().order);
}

// 初始化菜单栏
void MainWindow::initMenu(){
    //字典页
    menuActions = new QList<QAction*>();
    QMap<QString, QString> map;
    foreach(map, globalSetting->getSubMenu()){
        QAction* action = new QAction(check, map.value("name"), this);
        action->setIconVisibleInMenu(false);
        menuActions->append(action);
        ui->dictMenu->addAction(action);
        connect(action, &QAction::triggered, [=]{slotOpenDict(map.value("name"));});
    }
    connect(ui->closeDict, &QAction::triggered, this, &MainWindow::slotCloseDict);
    connect(ui->createDict, &QAction::triggered, this, &MainWindow::_createNewDict);
    connect(ui->actionDefaultPage, &QAction::triggered, [=]{_jump("defaultPage");});

    ui->menu_export->setEnabled(false);
    ui->menu_import->setEnabled(false);
    ui->addItem->setEnabled(false);
    ui->menu_item->setEnabled(false);
}


//@brief 初始化默认页面
void MainWindow::initDefaultPage(){
    connect(this->_defaultPage, &DefaultPage::emitCreateNewDict, this, &MainWindow::_createNewDict);
    connect(this->_defaultPage, &DefaultPage::emitOpenExistDict, this, &MainWindow::slotOpenDict);
    connect(this->_defaultPage, &DefaultPage::emitOpenHelp, [=]{_jump("help", "help_guide");});
}

//@brief MainWindow::initDictPage 初始化字典的页面
void MainWindow::initDictPage(){
    //加载字典
    connect(this, &MainWindow::emitLoadDict, _loadDict, &LoadDict::load);
    connect(this, &MainWindow::emitLoadDict, _sideBar, &SideBar::slotupdateMenuItems);
    //字典页跳转事件
    //connect(this->_loadDict, &LoadDict::jumps, this, &MainWindow::_jumpPage);
    //打开字典
    connect(ui->openDict, &QAction::triggered, [=]{
        QString path = QFileDialog::getOpenFileName(this,tr("fileDialog"), "./", tr("fileType"));
        QString name = QFileInfo(QFile(path)).baseName();
        globalSetting->addDict(name, path);
        slotOpenDict(name);
    });
}

//@brief MainWindow::initHelpPage 帮助页
void MainWindow::initHelpPage(){
     connect(ui->actionmarkdown, &QAction::triggered,  [=]{_jump("help", "help_md");});
     connect(ui->actionimportexport, &QAction::triggered, [=]{_jump("help", "help_importExport");});
     connect(ui->actionguide, &QAction::triggered, [=]{_jump("help", "help_guide");});
}

/**
 * @brief MainWindow::initSideBar
 */
void MainWindow::initSideBar(){
    _sideBar->setFixedWidth (200);
    connect(_sideBar, &SideBar::emitListClicked, [&](EntryModel* model){_jump("addItem", QString::number (model->id));});
    connect(_sideBar, &SideBar::emitAddEntry, [=]{this->_jump("addItem");});
    connect(_sideBar, &SideBar::emitEntryDeleted, [=]{this->_jump("addItem");});
}

//initItemPage 字典项
void MainWindow::initItemPage(){
    connect(ui->addItem, &QAction::triggered, [=]{_jump("addItem");});
    connect(ui->deleteItem, &QAction::triggered, [&]{_addItem->deletePage();});
    connect(this->_addItem, &addItem::entryChanged, _sideBar, &SideBar::slotupdateMenuItems);
}

/**
 * @brief MainWindow::initImportExport 导入导出选项
 */
void MainWindow::initImportExport(){
    exports = new Export(this);
    connect(ui->actionpdb, &QAction::triggered, exports, &Export::toPdb);
    connect(ui->actionhtml, &QAction::triggered, exports, &Export::toHtml);
    connect(ui->actionexcel, &QAction::triggered, exports, &Export::toExcel);
    connect(ui->actiondicthtml, &QAction::triggered, exports, &Export::toDictHtml);

    imports = new Import(this);
    connect(ui->actionImportExcel, &QAction::triggered, imports, &Import::importFromExcel);
    connect(imports, &Import::importSucceed, _sideBar, &SideBar::slotupdateMenuItems);
}

//创建新字典
void MainWindow::_createNewDict(){
    auto dialog = new CreateDictDialog(this);
    int result = dialog->exec();
    if(result == QDialog::Rejected){
        delete dialog;
        return;
    }
    QString name = dialog->getName();
    QString path = dialog->getPath();
    globalSetting->addDict(name, path);
    AppSqlite::instance(path, name);
    slotOpenDict(name);
    delete  dialog;
}

//打开字典
void MainWindow::slotOpenDict (QString name){
    _reshapeSubmenu(name);
    QString path = globalSetting->getPath(name);
    if(!QFile(path).exists()) return;

    AppSqlite::instance(path);

    this->setWindowTitle (SDB->dictName);
    ui->closeDict->setEnabled (true);
    ui->menu_import->setEnabled(true);
    ui->menu_export->setEnabled(true);
    ui->addItem->setEnabled(true);
    ui->menu_item->setEnabled(true);

    _jump("loadDict");
    emit emitLoadDict();
}
//关闭字典
void MainWindow::slotCloseDict(){
    ui->closeDict->setEnabled (false);
    ui->menu_import->setEnabled(false);
    ui->menu_export->setEnabled(false);
    ui->addItem->setEnabled(false);
    ui->menu_item->setEnabled(false);
    this->setWindowTitle (tr("字典"));

    _loadDict->save ();
    QThread::usleep (100);
    AppSqlite::close();

    _reshapeSubmenu();
    _jump("defaultPage");               //跳转到默认页面
}

//更新submenu
void MainWindow::_reshapeSubmenu(QString name){
    foreach(QAction* action, ui->dictMenu->actions()){
        if(action->objectName() == "" && !action->isSeparator()){
            ui->dictMenu->removeAction(action);
        }
    }
    foreach(QAction* a, *menuActions){
        menuActions->removeOne(a);
        delete a;
    }
    QMap<QString, QString> map;
    foreach(map, globalSetting->getSubMenu()){
        QAction* action = new QAction(check, map.value("name"), this);
        menuActions->append(action);
        ui->dictMenu->addAction(action);
        action->setIconVisibleInMenu(action->text() == name);
        QObject::connect(action, &QAction::triggered, [=]{
            slotOpenDict(map.value("name"));
        });
    }
    _defaultPage->updatePage();
}

//跳转
void MainWindow::_jump(const QString& page, QString val1, QString val2){
    for(Router r : routers){
        if(r.name == page){
            ui->stackWidget->setCurrentIndex(r.order);
            r.widget->setDefaultValue (val1, val2);
        }
    }
}

//所有内容不需要删除，程序退出自动删除
MainWindow::~MainWindow(){
    delete ui;
    delete menuActions;
}
