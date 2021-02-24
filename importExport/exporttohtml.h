#ifndef EXPORTTOHTML_H
#define EXPORTTOHTML_H

#include <QObject>
#include "data/dictmodel.h"
#include "data/entrymodel.h"
#include "globalsetting.h"
#include <QThread>

class ExportToHtml : public QThread
{
    Q_OBJECT
public:
    explicit ExportToHtml(QObject *parent = nullptr);
    void process();
    void run();
    void setEntries(QList<EntryModel*>*);
    void setDict(DictModel*);
    void setBaseName(QString);
    void setDir(QString);

signals:
    void emitComplete();

private:
    QList<EntryModel*>* entries;
    DictModel* dict;
    QString baseName;
    QString basePath{""};
    QString dict_title{""};
    QString dict_content{""};
    QString entry_menu{""};
    QString entries_list{""};
    QString dir;

    void writeFile(QString, QString);
    QString readFile(QString);
};

#endif // EXPORTTOHTML_H
