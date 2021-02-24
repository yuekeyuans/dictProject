#ifndef IMPORT_H
#define IMPORT_H

#include <QObject>
#include "importExport/importfromexcel.h"
#include <QFileDialog>
#include <data/entrymodel.h>
#include <data/dictmodel.h>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QDebug>
#include <QMessageBox>

using namespace QXlsx;

class Import : public QObject
{
    Q_OBJECT
public:
    explicit Import(QObject *parent = nullptr);
    ~Import();

signals:
    void emitImportSucceed();

public slots:
    void fromExcel();

    void slotSuccess();
    void slotFail();

private:
    ImportFromExcel* importFromExcel;
};

#endif // IMPORT_H
