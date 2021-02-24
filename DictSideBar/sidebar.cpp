#include "sidebar.h"
#include "ui_sidebar.h"
#include <QDebug>
#include "data/appsqlite.h"

SideBar::SideBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBar)
{
    ui->setupUi(this);

    headerBar = new HeaderBar();
    ui->header_layout->addWidget (headerBar);

    fileList = new BodyBarFileList();
    ui->stackedWidget->addWidget (fileList);

    connect(this, &SideBar::emitDeleteEntry, fileList, &BodyBarFileList::slotDeleteEntry);
    connect (this, &SideBar::emitUpdateSideBar, headerBar, &HeaderBar::emitUpdateHeaderBar);
    connect(this, &SideBar::emitUpdateSideBar, this, &SideBar::slotupdateMenuItems);

    connect (headerBar, &HeaderBar::emitAllTextSearch, this, &SideBar::slotAllTextSearch);
    connect(headerBar, &HeaderBar::emitShowParagraph, fileList, &BodyBarFileList::slotShowParagraph);
    // 预备加入tags 的信息
    connect(headerBar, &HeaderBar::emitAddEntry, this, &SideBar::emitAddEntry);
    connect(headerBar, &HeaderBar::emitDeleteEntry, fileList, &BodyBarFileList::slotDeleteEntry);
    connect(headerBar, &HeaderBar::emitTextChanged, this, &SideBar::slotupdateMenuItemsWithText);
    connect(fileList, &BodyBarFileList::emitEntryDeleted, this, &SideBar::emitEntryDeleted);
    connect(fileList, &BodyBarFileList::emitListClicked, this, &SideBar::emitListClicked);
    connect(fileList, &BodyBarFileList::emitupdateMenuItems, this, &SideBar::slotupdateMenuItems);
    connect(fileList, &BodyBarFileList::emitTreeAddEntry, this, &SideBar::emitAddEntry);
    connect(fileList, &BodyBarFileList::emitTagExport, this, &SideBar::emitTagExport);
    connect(this, &SideBar::emitUpdateFileList, fileList, &BodyBarFileList::slotUpdateList);

    connect(headerBar, &HeaderBar::emitViewHidden, this, &SideBar::slotViewHidden);
    connect(headerBar, &HeaderBar::emitTagAdd, this, &SideBar::slotupdateMenuItems);
    connect(headerBar, &HeaderBar::emitTagsFoldAll, fileList, &BodyBarFileList::slotTagFoldAll);
    connect(headerBar, &HeaderBar::emitTagsExpandAll, fileList, &BodyBarFileList::slotTagExpandAll);

}

void SideBar::slotAllTextSearch (bool isAllTextSearch){
    this->allTextSearch = isAllTextSearch;
    slotupdateMenuItems ();
}

void SideBar::slotViewHidden (bool isViewHidden){
    this->isViewHidden = isViewHidden;
    slotupdateMenuItems ();
}

void SideBar::slotupdateMenuItemsWithText (QString searchText){
    this->searchText = searchText;
    return slotupdateMenuItems ();
}

void SideBar::slotupdateMenuItems(){
    emit emitUpdateFileList(this->searchText, allTextSearch, isViewHidden);
    emit emitSideBarUpdated();
}

void SideBar::slotJumpPage (EntryModel* model, QString fragment){
    emit emitListClicked (model, fragment);
}

SideBar::~SideBar()
{
    delete ui;
    delete headerBar;
    delete fileList;
}
