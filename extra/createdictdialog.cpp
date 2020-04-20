#include "createdictdialog.h"
#include "ui_createdictdialog.h"

CreateDictDialog::CreateDictDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDictDialog)
{
    ui->setupUi(this);
}

CreateDictDialog::~CreateDictDialog()
{
    delete ui;
}
