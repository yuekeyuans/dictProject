#ifndef IMPORTFROMEXCEL_H
#define IMPORTFROMEXCEL_H

#include <QObject>
#include <QThread>

class ImportFromExcel : public QThread
{
    Q_OBJECT
public:
    explicit ImportFromExcel(QObject *parent = nullptr);
    void run();
    void process();


signals:

public slots:
};

#endif // IMPORTFROMEXCEL_H
