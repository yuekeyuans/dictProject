#ifndef EXPORTTOPDB_H
#define EXPORTTOPDB_H

#include <QObject>

class ExportToPdb : public QObject
{
    Q_OBJECT
public:
    explicit ExportToPdb(QObject *parent = nullptr);

signals:

public slots:
};

#endif // EXPORTTOPDB_H
