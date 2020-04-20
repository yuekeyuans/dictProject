#include "import.h"
#include <QFileDialog>
#include <data/entrymodel.h>
#include <data/dictmodel.h>


#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

Import::Import(QObject *parent) : QObject(parent){
    fromExcel = new ImportFromExcel(this);
}

Import::~Import(){
    delete fromExcel;
}

void Import::importFromExcel(){
    QString filePath = QFileDialog::getOpenFileName(nullptr, tr("tips"), tr("./"), tr("xls(*.xlsx)"));
    if(filePath == nullptr || filePath == ""){
        return;
    }
    else{
        Document xlsR(filePath);
        auto success = xlsR.load();
        if(!success){
            emit importFailed();
            return;
        }
        for(int r=1;;r++){
            auto cell = xlsR.cellAt(r, 1);
            if(cell == NULL){
                emit importSucceed();
                return;
            }
            EntryModel model;
            model.entry =cell->readValue().toString();
            model.text = xlsR.cellAt(r, 2)->readValue().toString();
            model.html = xlsR.cellAt(r, 3)->readValue().toString();
            model.insertOrUpdate();
        }
    }
}
