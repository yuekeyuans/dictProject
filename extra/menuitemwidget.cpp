#include "menuitemwidget.h"
#include "ui_menuitemwidget.h"

MenuItemWidget::MenuItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItemWidget)
{
    ui->setupUi(this);
}

MenuItemWidget::~MenuItemWidget()
{
    delete ui;
}
