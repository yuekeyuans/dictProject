#ifndef DICTMODEL_H
#define DICTMODEL_H

#include <QObject>

class DictModel : public QObject
{
    Q_OBJECT
public:
    explicit DictModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // DICTMODEL_H
