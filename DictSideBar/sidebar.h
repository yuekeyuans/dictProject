#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include "DictSideBar/headerbar.h"
#include "DictSideBar/bodyBarfilelist.h"
#include "extra/dictinfodialog.h"

namespace Ui {
class SideBar;
}

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

public slots:
    void slotupdateMenuItems();
    void slotupdateMenuItemsWithText(QString searchText="");
    void slotAllTextSearch(bool);
    void slotJumpPage(EntryModel*, QString fragment);
    void slotViewHidden(bool);

signals:
    void emitListClicked(EntryModel*, QString fragment);
    void emitAddEntry();
    void emitDeleteEntry();
    void emitEntryDeleted();
    void emitUpdateSideBar();
    void emitTagExport(TagModel*);
    void emitUpdateFileList(QString, bool, bool);
    void emitSideBarUpdated();

private:
    Ui::SideBar *ui{nullptr};
    HeaderBar* headerBar{nullptr};
    BodyBarFileList* fileList{nullptr};

    QString searchText{""};
    bool allTextSearch{false};
    bool isViewHidden{false};
};

#endif // SIDEBAR_H
