#include "appsqlite.h"
#include <QtSql>
#include "globalsetting.h"
#include "QDir"
#include "extra/utils.h"
#include <QTime>

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
        createDatabase();
    }
    if(dictName != ""){
        initDatabase ();
    }
    _appSqlite = this;
    initTagCount();
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

bool AppSqlite::createDatabase(){

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
       if(!sql_query.exec(SQL_CREATE_TAG_TABLE)){ //创建表entry 表
           qWarning("[SQL] %s",qPrintable(sql_query.lastError().text()));
           return false;
       }
        return true;
    }
    qWarning("Init database failed,database is not open.");
    return false;
}

void AppSqlite::initDatabase(){
    QSqlQuery query1;

    query1.prepare(SQL_INIT_DICT_TABLE);
    query1.bindValue(":title", dictName);
    query1.exec();

    QSqlQuery query2;
    query2.exec (SQL_INIT_TAG_TABLE_ANCHOR);

    QSqlQuery query3;
    query3.exec (SQL_INIT_TAG_TABLE_PLUGIN);
}

void AppSqlite::initTagCount()
{
    QSqlQuery query;
    query.exec(SQL_INIT_TAG_COUNT);
}

AppSqlite::~AppSqlite(){

}
