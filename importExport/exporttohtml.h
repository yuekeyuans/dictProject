#ifndef EXPORTTOHTML_H
#define EXPORTTOHTML_H

#include <QObject>

class ExportToHtml : public QObject
{
    Q_OBJECT
public:
    explicit ExportToHtml(QObject *parent = nullptr);

signals:

public slots:
};

#endif // EXPORTTOHTML_H
