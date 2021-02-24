#ifndef BODYBARFILELIST_H
#define BODYBARFILELIST_H

#include <QWidget>
#include "DictSideBar/sidebaritemmodel.h"
#include "DictSideBar/sidebaritem.h"
#include <QMessageBox>
#include "data/dictmodel.h"
#include "data/entrymodel.h"
#include "data/tagmodel.h"

namespace Ui {
class BodyBarFileList;
}

class BodyBarFileList : public QWidget
{
    Q_OBJECT

public:
    explicit BodyBarFileList(QWidget *parent = nullptr);
    ~BodyBarFileList();

public slots:
    void slotUpdateList(QString searchText, bool allSearch, bool isViewHidden);
    void slotShowParagraph(bool);
    void slotDeleteEntry();
    void slotCustomContextMenu(const QPoint &pos);
    void slotToggleHideEntry();
    void slotMoveTo(const QModelIndex &fromParent, QString id, int row, const QModelIndex &toParent);
    void slotCopyName();
    void slotCopyUrl();
    void slotCopyAsNewEntry();
    void slotTagFoldAll();
    void slotTagExpandAll();
    void slotTagDelete();
    void slotTagExpand();
    void slotTagFold();
    void slotTagAddSubTag();
    void slotTagExport();
    void slotTagRefreshAnchors();

signals:
    void emitListClicked(EntryModel* model, QString fragment = "");
    void emitTagExport(TagModel*);
    void emitupdateMenuItems();
    void emitEntryDeleted();
    void emitTreeAddEntry();
    void emitRemoveEntry();

private:
    Ui::BodyBarFileList *ui{nullptr};
    SideBarItemModel* model{nullptr};
    QList<EntryModel*>* entryModelsRestore{nullptr};
    QList<TagModel*>* tagModelsRestore{nullptr};
    QList<SideBarItem*>* tagItemRestore{nullptr};
    void changSortId(QList<EntryModel*> &list, bool order);
    bool showParagraph{false};
    bool allTextSearch{false};
};

#endif // BODYBARFILELIST_H
