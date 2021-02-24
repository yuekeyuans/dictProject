#ifndef EXPORT_H
#define EXPORT_H

#include <QObject>
#include <QtCore>
#include "importExport/exporttoexcel.h"
#include "importExport/exporttopdb.h"
#include "importExport/exporttodicthtml.h"
#include "importExport/exporttohtml.h"
#include "importExport/exporttotag.h"
#include "extra/tagexportoptionsdialog.h"

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
    void toTag(TagModel*);

    void slotShowInfo();

private:
    ExportToExcel* exportToExcel;
    ExportToPdb* exportToPdb;
    ExportToDictHtml *exportToDictHtml;
    ExportToHtml* exportToHtml;
    ExportToTag *exportToTag;
};

#endif // EXPORT_H
