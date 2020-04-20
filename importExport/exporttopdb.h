#ifndef EXPORTTOPDB_H
#define EXPORTTOPDB_H

#include <QObject>
#include <QThread>
#include "data/dictmodel.h"
#include "data/entrymodel.h"

class ExportToPdb : public QThread
{
    Q_OBJECT
public:
    explicit ExportToPdb(QObject *parent = nullptr);
    ~ExportToPdb();
    void process();
    void setDict(DictModel*);
    void setEntries(QList<EntryModel *>*);
    void setBaseName(QString);
    void writeFile(QString path, QString content);
    void writeFile(QString path, QByteArray array);

private:
    QList<EntryModel*>* entries;
    DictModel* dict;
    QString baseName;

    QString index_page;
    QString index_list_page;
    QString item_page;
};

#endif // EXPORTTOPDB_H
