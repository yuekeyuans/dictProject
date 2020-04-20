#ifndef EXPORTTOEXCEL_H
#define EXPORTTOEXCEL_H

#include <QObject>

class ExportToExcel : public QObject
{
    Q_OBJECT
public:
    explicit ExportToExcel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // EXPORTTOEXCEL_H
