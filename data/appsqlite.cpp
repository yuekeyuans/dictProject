#include "appsqlite.h"
#include <QtSql>
#include "sqlitesource.h"
#include "QDir"

QString AppSqlite::dbFile = "";
QString AppSqlite::dictName = "";


AppSqlite::AppSqlite()
{
    // 如果没有文件，返回
    if(dbFile == ""){
        return;
    }

    //关闭原先数据库
    if(_appSqlite != nullptr){
        if(_appSqlite->database.isOpen()){
            _appSqlite->database.close();
        }
        delete _appSqlite;
        _appSqlite = nullptr;
    }

    if(openDatabase()){
        initDatabase();
    }
    if(dictName != ""){
        initDictTable();
    }
    _appSqlite = this;
}

bool AppSqlite::openDatabase(){
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dbFile);
    if (!database.open())    {
        qWarning(qPrintable(QString("Connect database %1 error, %2").arg(dbFile).arg(database.lastError().text())));
        return false;
    }
    qWarning(qPrintable(QString("Connect database %1 succeed.").arg(dbFile)));
    return true;
}

bool AppSqlite::initDatabase(){

    if (database.open())
    {
        QSqlQuery sql_query;

       if(!sql_query.exec(SQL_CREATE_DICT_TABLE)){  //创建表dict 表
            qWarning("[SQL] %s",qPrintable(sql_query.lastError().text()));
            return false;
        }
       if(!sql_query.exec(SQL_CREATE_ENTRY_TABLE)){ //创建表entry 表
           qWarning("[SQL] %s",qPrintable(sql_query.lastError().text()));
           return false;
       }
        return true;
    }
    qWarning("Init database failed,database is not open.");
    return false;
}

bool AppSqlite::initDictTable(){
    QSqlQuery query;
    query.prepare("INSERT INTO [dict]([id],[title],[description],[image],[html]) VALUES (1,:title,'','','')");
    query.bindValue(":title", dictName);
    bool value = query.exec();
    return value;
}

AppSqlite::~AppSqlite(){

}
