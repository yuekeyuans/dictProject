#ifndef ENTRYMODEL_H
#define ENTRYMODEL_H

#include <QObject>
#include <QPair>
#include <QTextDocument>

class EntryModel : public QObject
{
    Q_OBJECT
public:
    explicit EntryModel(QObject *parent = nullptr);
    EntryModel(QString entry, QString html);
    EntryModel(int id, QString entry, QString html);
    ~EntryModel();
    int id = -1;
    QString entry;
    QString text;
    QString mkdown;
    QString html;
    QString createDate;
    QString lastUpdateDate;
    QString lastViewDate;

    void loadAll(QList<QPair<int, QString>>*, QString keyword, QString sortType);
    QList<EntryModel*>* loadAll();
    EntryModel* copyLoad();
    QMap<QString, QString>* sorts;
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
    void setLastUpdateDate();
    void setHtml(QString);
    void setMkDown(QString);
    void setText(QString);

private:
    int getNextId();
};

#endif // ENTRYMODEL_H
