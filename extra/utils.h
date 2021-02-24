#ifndef UTILS_H
#define UTILS_H

#include <QObject>

class Utils : public QObject
{
    Q_OBJECT
public:
    explicit Utils(QObject *parent = nullptr);

    static QString getUid();

    const static QList<QChar> CHARS;

private:
    static QString transform(qlonglong);
};

#endif // UTILS_H
