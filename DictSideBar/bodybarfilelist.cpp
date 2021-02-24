#include "DictSideBar/bodyBarfilelist.h"
#include "ui_bodybarfilelist.h"
#include <QStandardItem>
#include <QAbstractItemView>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QClipboard>
#include "data/appsqlite.h"
#include "data/tagmodel.h"
#include "data/entrymodel.h"
#include <QInputDialog>

BodyBarFileList::BodyBarFileList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BodyBarFileList){
    ui->setupUi(this);
    model = new SideBarItemModel(this);
    ui->treeView->setModel (model);
    ui->treeView->header ()->hide ();
    ui->treeView->setDropIndicatorShown (true);
    ui->treeView->setDragDropMode (QAbstractItemView::InternalMove);
    ui->treeView->viewport ()->setAcceptDrops (true);
    ui->treeView->setWordWrap (true);
    ui->treeView->resizeColumnToContents (0);
    ui->treeView->setContextMenuPolicy (Qt::CustomContextMenu);

    connect (ui->treeView, &QTreeView::clicked, [&](const QModelIndex &index){
        auto item = (dynamic_cast<SideBarItem*>(this->model->itemFromIndex (index)));
        if(item->isEntry ()){
            EntryModel* model = item->getEntryModel ();
            model->load();
            emit emitListClicked (model);
        }
    });
    connect (ui->treeView, &QTreeView::collapsed, [&](QModelIndex index){
        dynamic_cast<SideBarItem*>( model->itemFromIndex (index))
            ->getTagModel ()->setFold (!(ui->treeView->isExpanded (index)));
    });
    connect(ui->treeView, &QTreeView::expanded,  [&](QModelIndex index){
        dynamic_cast<SideBarItem*>( model->itemFromIndex (index))
            ->getTagModel ()->setFold (!(ui->treeView->isExpanded (index)));
    });

    connect(ui->treeView, &QTreeView::customContextMenuRequested, this, &BodyBarFileList::slotCustomContextMenu);
    connect (model, &SideBarItemModel::emitMoveTo, this, &BodyBarFileList::slotMoveTo);
}

// TODO:
void BodyBarFileList::slotUpdateList(QString searchText, bool allSearch, bool isViewHidden){
    if(tagModelsRestore != nullptr){ // clear tag model
        qDeleteAll(*tagModelsRestore);
        tagModelsRestore->clear ();
        delete tagModelsRestore;
        tagModelsRestore = nullptr;
    }
    if(entryModelsRestore != nullptr){ // clear entry model
        qDeleteAll(*entryModelsRestore);
        entryModelsRestore->clear ();
        delete entryModelsRestore;
        entryModelsRestore = nullptr;
    }
    if(tagItemRestore != nullptr){   // clear tag model, data not to delete and system will delete it.
        tagItemRestore->clear();
        delete tagItemRestore;
        tagItemRestore = nullptr;
    }
    tagItemRestore = new QList<SideBarItem*>();
    model->clear ();  // clear sidebar model

    TagModel tagModel;
    tagModelsRestore = tagModel.loadAll ();

    EntryModel entryModel;
    entryModelsRestore = entryModel.loadAllInList (searchText, allSearch, isViewHidden);
    auto parentItem = model->invisibleRootItem ();
    for(auto tag : *tagModelsRestore){
        auto item = new SideBarItem(tag);
        if(tag->parentId == TagModel::TAG_ID_PARENT){
            parentItem->appendRow (item);
        }else {
            for(int i = 0;i<tagItemRestore->length ();i++){
                if(tagItemRestore->at (i)->getTagModel ()->id == tag->parentId){
                    tagItemRestore->at (i)->appendRow (item);
                    break;
                }
            }
        }
        tag->fold ? ui->treeView->collapse (model->indexFromItem (item))
                  : ui->treeView->expand (model->indexFromItem (item));
        tagItemRestore->append (item);
    }

    for(auto entry : *entryModelsRestore){
        auto item = new SideBarItem(entry, showParagraph);
        if(entry->tagId == TagModel::TAG_ID_PARENT){
            parentItem->appendRow (item);
        }else{
            for(int i = 0;i<tagItemRestore->length ();i++){
                if(tagItemRestore->at (i)->getTagModel ()->id == entry->tagId){
                    tagItemRestore->at (i)->appendRow (item);
                    break;
                }
            }
        }
        if(showParagraph){
            item->setSizeHint (QSize(0,100));
        }
    }
}

void BodyBarFileList::slotShowParagraph (bool isShow){
    this->showParagraph = isShow;
    emit emitupdateMenuItems ();
}

void BodyBarFileList::slotDeleteEntry (){
    if(ui->treeView->currentIndex () == QModelIndex()) return;

    auto currentIndex = model->itemFromIndex (ui->treeView->currentIndex ());
    EntryModel* mdl = dynamic_cast<SideBarItem*>(currentIndex)->getEntryModel ();

    QMessageBox deleteEntryQueryBox;
    deleteEntryQueryBox.setWindowTitle (tr("query"));
    deleteEntryQueryBox.setText (tr("will this item be deleted?"));
    deleteEntryQueryBox.setStandardButtons (QMessageBox::Ok | QMessageBox:: Cancel);
    if(deleteEntryQueryBox.exec () == QMessageBox::Ok){
        mdl->deleted ();
        emit emitEntryDeleted ();
        emit emitupdateMenuItems ();
    }
}

