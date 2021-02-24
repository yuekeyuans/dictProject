#ifndef DICTMODEL_H
#define DICTMODEL_H

#include <QObject>
#include <QDateTime>
#include "qt-json-master/json.h"

using namespace QtJson;

class DictModel : public QObject
{
    Q_OBJECT
public:
    explicit DictModel(QObject *parent = nullptr);
    int id{-1};
    QString title{""};
    QString description{""};
    QString image{""};
    QString html{""};

    int getNextId();

    DictModel* loadAll();

public slots:
    void insert();
    void update();
    void load();

};

#endif // DICTMODEL_H
