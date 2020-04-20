#include "createdict.h"
#include "ui_createdict.h"

CreateDict::CreateDict(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateDict)
{
    ui->setupUi(this);
}

CreateDict::~CreateDict()
{
    delete ui;
}