void BodyBarFileList::slotMoveTo (const QModelIndex &fromParent, QString fromId, int row, const QModelIndex &toParent){
    TagModel tagModel;
    int tagLength = tagModel.getTotalCount ();
    int fromIndex{-1}, toIndex{-1};
    QList<EntryModel*> subModel;
    bool isTopLevel = (toParent == QModelIndex());
    bool isChangeTag = (fromParent.model () != toParent.model ());
    QString tag_id = isTopLevel ? TagModel::TAG_ID_PARENT: dynamic_cast<SideBarItem*>( model->itemFromIndex (toParent))->getId ();

    for(int i=0; i<entryModelsRestore->length ();i++){
        if(entryModelsRestore->at (i)->id == fromId){
            fromIndex = i;
            break;
        }
    }

    if(row == -1){ // 跳到最后一个, 如果就在最后一个，可以直接跳过去，
        for(int i=0;i<entryModelsRestore->length ();i++){
            if(entryModelsRestore->at (i)->tagId == tag_id){
                toIndex = i;
            }
        }
    } else {
        int _row = isTopLevel ? tagLength : 0;
        toIndex = 0;
        for(int i=0;i<entryModelsRestore->length ();i++){
            if(entryModelsRestore->at(i)->tagId == tag_id){
                toIndex = i;
                _row ++;
                if(_row >= row){
                    break;
                }
            }
        }
    }

    entryModelsRestore->at (fromIndex)->setTag (tag_id);

    if(isChangeTag){
        if(fromIndex > toIndex){
            emit emitupdateMenuItems ();
            return;
        }
    }

    subModel =
        entryModelsRestore->mid (fromIndex>toIndex ? toIndex: fromIndex, abs(fromIndex-toIndex) + 1);
    this->changSortId (subModel, (fromIndex < toIndex));
    if (isChangeTag) { //改变tag,重新计数
        SDB->initTagCount();
    }
    emit emitupdateMenuItems ();
}

// order = true 时， from tag < toTag
void BodyBarFileList::changSortId(QList<EntryModel*> &list, bool order){
    if(list.length () == 1) return;

    int begin = 0;
    int end = list.length () - 1;
    int stash_sort{-1};

    if(order){
        stash_sort = list.at (end)->sortId;
        for(int i = end; i>begin; i--){
            list.at (i)->setSortId (list.at (i-1)->sortId);
        }
        list.at (begin)->setSortId (stash_sort);
    }else { // toTag, next, next, fromTag
        begin = begin + 1;
        stash_sort = list.at (begin)->sortId;
        for(int i=begin; i<end; i++){
            list.at (i)->setSortId (list.at (i+1)->sortId);
        }
        list.at (end)->setSortId (stash_sort);
    }
}

void BodyBarFileList::slotToggleHideEntry (){
    if(ui->treeView->currentIndex () == QModelIndex()) return;
    EntryModel* currentEntry = dynamic_cast<SideBarItem*>( model->itemFromIndex (ui->treeView->currentIndex ()))->getEntryModel ();
    currentEntry->setVisiable (!currentEntry->isVisiable);
    emit emitupdateMenuItems ();
}

void BodyBarFileList::slotCopyName (){
    if(ui->treeView->currentIndex () == QModelIndex()) return;
    EntryModel* currentEntry = dynamic_cast<SideBarItem*>( model->itemFromIndex (ui->treeView->currentIndex ()))->getEntryModel ();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(currentEntry->entry);
}

void BodyBarFileList::slotCopyUrl (){
    if(ui->treeView->currentIndex () == QModelIndex()) return;
    EntryModel* currentEntry = dynamic_cast<SideBarItem*>( model->itemFromIndex (ui->treeView->currentIndex ()))->getEntryModel ();
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText("entry://" + currentEntry->entry);
}

void BodyBarFileList::slotCopyAsNewEntry(){
    if(ui->treeView->currentIndex () == QModelIndex()) return;
    EntryModel* currentEntry = dynamic_cast<SideBarItem*>( model->itemFromIndex (ui->treeView->currentIndex ()))->getEntryModel ();
    QString text = QInputDialog::getText(nullptr, tr("Input Dialog"),
                                         tr("Please input your comment"),
                                         QLineEdit::Normal,
                                         currentEntry->entry + "_new");
    if(text == "")return;
    if(text == currentEntry->entry){
        QMessageBox::information (this, tr("tips"), tr("please input different text"));
        return;
    }
    EntryModel model{currentEntry->id};
    model.load ();
    model.id = EntryModel::ENTRY_ID_NULL;
    model.entry = text;
    model.insert ();
    emit emitupdateMenuItems ();
}

