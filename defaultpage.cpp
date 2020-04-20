#include "defaultpage.h"
#include "ui_defaultpage.h"

DefaultPage::DefaultPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DefaultPage)
{
    ui->setupUi(this);
}

DefaultPage::~DefaultPage()
{
    delete ui;
}
