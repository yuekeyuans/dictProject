#include "headerbarmenu.h"
#include "ui_headerbarmenu.h"
#include "data/appsqlite.h"
#include "data/entrymodel.h"
#include "data/tagmodel.h"
#include <QInputDialog>

HeaderBarMenu::HeaderBarMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderBarMenu)
{
    ui->setupUi(this);
    createTageMemu ();
    connect (ui->prepareInput, &QPushButton::clicked, [&]{
        emit searchButtonClicked();
    });
    connect(ui->infoButton, &QPushButton::clicked, this, &HeaderBarMenu::slotShowInfo);
    connect(ui->addButton, &QPushButton::clicked, [&] {
        if(SDB != nullptr)
            emit emitAddEntry();
    });
    connect(ui->deleteButton, &QPushButton::clicked, [&] {
        if(SDB != nullptr)
            emit emitDeleteEntry();
    });
    connect(ui->viewHidden, &QToolButton::clicked, [&] {
        if(SDB == nullptr)
            return;
        ui->viewHidden->setIcon (isView? view_off :view_on);
        isView = !isView;
        emit emitViewHidden(isView);
    });
}

void HeaderBarMenu::createTageMemu(){
    auto menu = new QMenu(this);
    auto actionAdd = menu->addAction (tr("add tag"));
    auto actionExpand =  menu->addAction (tr("expand all tags"));
    auto actionFold = menu->addAction (tr("fold all tags"));

    connect(actionAdd, &QAction::triggered, [&]{
        QString name = QInputDialog::getText (this, tr("标签"), tr("请输入标签名"));
        if(name == "") return;
        TagModel tag;
        tag.name = name;
        tag.insert ();
        emit emitTagAdd();
    });

    connect (actionExpand, &QAction::triggered, this, &HeaderBarMenu::emitTagExpandAll);
    connect (actionFold, &QAction::triggered, this, &HeaderBarMenu::emitTagFoldAll);

    ui->tagButton->setMenu (menu);
}

void HeaderBarMenu::slotUpdate (){
    if(SDB == nullptr){
        ui->viewHidden->setIcon (view_off);
        this->isView = false;
    }
}

void HeaderBarMenu::slotShowInfo (){
    if(SDB == nullptr) return; //是否打开字典

    EntryModel entryModel;
    QString name = SDB->dictName;
    QString size = QString::number (QFileInfo(SDB->dbFile).size ());
    QString path = SDB->dbFile;
    QString totalcount = QString::number (entryModel.getTotalCount ());
    QString showCount = QString::number (entryModel.getShowCount());
    QString hideCount = QString::number (entryModel.getHideCount ());

    DictInfoDialog infoDialog(this);
    infoDialog.args(name, path, size, totalcount, showCount, hideCount);
    infoDialog.exec();
}


HeaderBarMenu::~HeaderBarMenu(){
    delete ui;
}
