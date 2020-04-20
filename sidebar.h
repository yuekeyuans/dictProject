#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QListWidgetItem>
#include "extra/sidebarselectdialog.h"
#include "data/entrymodel.h"

namespace Ui {
class SideBar;
}

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = nullptr);
    ~SideBar();

signals:
    void finished();

private:
    Ui::SideBar *ui;
    SideBarSelectDialog* dialog;

    QList<QPair<int, QString>>* selectedItems;

    // menu and action
    QMenu* contextMenu;
    QMenu* itemMenu;
    QList<QListWidgetItem*>* listWidgetItems;
    QList<QWidget*>* widgetItems;
    QMap<int, QString>* sortAction;

    QAction* itemDeleteAction;
    QAction* itemGetUrlAction;
    QAction* itemSetInvisibleAction;

    QAction* contextAddAction;
    QAction* contextDeleteAction;


    void createDialog();
    void createListMenu();
    void makeList();
    void createSortButton();

public slots:
    void updateMenuItems();

signals:
    void itemClicked(const EntryModel& model);
};

#endif // SIDEBAR_H