void BodyBarFileList::slotCustomContextMenu (const QPoint &pos){
    if(SDB == nullptr) return;

    QMenu menu;
    QModelIndex curIndex = ui->treeView->indexAt(pos);      //当前点击的元素的index
    if (curIndex.isValid())
    {
        SideBarItem* item = dynamic_cast<SideBarItem*>(model->itemFromIndex (curIndex));
        if(item->isEntry ()){
            menu.addAction(tr("delete"), this, &BodyBarFileList::slotDeleteEntry);
            menu.addAction(tr("toggle hidden file"),this, &BodyBarFileList::slotToggleHideEntry);
            menu.addAction(tr("copy name"), this, &BodyBarFileList::slotCopyName);
            menu.addAction (tr("copy url path"), this, &BodyBarFileList::slotCopyUrl);
            menu.addAction (tr("copy as new Entry"), this, &BodyBarFileList::slotCopyAsNewEntry);
        }else{
            if(item->getTagModel ()->fold){
                menu.addAction (tr("expand"), this, &BodyBarFileList::slotTagExpand);
            }else{
                menu.addAction (tr("fold"), this, &BodyBarFileList::slotTagFold);
            }
            menu.addAction (tr("add sub tag"), this, &BodyBarFileList::slotTagAddSubTag);
            if (!(item->getTagModel()->id == TagModel::TAG_ID_ANCHOR
                  || item->getTagModel()->id == TagModel::TAG_ID_PLUGIN)) {
                menu.addAction(tr("delete tag"), this, &BodyBarFileList::slotTagDelete);
                menu.addAction(tr("export"), this, &BodyBarFileList::slotTagExport);
            }
            if (item->getTagModel()->id == TagModel::TAG_ID_ANCHOR) {
                menu.addAction(tr("refresh anchors"), this, &BodyBarFileList::slotTagRefreshAnchors);
            }
        }
    }else{
        menu.addAction (tr("add item"), this, &BodyBarFileList::emitTreeAddEntry);
    }
    menu.exec(ui->treeView->mapToGlobal(pos)/*全局位置*/);
}

// TODO: not initialized yet!
void BodyBarFileList::slotTagRefreshAnchors (){

}

void BodyBarFileList::slotTagExport (){
    SideBarItem* item = dynamic_cast<SideBarItem*>(model->itemFromIndex (ui->treeView->currentIndex ()));
    emit emitTagExport (item->getTagModel ());
}

void BodyBarFileList::slotTagAddSubTag (){
    QString name = QInputDialog::getText (this, tr("标签"), tr("请输入标签名"));
    if(name == "") return;
    SideBarItem* item = dynamic_cast<SideBarItem*>(model->itemFromIndex (ui->treeView->currentIndex ()));

    TagModel tag;
    tag.name = name;
    tag.parentId = item->getTagModel ()->id;
    tag.insert ();
    emit emitupdateMenuItems ();
}

void BodyBarFileList::slotTagExpand (){
    auto curIndex = ui->treeView->currentIndex ();
    ui->treeView->setExpanded (curIndex, true);
    auto item = dynamic_cast<SideBarItem*>(model->itemFromIndex (curIndex))->getTagModel ();
    item->setFold (false);
}

void BodyBarFileList::slotTagFold (){
    auto curIndex = ui->treeView->currentIndex ();
    ui->treeView->setExpanded (curIndex, false);
    auto item = dynamic_cast<SideBarItem*>(model->itemFromIndex (curIndex))->getTagModel ();
    item->setFold (true);
}

void BodyBarFileList::slotTagDelete (){
    auto button = QMessageBox::question (this, tr("delete this tag?"), tr("when delete this tag, all sub tags and its contents will be deleted, are you really want to delete this tags?"));
    if(button == QMessageBox::No){
        return;
    }

    auto curIndex = ui->treeView->currentIndex ();
    auto item = dynamic_cast<SideBarItem*>(model->itemFromIndex (curIndex))->getTagModel ();
    TagModel tag;
    auto tags = tag.loadAllTagsAndSubtags (item->id);
    tag.deleted (tags);
    EntryModel entry;
    entry.deleted (tags);
    delete tags;
    emit emitupdateMenuItems ();
}
void BodyBarFileList::slotTagFoldAll (){
    for(auto tag : *tagItemRestore){
        tag->getTagModel ()->setFold (true);
    }
    emit emitupdateMenuItems ();
}

void BodyBarFileList::slotTagExpandAll (){
    for(auto tag:*tagItemRestore){
        tag->getTagModel ()->setFold (false);
    }
    emit emitupdateMenuItems ();
}

BodyBarFileList::~BodyBarFileList(){
    delete ui;
    delete model;
    if (entryModelsRestore != nullptr) {
        qDeleteAll(*entryModelsRestore);
        entryModelsRestore->clear();
        delete entryModelsRestore;
        entryModelsRestore = nullptr;
    }
    if (tagModelsRestore != nullptr) {
        qDeleteAll(*tagModelsRestore);
        tagModelsRestore->clear();
        delete tagModelsRestore;
        tagModelsRestore = nullptr;
    }
    if (tagItemRestore != nullptr) {
        tagItemRestore->clear();
        delete tagItemRestore;
        tagItemRestore = nullptr;
    }

}
