#include "headerbar.h"
#include "ui_headerbar.h"
#include "data/appsqlite.h"

HeaderBar::HeaderBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeaderBar)
{
    ui->setupUi(this);
    barSearch = new HeaderBarSearch();

    barMenu = new HeaderBarMenu();
    ui->stackedWidget->addWidget (barMenu);
    ui->stackedWidget->addWidget (barSearch);

    connect (barMenu, &HeaderBarMenu::searchButtonClicked,[=]{
        ui->stackedWidget->setCurrentIndex (1);
    });
    connect (barSearch, &HeaderBarSearch::emitCompleteSearch, [=]{
        ui->stackedWidget->setCurrentIndex (0);
    });
    connect (barSearch, &HeaderBarSearch::emitAllTextSearch, this, &HeaderBar::emitAllTextSearch);
    connect(barSearch, &HeaderBarSearch::emitShowParagraph, this, &HeaderBar::emitShowParagraph);
    connect(barSearch, &HeaderBarSearch::emitTextChanged, this, &HeaderBar::emitTextChanged);
    connect (barMenu, &HeaderBarMenu::emitAddEntry, this, &HeaderBar::emitAddEntry);
    connect (barMenu, &HeaderBarMenu::emitDeleteEntry, this, &HeaderBar::emitDeleteEntry);
    connect (barMenu, &HeaderBarMenu::emitViewHidden, this, &HeaderBar::emitViewHidden);
    connect (barMenu, &HeaderBarMenu::emitTagAdd, this, &HeaderBar::emitTagAdd);
    connect (barMenu, &HeaderBarMenu::emitTagExpandAll, this, &HeaderBar::emitTagsExpandAll);
    connect(barMenu, &HeaderBarMenu::emitTagFoldAll, this, &HeaderBar::emitTagsFoldAll);

    connect (this, &HeaderBar::emitUpdateHeaderBar, barMenu, &HeaderBarMenu::slotUpdate);
    connect(this, &HeaderBar::emitUpdateHeaderBar, barSearch, &HeaderBarSearch::slotUpdate);
}

void HeaderBar::slotUpdate (){

}

HeaderBar::~HeaderBar()
{
    delete ui;
    delete barSearch;
    delete barMenu;
}
