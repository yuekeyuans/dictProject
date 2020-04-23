#ifndef APPSQLITE_H
#define APPSQLITE_H

#include <QObject>
#include <QtSql>
class AppSqlite
{
private:
    static AppSqlite* _appSqlite;
    AppSqlite();
    ~AppSqlite();

public:
    QSqlDatabase database;
    bool openDatabase();
    bool initDatabase();
    bool initDictTable();

    static QString dbFile;
    static QString dictName;
    static AppSqlite* instance(){return _appSqlite;}
    static AppSqlite* instance(const QString &path){
        AppSqlite::dbFile = path;
        AppSqlite::dictName = QFileInfo(path).baseName();
        new AppSqlite();
        return _appSqlite;
    }
    static AppSqlite* instance(const QString &path, const QString &name){
        AppSqlite::dbFile = path;
        AppSqlite::dictName = name;
        return instance(path);
    }
    static void close(){
        AppSqlite::dbFile = "";
        AppSqlite::dictName = "";
        if(_appSqlite != nullptr){
            if(_appSqlite->database.isOpen()){
                _appSqlite->database.close();
            }
            delete _appSqlite;
            _appSqlite = nullptr;
        }
    }
};

//AppSqlite* AppSqlite::_appSqlite = nullptr;

#define SDB AppSqlite::instance()

#endif // APPSQLITE_H
