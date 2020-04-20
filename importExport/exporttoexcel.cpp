#include "exporttoexcel.h"
#include <thread>
#include <QMessageBox>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "data/entrymodel.h"
#include "data/dictmodel.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

ExportToExcel::ExportToExcel(QObject *parent) : QThread(parent)
{

}

void ExportToExcel::process(){
    //获得文件未知
    QString file = QFileDialog::getSaveFileName(nullptr,tr("open"),"../" + baseName, tr("xlsx(*.xlsx)"));
    if(file == "" || entries == nullptr || dict == nullptr){
        QMessageBox::about(nullptr, tr("tip"), tr("fail"));
        return;
    }

    QXlsx::Document xlsxW;
    for(int i=0;i<entries->size();i++){
        //xlsxW.write(i+1, 1, entries->at(i)->id);
        xlsxW.write(i+1, 1, entries->at(i)->entry);
        xlsxW.write(i+1, 2, entries->at(i)->text);
        xlsxW.write(i+1, 3, entries->at(i)->html);
        xlsxW.write(i+1, 4, entries->at(i)->mkdown);
        //xlsxW.write(i+1, 4, entries->at(i)->createDate);
    }
    for(auto entry: *entries){
        delete  entry;
    }
    delete entries;
    xlsxW.renameSheet(xlsxW.sheetNames().first(),"entries");
    xlsxW.addSheet("dict");
    xlsxW.write(1,1, dict->id);
    xlsxW.write(1,2, dict->title);
    xlsxW.write(1,3, dict->description);
    xlsxW.write(1,4, dict->html);
    delete dict;
    //保存文件
    if ( xlsxW.saveAs(file)) {
        QMessageBox::about(nullptr, tr("tip"), tr("finish"));
    }else{
        QMessageBox::about(nullptr, tr("tip"), tr("fail"));
    }
}

void ExportToExcel::setDict(DictModel *dict){
    this->dict = dict;
}

void ExportToExcel::setEntries(QList<EntryModel *> * entries){
    this->entries = entries;
}

void ExportToExcel::setBaseName(QString baseName){
    this->baseName = baseName;
}
