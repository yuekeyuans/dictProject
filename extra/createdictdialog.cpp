#include "createdictdialog.h"
#include "ui_createdictdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include "data/setting.h"

CreateDictDialog::CreateDictDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDictDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CreateDictDialog::checkInput);
    connect(ui->openFile, &QPushButton::clicked, [=]{this->openFileDialog();});
}

CreateDictDialog::~CreateDictDialog(){
    delete ui;
}

QString CreateDictDialog::getName(){
    return ui->name->text();
}

QString CreateDictDialog::getPath(){
    return ui->path->text();
}

void CreateDictDialog::checkInput(){
    if(ui->name->text() == "" || ui->path->text() == ""){
        QMessageBox::warning(this, tr("warnig"), tr("input complete"), QMessageBox::Ok);
        return;
    }
    Setting setting;
    setting.addDict(getName(), getPath());
    emit accept();
}

void CreateDictDialog::openFileDialog(){
    QString file =
            QFileDialog::getSaveFileName(
                this,
                "open","../",
                 tr("fileType"));
    QString filePath =  file == ""? "":file;
    ui->path->setText(filePath);
    QFileInfo fileInfo(filePath);
    ui->name->setText(fileInfo.baseName());
}
