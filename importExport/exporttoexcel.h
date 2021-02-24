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
    void run();


    void setEntries(QList<EntryModel *> *);
    void setDict(DictModel *);
    void setTags(QList<TagModel *> *);
    void setBaseName(QString);
    void setFileName(QString);

signals:
    void emitComplete();

private:
    bool writeEntry(QList<EntryModel *> *);
    bool writeTag(QList<TagModel *> *);
    bool writeDict(DictModel *);

    QList<EntryModel*>* entries;
    DictModel* dict;
    QList<TagModel *> *tags;
    QString baseName;

    QString fileName;
};

#endif // EXPORTTOEXCEL_H
