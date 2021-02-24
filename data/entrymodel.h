#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include <QObject>
#include <QPair>
#include <QTextDocument>
#include <QSqlQuery>
#include <iostream>
#include "tagmodel.h"

using namespace std;

class EntryModel : public QObject
{
    Q_OBJECT
public:

    const static QString ENTRY_ID_NULL;

    explicit EntryModel(QObject *parent = nullptr);
    EntryModel(QString);
//    EntryModel(QString entry, QString html);
//    EntryModel(QString id, QString entry, QString html);

    EntryModel(const EntryModel&) =default;
    EntryModel& operator=(const EntryModel&) =default;
    ~EntryModel();
    QString id{ENTRY_ID_NULL};
    QString tagId{TagModel::TAG_ID_PARENT};
    int sortId{0};
    QString entry{""};
    QString text{""};
    QString mkdown{""};
    QString html{""};
    QString createDate{""};
    QString lastUpdateDate{""};
    QString lastViewDate{""};
    bool isVisiable{true};

    bool isEntry{true};

    EntryModel* copy();

    QList<EntryModel*>* loadAll(QString keyword="",
                                 bool allTextSearch=false,
                                 bool showHidden = false);
    QList<EntryModel*>* loadAllInList(QString keyword="",
                                 bool allTextSearch=false,
                                 bool showHidden = false);

    QList<QMap<QString, QString>>* loadNames(QString, bool);
    QList<QMap<QString, QString>>* loadAchors(QString);

    QList<QString>* loadAchors();
    void load();
    QList<EntryModel *> *load(QList<TagModel*>);
    QList<EntryModel *> *loadByTagId(QString);

    bool checkExist();
    bool insert();
    bool update();
    void deleted();
    void deleted(QList<QString>* tags);
    bool insertOrUpdate();

    void setLastViewDate();
    void setVisiable(bool);
    void setLastUpdateDate();
    void setHtml(QString);
    void setMkDown(QString);
    void setText(QString);
    void setSortId(int);
    void setTag(QString);

    int getTotalCount();
    int getShowCount();
    int getHideCount();

public slots:
    void slotinsertEntries(QList<EntryModel *> *);

signals:
    void emitInsertEntriesSucceed();

private:
    QString getNextId();
    int getNextSortId();
    QList<EntryModel *> *queryToEntry(QSqlQuery &, QList<EntryModel *> * = nullptr);
    void bindParameter(QSqlQuery&, EntryModel* = nullptr);

    QTextDocument* textDocument;
};

#endif // ENTRYMODEL_H
