#include "import.h"

Import::Import(QObject *parent) : QObject(parent){
    importFromExcel = new ImportFromExcel(parent);
    connect(importFromExcel, &ImportFromExcel::emitFail, this, &Import::slotFail);
    connect(importFromExcel, &ImportFromExcel::emitSuccess, this, &Import::slotSuccess);
}

void Import::fromExcel()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr,
                                                    tr("tips"),
                                                    tr("./"),
                                                    tr("xls(*.xlsx)"));
    if (filePath == nullptr || filePath == "") {
        return;
    }
    importFromExcel->setFilePath(filePath);
    importFromExcel->start ();
}

void Import::slotFail()
{
    QMessageBox::information(nullptr, tr("tips"), tr("fail"));
}

void Import::slotSuccess()
{
    emit emitImportSucceed();
}

Import::~Import(){
    delete importFromExcel;
}
