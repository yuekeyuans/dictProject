#include "sidebar.h"
#include "ui_sidebar.h"
#include <QDebug>
#include <QLabel>
#include "extra/menuitemwidget.h"
#include "data/entrymodel.h"

SideBar::SideBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SideBar)
{
    ui->setupUi(this);
    listWidgetItems = new QList<QListWidgetItem*>();
    widgetItems = new QList<QWidget*>();
    selectedItems = new QList<QPair<int, QString>>();

    createDialog ();
    createListMenu ();
    createSortButton ();

    makeList ();
}

//显示对话框
void SideBar::createDialog(){
    dialog = new SideBarSelectDialog();
    connect(ui->toolButton, &QToolButton::clicked, [&]{dialog->show ();});
    connect(dialog, &SideBarSelectDialog::finished, [&]{
        qDebug() << "hello world";
    });
//    connect (ui->listWidget, &QListWidget::itemClicked,[&](QListWidgetItem* item){
//        auto text = item;
//    });
}

//list menu
void SideBar::createListMenu(){
    contextMenu = new QMenu();
    contextAddAction = new QAction("add item", this);
    contextDeleteAction = new QAction("delete action", this);
    contextMenu->addAction (contextAddAction);
    contextMenu->addAction (contextDeleteAction);

    itemMenu = new QMenu();
    itemDeleteAction = new QAction("delete item", this);
    itemGetUrlAction = new QAction("item get url", this);
    itemSetInvisibleAction = new QAction("item set invisible", this);
    itemMenu->addAction (itemDeleteAction);
    itemMenu->addAction (itemGetUrlAction);
    itemMenu->addAction (itemSetInvisibleAction);

    auto request = [&](QPoint pos){
        QListWidgetItem* item = ui->listWidget->itemAt (pos);
        if(item == nullptr){
            contextMenu->exec (QCursor::pos());
        }else{
            itemMenu->exec (QCursor::pos ());
        }
    };
    connect (ui->listWidget, &QListWidget::customContextMenuRequested, request);
}

void SideBar::createSortButton(){
    //排序按钮
    sortAction = new QMap<int, QString>();
    sortAction->insert(0, tr("nameUp"));
    sortAction->insert(1, tr("nameDown"));
    sortAction->insert(2, tr("timeUp"));
    sortAction->insert(3, tr("timeDown"));
    sortAction->insert(4, tr("lastViewUp"));
    sortAction->insert(5, tr("lastUpdateUp"));
    ui->sortBox->addItems (sortAction->values ());
}

void SideBar::makeList(){
    // release list
    ui->listWidget->clear ();
    for(auto item : *listWidgetItems){
        listWidgetItems->removeOne (item);
        delete item;
    }
    for(auto item: *widgetItems){
        widgetItems->removeOne (item);
        delete item;
    }
    //create list
    for(auto item: *selectedItems){
        auto listItem = new QListWidgetItem();
        auto widget = new MenuItemWidget(this, WidgetType::TITLE, item.second);
        listItem->setSizeHint (QSize(100, widget->height ()));
        ui->listWidget->addItem (listItem);
        ui->listWidget->setItemWidget (listItem, widget);
        connect (widget, &MenuItemWidget::itemClicked, this, &SideBar::itemClicked);

        listWidgetItems->append (listItem);
        widgetItems->append (widget);
    }
}

void SideBar::updateMenuItems (){
        EntryModel model;
        model.loadAll(selectedItems, ui->searchBox->text(), ui->sortBox->currentText());
        makeList ();
        //enable
        ui->deleteItemButton->setEnabled(selectedItems->length () > 0);
}

SideBar::~SideBar()
{
    delete ui;
    delete this->contextMenu;
    delete this->contextAddAction;
    delete this->contextDeleteAction;
    delete this->itemMenu;
    delete this->itemDeleteAction;
    delete this->itemGetUrlAction;
    delete this->itemSetInvisibleAction;
    delete this->dialog;
}
