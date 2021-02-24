#ifndef EXPORTTOTAG_H
#define EXPORTTOTAG_H

#include <QObject>
#include <QThread>
#include <QSqlDatabase>
#include "data/tagmodel.h"
#include "data/entrymodel.h"
#include "extra/tagexportoptionsdialog.h"

class ExportToTag : public QThread
{
    Q_OBJECT
public:
    explicit ExportToTag(QObject *parent = nullptr);
    ~ExportToTag();
    void run();
    void setTag(TagModel *);
    void setExportType(TagExportOptionsDialog::TagVal);
    void setName(QString name);
    void setFilePath(QString);
    void setTags(QList<TagModel *> *);
    void setEntries(QList<EntryModel *> *);

    void exportFlat();
    void exportToPlugin();
    void exportToParent();
    void exportOrignal();

    void writeTags();
    void writeEntries();

signals:
    void emitComplete();

public slots:

private:
    TagModel *model;
    TagExportOptionsDialog::TagVal tagOption;
    QList<TagModel *> *tags;
    QList<EntryModel *> *entries;
    QString filePath;
};

#endif // EXPORTTOTAG_H
