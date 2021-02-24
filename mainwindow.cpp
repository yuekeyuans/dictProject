#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loaddict.h"
#include "additem.h"
#include <QtWidgets>
#include "webviewwitheditor.h"
#include "QMap"
#include "QTextCodec"
#include "helppage.h"
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
    initSideBar();
    initItemPage();
    initImportExport();
}

void MainWindow::initMainPage(){

    ui->mainToolBar->hide();
    QString appPath = QCoreApplication::applicationDirPath() + "/";

    splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget (_sideBar = new SideBar(this));

    stackedWidget = new QStackedWidget(this);
    routers.append(Router("defaultPage", 0, _defaultPage = new DefaultPage(this)));
    routers.append(Router("loadDict", 1, _loadDict = new LoadDict(this)));
    routers.append(Router("addItem", 2, _addItem = new addItem(this)));
    foreach (const Router r, routers){
        stackedWidget->addWidget(dynamic_cast<QWidget*>(r.widget));
    }
    stackedWidget->setCurrentIndex(routers.first().order);

    splitter->addWidget (stackedWidget);
    splitter->setStretchFactor (0, 1);
    splitter->setStretchFactor (1, 10);

    ui->centralLayout->addWidget (splitter);
}

// 初始化菜单栏
void MainWindow::initMenu(){
    viewMode = new QAction(tr("转到查看"),this);
    ui->menuBar->addAction (viewMode);

    homePage = new QAction(tr("主页"), this);
    ui->menuBar->addAction (homePage);

    //->字典页
    QMap<QString, QString> map;
    foreach(map, globalSetting->getSubMenu()){
        QAction* action = new QAction(check, map.value("name"), this);
        action->setIconVisibleInMenu(false);
        ui->dictMenu->addAction(action);
        connect(action, &QAction::triggered, [=]{slotOpenDict(map.value("name"));});
    }
    connect(ui->closeDict, &QAction::triggered, this, &MainWindow::slotCloseDict);
    connect(ui->createDict, &QAction::triggered, this, &MainWindow::slotCreateDict);
    connect(ui->actionDefaultPage, &QAction::triggered, [=]{_jump("defaultPage");});
    connect(ui->openDict, &QAction::triggered, [=]{
        QString path = QFileDialog::getOpenFileName(this,tr("fileDialog"), "./", tr("fileType"));
        QString name = QFileInfo(QFile(path)).baseName();
        globalSetting->addDict(name, path);
        slotOpenDict(name);
    });
    connect(viewMode, &QAction::triggered , this, &MainWindow::slotViewModeChanged);
    connect(this, &MainWindow::emitViewModeChanged, _addItem, &addItem::emitViewModeChanged);
    connect(this, &MainWindow::emitViewModeChanged, _loadDict, &LoadDict::emitViewModeChanged );

    connect(homePage, &QAction::triggered, [&]{
        _jump("loadDict");
    });

    ui->menu_export->setEnabled(false);
    ui->menu_import->setEnabled(false);
    ui->addItem->setEnabled(false);
    ui->menu_item->setEnabled(false);

}

void MainWindow::initDefaultPage(){
    connect(this->_defaultPage, &DefaultPage::emitCreateNewDict, this, &MainWindow::slotCreateDict);
    connect(this->_defaultPage, &DefaultPage::emitOpenExistDict, this, &MainWindow::slotOpenDict);
    connect(this->_defaultPage, &DefaultPage::emitOpenHelp, [=]{_jump("help", "help_guide");});
}

void MainWindow::initDictPage(){
    connect(this, &MainWindow::emitDictChanged, _loadDict, &LoadDict::load);
    connect(this, &MainWindow::emitDictChanged, _sideBar, &SideBar::slotupdateMenuItems);
    //字典页跳转事件
    connect(_loadDict, &LoadDict::emitJumpPage, _sideBar, &SideBar::slotJumpPage);
}

/**
 * @brief MainWindow::initSideBar
 */
void MainWindow::initSideBar(){
    connect(_sideBar, &SideBar::emitListClicked, [&](EntryModel *model, QString fragment) {
        _addItem->setEntryModel(model);
        _jump("addItem", fragment);
    });
    connect(_sideBar, &SideBar::emitAddEntry, [=] {
        _addItem->setEntryModel(nullptr);
        _jump("addItem");
    });
    connect(_sideBar, &SideBar::emitEntryDeleted, [=] {
        _addItem->setEntryModel(nullptr);
        _jump("addItem");
    });
    connect(_sideBar, &SideBar::emitSideBarUpdated, _addItem, &addItem::emitSideBarUpdated);
}

