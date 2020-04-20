#ifndef EXPORT_H
#define EXPORT_H

#include <QObject>
#include <QtCore>
#include "importExport/exporttoexcel.h"
#include "importExport/exporttopdb.h"
#include "importExport/exporttodicthtml.h"
#include "importExport/exporttohtml.h"

class Export : public QObject
{
    Q_OBJECT
public:
    explicit Export(QObject *parent = nullptr);
    ~Export();

signals:

public slots:
    void toPdb();
    void toExcel();
    void toHtml();
    void toDictHtml();
private:
    ExportToExcel* exportToExcel;
    ExportToPdb* exportToPdb;
    ExportToDictHtml *exportToDictHtml;
    ExportToHtml* exportToHtml;
};

#endif // EXPORT_H
