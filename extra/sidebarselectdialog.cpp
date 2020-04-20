#include "sidebarselectdialog.h"
#include "ui_sidebarselectdialog.h"

SideBarSelectDialog::SideBarSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SideBarSelectDialog)
{
    ui->setupUi(this);
    this->setModal (true);
}

SideBarSelectDialog::~SideBarSelectDialog()
{
    delete ui;
}
