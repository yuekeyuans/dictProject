#ifndef EXPORTTODICTHTML_H
#define EXPORTTODICTHTML_H

#include <QObject>
#include <QThread>
#include <QFile>
#include "data/dictmodel.h"
#include "data/entrymodel.h"

class ExportToDictHtml : public QThread
{
    Q_OBJECT
public:
    explicit ExportToDictHtml(QObject *parent = nullptr);
    ~ExportToDictHtml();
    void run();
    void process();
    void setEntries(QList<EntryModel*>*);
    void setDict(DictModel*);
    void setBaseName(QString);
    void setPath(QString);

signals:
    void emitComplete();
private:
    QString wrapFile(QString);
    QList<EntryModel*>* entries;
    DictModel* dict;
    QString baseName;
    QRegExp ex;
    QString path;

};

#endif // EXPORTTODICTHTML_H
