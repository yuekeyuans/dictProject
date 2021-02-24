#ifndef IMPORTFROMEXCEL_H
#define IMPORTFROMEXCEL_H

#include <QThread>
#include <data/entrymodel.h>
#include <data/dictmodel.h>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

using namespace QXlsx;

class ImportFromExcel : public QThread
{
    Q_OBJECT
public:
    explicit ImportFromExcel(QObject *parent = nullptr);
    ~ImportFromExcel();
    void run();
    void process();

    QString processHtml(QString);
    void importExcel();

    void processVersion1();
    void processVersion2();

    void setFilePath(QString);

signals:
    void emitInsertDict();
    void emitInsertEntries(QList<EntryModel*> *);

    void emitInsertTags(QList<TagModel *> *);

    void emitSuccess();
    void emitFail();
public slots:

private:
    EntryModel *entryModel;
    DictModel *dictModel;
    TagModel *tagModel;

    Document* xlsR{nullptr};
    QString filePath;
};

#endif // IMPORTFROMEXCEL_H
