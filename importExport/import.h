#ifndef IMPORT_H
#define IMPORT_H

#include <QObject>
#include "importExport/importfromexcel.h"

class Import : public QObject
{
    Q_OBJECT
public:
    explicit Import(QObject *parent = nullptr);
    ~Import();

signals:
    void importFailed();
    void importSucceed();

public slots:
    void importFromExcel();

private:
    ImportFromExcel* fromExcel;
};

#endif // IMPORT_H
