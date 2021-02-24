#include "dictinfodialog.h"
#include "ui_dictinfodialog.h"

DictInfoDialog::DictInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DictInfoDialog)
{
    ui->setupUi(this);
}

void DictInfoDialog::args(QString name, QString path, QString size, QString count, QString showCount, QString hideCount){
    ui->dictName->setText (name);
    ui->path->setText(path);
    ui->entryCount->setText (count);
    ui->dictSize->setText (readableFilesize (size.toLong ()));
    ui->showCount->setText (showCount);
    ui->hideCount->setText (hideCount);
}

QString DictInfoDialog::readableFilesize( long filesize){
    QStringList units;
    units << "B" << "KB" << "MB" << "GB" << "TB" << "PB";
    double mod  = 1024.0;
    double size = filesize;
    int i = 0;
    long rest = 0;
    while (size >= mod && i < units.count()-1 ){
        rest= (long)size % (long)mod ;
        size /= mod;
        i++;
    }
    QString szResult = QString::number(floor(size));
    if( rest > 0)
    {
        szResult += QString(".") + QString::number(rest).left(2);
    }
    szResult += units[i];
    return  szResult;
}

DictInfoDialog::~DictInfoDialog()
{
    delete ui;
}
