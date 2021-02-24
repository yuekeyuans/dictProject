#ifndef SIDEBARITEMMODEL_H
#define SIDEBARITEMMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QMimeData>
#include "data/entrymodel.h"

class SideBarItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit SideBarItemModel(QObject *parent = nullptr);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QMimeData* mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent);

signals:
    void emitMoveTo(const QModelIndex &fromParent, QString id, int row, const QModelIndex &toParent);
    void setTagCount();

public slots:

private:

};

#endif // SIDEBARITEMMODEL_H
