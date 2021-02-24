#include "sidebaritem.h"
#include <QDebug>

SideBarItem::SideBarItem() : QStandardItem ()
{

}

SideBarItem::SideBarItem(QString str):QStandardItem(str){

}

SideBarItem::SideBarItem(EntryModel* _model):SideBarItem(_model, false){

}

SideBarItem::SideBarItem(TagModel* tag):SideBarItem(){
    this->tag = tag;
    this->setText (tag->name + " (" + QString ::number (tag->getSize ()) + ")");
    this->setBackground (QColor(240,240,240));
}

SideBarItem::SideBarItem(EntryModel* _model, bool showParagraph): QStandardItem (){
    this->entry = _model;
    this->setRowCount (4);
    showParagraph ? this->setText(entry->entry + "\n" + zipText(entry->text) + "")
                  : this->setText(entry->entry);

    !entry->isVisiable ? this->setBackground(QColor(0, 0, 0, 20))
                       : this->setBackground (QColor(0, 0, 0, 0));
}

EntryModel* SideBarItem::getEntryModel() const{
    return entry;
}

bool SideBarItem::isEntry() const{
    return entry != nullptr;
}

TagModel* SideBarItem::getTagModel() const{
    return tag;
}

QString SideBarItem::zipText(QString str){
    return str.replace (QRegExp("\\s|\t|\r|\n"),"");
}

QString SideBarItem::getId() const{
    return isEntry() ? entry->id : tag->id;
}

QString SideBarItem::getType() const{
    return isEntry() ? "entry" : "tag";
}

QString SideBarItem::getName() const{
    return isEntry() ? entry->entry : tag->name;
}

SideBarItem::~SideBarItem()
{
    //不需要释放 entry 和 tag,这里是传递指针，指针在外部释放
}
