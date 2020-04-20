#ifndef EXPORTTOHTML_H
#define EXPORTTOHTML_H

#include <QObject>
#include "data/dictmodel.h"
#include "data/entrymodel.h"

class ExportToHtml : public QObject
{
    Q_OBJECT
public:
    explicit ExportToHtml(QObject *parent = nullptr);
    void process();
    void setEntries(QList<EntryModel*>*);
    void setDict(DictModel*);
    void setBaseName(QString);
signals:
    void exportComplete();
    void exportFail();

private:
    QList<EntryModel*>* entries;
    DictModel* dict;
    QString baseName;

    void writeFile(QString, QString);
    QString readFile(QString);
};

#endif // EXPORTTOHTML_H
