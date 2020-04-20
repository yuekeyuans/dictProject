#include "appsqlite.h"
#include <QtSql>
#include "sqlitesource.h"
#include "QDir"

AppSqlite::AppSqlite()
{
    assert(_appSqlite == nullptr && "only one instance allowed");

    if(openDatabase()){
        initDatabase();
    }
    _appSqlite = this;
}

bool AppSqlite::openDatabase(){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dbFile);
    if (!database.open())    {
        qWarning(qPrintable(QString("Connect database %1 error, %2").arg(dbFile).arg(database.lastError().text())));
        return false;
    }else{
        qWarning(qPrintable(QString("Connect database %1 succeed.").arg(dbFile)));
        return true;
    }
}

bool AppSqlite::initDatabase(){

    if (database.open())
    {
        QSqlQuery sql_query;

        //创建表dict 表
       if(!sql_query.exec(SQL_CREATE_DICT_TABLE))
        {
            qWarning("[SQL] %s",qPrintable(sql_query.lastError().text()));
            return false;
        }
       //创建表dict 表
      if(!sql_query.exec(SQL_CREATE_ENTRY_TABLE))
       {
           qWarning("[SQL] %s",qPrintable(sql_query.lastError().text()));
           return false;
       }
        return true;
    }
    else
    {
        qWarning("Init database failed,database is not open.");
        return false;
    }
}

void AppSqlite::quit(){
    if(database.isOpen()){
        database.close();
    }
}
