#include "sidebarselectdialog.h"
#include "ui_sidebarselectdialog.h"

SideBarSelectDialog::SideBarSelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SideBarSelectDialog)
{
    ui->setupUi(this);
}

SideBarSelectDialog::~SideBarSelectDialog()
{
    delete ui;
}
