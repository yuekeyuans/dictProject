#include "loaddict.h"
#include "ui_loaddict.h"

LoadDict::LoadDict(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadDict)
{
    ui->setupUi(this);
}

LoadDict::~LoadDict()
{
    delete ui;
}
