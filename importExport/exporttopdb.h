#ifndef EXPORTTOPDB_H
#define EXPORTTOPDB_H

#include <QObject>
#include <QThread>
#include "data/dictmodel.h"
#include "data/entrymodel.h"
#include "globalsetting.h"

class ExportToPdb : public QThread
{
    Q_OBJECT
public:
    explicit ExportToPdb(QObject *parent = nullptr);
    ~ExportToPdb();
    void process();
    void run();
    void setDict(DictModel*);
    void setEntries(QList<EntryModel *>*);
    void setBaseName(QString);
    void setDir(QString);

    void writeFile(QString path, QString content);
    void writeFile(QString path, QByteArray array);

signals:
    void emitComplete();

private:
    QList<EntryModel*>* entries;
    DictModel* dict;
    QString baseName;
    QString dir;

    QString basePath{""};

    QString index_page;
    QString index_list_page;
    QString item_page;
};

#endif // EXPORTTOPDB_H
