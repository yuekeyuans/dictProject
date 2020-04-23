#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include <QObject>
#include <QPair>
#include <QTextDocument>
#include <iostream>
using namespace std;

class EntryModel : public QObject
{
    Q_OBJECT
public:
    explicit EntryModel(QObject *parent = nullptr);
    EntryModel(int);
    EntryModel(QString);
    EntryModel(QString entry, QString html);
    EntryModel(int id, QString entry, QString html);

    EntryModel(const EntryModel&) =default;
    EntryModel& operator=(const EntryModel&) =default;
    ~EntryModel();
    int id = -1;
    int sortId{-1};
    bool isVisiable{true};
    QString entry;
    QString text;
    QString mkdown;
    QString html;
    QString createDate;
    QString lastUpdateDate;
    QString lastViewDate;
    bool isEntry{true};

    EntryModel* copyLoad();
    QList<EntryModel*>* loadAll(QString keyword="", bool allTextSearch=false, QString sortType="id");
    QTextDocument* textDocument;


    bool checkExist();

signals:

public slots:
    void insert();
    void update();
    void deleted();
    void load();
    void insertOrUpdate();

    void setLastViewDate();
    void setVisiable(bool);
    void setLastUpdateDate();
    void setHtml(QString);
    void setMkDown(QString);
    void setText(QString);
    void setSortId(int);
    int getTotalCount();

private:
    int getNextId();
};
#endif // ENTRYMODEL_H
