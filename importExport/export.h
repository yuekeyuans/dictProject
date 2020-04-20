#ifndef EXPORT_H
#define EXPORT_H

#include <QObject>

class Export : public QObject
{
    Q_OBJECT
public:
    explicit Export(QObject *parent = nullptr);

signals:

public slots:
};

#endif // EXPORT_H