//initItemPage 字典项
void MainWindow::initItemPage(){
    connect(ui->addItem, &QAction::triggered, _sideBar, &SideBar::emitAddEntry);
    connect(ui->deleteItem, &QAction::triggered, _sideBar, &SideBar::emitDeleteEntry);
    connect(_addItem, &addItem::entryChanged, _sideBar, &SideBar::slotupdateMenuItems);
    connect (_addItem, &addItem::emitJumpPage, _sideBar, &SideBar::slotJumpPage);
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
    connect(_sideBar, &SideBar::emitTagExport, exports, &Export::toTag);

    imports = new Import(this);
    connect(ui->actionImportExcel, &QAction::triggered, imports, &Import::fromExcel);
    connect(imports, &Import::emitImportSucceed, _sideBar, &SideBar::slotupdateMenuItems);
}

//创建新字典
void MainWindow::slotCreateDict(){
    auto dialog = new CreateDictDialog(this);
    int result = dialog->exec();
    if(result == QDialog::Rejected){
        delete dialog;
        return;
    }
    QString name = dialog->getName();
    QString path = dialog->getPath();

    AppSqlite::instance(path, name);
    globalSetting->addDict(name, path);
    slotOpenDict (name);
    delete  dialog;
}

//打开字典
void MainWindow::slotOpenDict (QString name){
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
    emit emitDictChanged();
    slotReshapeMenu(name);
}

void MainWindow::openDict(QString path){
    path = path.replace ("\\", "/");
    QString name = globalSetting->getName (path);
    slotOpenDict (name);
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
    emit emitDictChanged ();
    slotReshapeMenu();
    _jump("defaultPage");               //跳转到默认页面
}

void MainWindow::slotViewModeChanged (){
    if(SDB == nullptr) return;
    isViewMode = !isViewMode;
    viewMode->setText (isViewMode ? "转到编辑":"转到查看");
    ui->menu_item->setEnabled (!isViewMode);
    ui->menu_export->setEnabled (!isViewMode);
    ui->menu_import->setEnabled (!isViewMode);
    ui->dictMenu->setEnabled (!isViewMode);
    emit emitViewModeChanged(isViewMode);
}

//更新submenu
void MainWindow::slotReshapeMenu(QString name){
    foreach(QAction* action, ui->dictMenu->actions()){
        if(action->objectName() == "" && !action->isSeparator()){
            ui->dictMenu->removeAction(action);
        }
    }

    QMap<QString, QString> map;
    foreach(map, globalSetting->getSubMenu()){
        QAction* action = new QAction(check, map.value("name"), this);
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
            stackedWidget->setCurrentIndex(r.order);
            r.widget->setDefaultValue (val1, val2);
        }
    }
}


void MainWindow::RegisterShellFileType(QString ext_name, QString type_name,
                                       QString description){

    bool shouldUpdate{false};

    QString hkey = "HKEY_CLASSES_ROOT\\";
    QString exeFile = "C:\\Users\\Administrator\\Desktop\\dict\\dictProject.exe";
//    QString exeFile = qApp->arguments ()[0];

    QSettings setting1(hkey + ext_name, QSettings::NativeFormat);
    setting1.setValue (".", type_name);

    QSettings settings(hkey + type_name, QSettings::NativeFormat);
    settings.setValue (".", description);

    QSettings setting3(hkey + type_name + "\\DefaultIcon", QSettings::NativeFormat);
    if(setting3.value (".", "") !=  exeFile + ",1"){
        setting3.setValue (".", exeFile + ",1");
        shouldUpdate = true;
    }

    QSettings setting4(hkey + type_name + "\\" + "\\Shell\\Open\\Command", QSettings::NativeFormat);
    if(setting4.value (".", "") != exeFile +  " \"%1\""){  // 不是 当前的exec
        setting4.setValue (".", exeFile +  " \"%1\"");
        shouldUpdate = true;
    }

    if(shouldUpdate){
        SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);
    }
}

MainWindow::~MainWindow(){
    delete ui;
    delete imports;
    delete exports;
    delete _sideBar;
    delete _addItem;
    delete _loadDict;
    delete _defaultPage;
    delete homePage;
    delete viewMode;
    delete stackedWidget;
    delete splitter;
    delete globalSetting;
}
