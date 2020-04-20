#ifndef EXPORTTOEXCEL_H
#define EXPORTTOEXCEL_H

#include <QObject>
#include <QThread>
#include "data/entrymodel.h"
#include "data/dictmodel.h"

class ExportToExcel : public QThread
{
    Q_OBJECT
public:
    explicit ExportToExcel(QObject *parent = nullptr);
    void process();
    void setEntries(QList<EntryModel*>*);
    void setDict(DictModel*);
    void setBaseName(QString);

private:
    QList<EntryModel*>* entries;
    DictModel* dict;
    QString baseName;
};

#endif // EXPORTTOEXCEL_H
