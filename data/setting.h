#ifndef SETTING_H
#define SETTING_H

#include <QObject>

//全局存储
class Setting : public QObject
{
    Q_OBJECT
public:
    explicit Setting(QObject *parent = nullptr);
    bool checkDictExist(const QString &path);
    bool addDict(QString name, QString path);
    void delectDict(QString name);
    void saveDict();
    bool loadDict();
    QString getName(QString path);
    QString getPath(QString name);

    QList<QMap<QString, QString>> getSubMenu();

private:
    QList<QMap<QString, QString>> dicts;



};

#endif // SETTING_H
