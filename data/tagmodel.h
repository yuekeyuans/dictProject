#ifndef TAGMODEL_H
#define TAGMODEL_H

#include <QObject>

class TagModel : public QObject
{
    Q_OBJECT
public:
    const static QString TAG_ID_NULL;
    const static QString TAG_ID_PARENT;
    const static QString TAG_ID_ANCHOR;
    const static QString TAG_ID_PLUGIN;

    explicit TagModel(QObject *parent = nullptr);
    explicit TagModel(QString);
    QString id{TAG_ID_NULL};
    int size{0};
    int sortId{0};
    QString name{""};
    QString type{"user"};
    bool locked{false};
    bool fold{true};
    QString parentId{TAG_ID_PARENT};

    bool insert();
    bool deleted();
    bool deleted(QList<QString>*);
    bool update();

    void load();
    TagModel *copy();
    QList<TagModel*> *load(QString ids, QList<TagModel*>* tags = nullptr);
    void setSize(int);
    int getSize() const;
    void setFold(bool fold);
    int getTotalCount(QString id = TAG_ID_PARENT);

    QList<TagModel*>* loadAll();
    QList<QString> *loadAllTagsAndSubtags(QString id, QList<QString> *tags = nullptr);

public slots:
    void slotInsertTags(QList<TagModel *> *);

signals:
    void emitInsertTagsSucceed();

private:
    QString getNextId();
    int getNextSortId();

};

#endif // TAGMODEL_H
