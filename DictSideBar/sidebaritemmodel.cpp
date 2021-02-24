#include "sidebaritemmodel.h"
#include <QDebug>
#include "data/entrymodel.h"
#include "DictSideBar/sidebaritem.h"
#include "data/appsqlite.h"
#include <QSettings>

SideBarItemModel::SideBarItemModel(QObject *parent) : QStandardItemModel(parent){

}

Qt::ItemFlags SideBarItemModel::flags(const QModelIndex &index) const{
    if(!index.isValid ()){
        return Qt::NoItemFlags | Qt::ItemIsDropEnabled;
    }

    auto it = dynamic_cast<SideBarItem*>(this->itemFromIndex (index));
    if(!it->isEntry ()) {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled ;
}

QMimeData* SideBarItemModel::mimeData(const QModelIndexList &indexes) const{
    QMimeData *data = QStandardItemModel::mimeData (indexes);
    if(!data){
        return nullptr;
    }
    auto item = dynamic_cast<SideBarItem*>(this->itemFromIndex (indexes.at (0)));
    data->setData ("type", item->getType ().toLocal8Bit ());
    data->setData ("id", item->getId ().toLocal8Bit ());
    data->setData ("name", item->getName ().toLocal8Bit ());

    return data;
}

bool SideBarItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                    int row, int, const QModelIndex &parent){
    if(SDB ==nullptr){return false;}

    QString id = QString::fromLocal8Bit (data->data ("id"));
    QString type = QString::fromLocal8Bit (data->data("type"));
    QString name = QString::fromLocal8Bit (data->data("name"));

    //这样使用，防止 tag 和 entry 冲突，虽然不太可能
    QStandardItem* item{nullptr};
    auto children = this->findItems(name,Qt::MatchFixedString | Qt::MatchCaseSensitive | Qt::MatchRecursive);
    for(auto child: children){
        if(dynamic_cast<SideBarItem*>(child)->getType () == "entry"){
            item = child;
            break;
        }
    }

    QModelIndex modelIndex;
    if(item->parent () != nullptr){ // 顶级的。
        modelIndex = item->parent ()->index ();
    }
    emit emitMoveTo (modelIndex, id, row, parent);
    return false;
}
