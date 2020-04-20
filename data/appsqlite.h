#ifndef APPSQLITE_H
#define APPSQLITE_H

#include <QObject>
#include <QtSql>
class AppSqlite
{
private:
    QSqlDatabase database;
    QString dbFile = "a.db";
    static AppSqlite* _appSqlite;

public:
    AppSqlite();
    bool openDatabase();
    bool initDatabase();
    void doSomething(){qDebug()<< "hello world";}
    void quit();
    static AppSqlite* instance(){return _appSqlite;}
};


#define SDB AppSqlite::instance()

#endif // APPSQLITE_H
