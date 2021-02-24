#ifndef SIDEBARITEM_H
#define SIDEBARITEM_H

#include <QObject>
#include <QStandardItem>
#include "data/entrymodel.h"
#include "data/tagmodel.h"

class SideBarItem : public QStandardItem
{
    //Q_OBJECT
public:
    explicit SideBarItem();
    explicit SideBarItem(QString str);
    explicit SideBarItem(EntryModel* model);
    explicit SideBarItem(EntryModel* model, bool showParagraph);
    explicit SideBarItem(TagModel* model);
    ~SideBarItem();
    bool isEntry() const;
    QString getId() const;
    QString getType() const;
    QString getName() const;

    EntryModel* getEntryModel() const;
    TagModel* getTagModel() const;

signals:

public slots:

private:
    EntryModel* entry{nullptr};
    TagModel* tag{nullptr};
    QString zipText(QString);
    QString typeName{"entry"};
};

#endif // SIDEBARITEM_H
