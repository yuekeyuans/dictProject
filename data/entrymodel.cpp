#include "entrymodel.h"
#include <QSqlQuery>
#include "data/appsqlite.h"
#include <QDateTime>
#include <QVariant>
#include <QTextDocument>

EntryModel::EntryModel(QObject *parent) : QObject(parent)
{
    textDocument = new QTextDocument;
}

EntryModel::EntryModel(QString entry, QString html):EntryModel(){
    this->entry = entry;
    this->html = html;
}
EntryModel::EntryModel(int id, QString entry, QString html):EntryModel(){
    this->id = id;
    this->entry = entry;
    this->html = html;
}
EntryModel::EntryModel(int id):EntryModel(){
    this->id = id;
    load ();
}
EntryModel::EntryModel(QString name):EntryModel(){
    this->entry = name;
    load ();
}

QList<EntryModel*>* EntryModel::loadAll (QString keyWord, bool allTextSearch, QString sortType){
    QList<EntryModel*>* list = new QList<EntryModel*>();
    QSqlQuery query;

    QString whereArgs = "";
    if(keyWord.trimmed() != ""){
        if(allTextSearch){
            whereArgs = QString(" where entry like '%"+keyWord.trimmed()+"%' or text like '%" + keyWord.trimmed() + "%'");
        }else{
            whereArgs = QString(" where entry like '%"+keyWord.trimmed()+"%' ");
        }
    }
    QString orderBy = " order by sortId asc ";
    QString sql = "select * from entry ";
    sql.append(whereArgs);
    sql.append(orderBy);
    query.exec(sql);
    while(query.next()){
        EntryModel* model = new EntryModel();
        model->id = query.value("id").toInt();
        model->sortId = query.value ("sortId").toInt ();
        model->text = query.value("text").toString();
        model->mkdown = query.value("mkdown").toString();
        model->entry = query.value("entry").toString();
        model->html = query.value("html").toString();
        model->createDate = query.value("createDate").toString();
        model->isVisiable = query.value ("visiable").toString () == "" ? true :false;
        model->lastViewDate = query.value("lastViewDate").toString();
        model->lastUpdateDate = query.value("lastUpdateDate").toString();
        list->append(model);
    }
    return list;
}

EntryModel* EntryModel::copyLoad(){
    EntryModel* model = new EntryModel();
    load();
    setLastViewDate();
    model->id = id;
    model->sortId = sortId;
    model->entry = entry;
    model->text = text;
    model->html = html;
    model->mkdown =mkdown;
    model->isVisiable = isVisiable;
    model->createDate = createDate;
    model->lastViewDate = lastViewDate;
    model->lastUpdateDate = lastUpdateDate;
    return model;
}

void EntryModel::load(){
    //如果有id,根据id，不然根据entry 加载 enty;
    QSqlQuery query;
    if(id != -1){
        query.prepare("select * from entry where id = :id");
        query.bindValue(":id", id);
    }else {
        query.prepare("select * from entry where entry = :entry");
        query.bindValue(":entry", entry);
    }
    query.exec();
    while(query.next()){
        id = query.value("id").toInt();
        sortId = query.value ("sortId").toInt ();
        text = query.value("text").toString();
        mkdown = query.value("mkdown").toString();
        entry = query.value("entry").toString();
        html = query.value("html").toString();
        isVisiable =  query.value ("visiable").toString () == "no" ? false:true;
        createDate = query.value("createDate").toString();
        lastViewDate = query.value("lastViewDate").toString();
        lastUpdateDate = query.value("lastUpdateDate").toString();
    }
}

void EntryModel::deleted(){
    QString sql = "delete from entry where id = :id";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    query.exec();
}

void EntryModel::insertOrUpdate(){
    if(checkExist()){
        update();
    }else{
        insert();
    }
}

void EntryModel::update(){
    setLastUpdateDate();
    QString sql = "UPDATE [entry] \
            SET [entry] = :entry, [html] = :html,[sortId] = :sortId, [visiable] = :visiable \
            WHERE  [id] = :id";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    query.bindValue(":entry", entry);
    query.bindValue(":html", html);
    query.bindValue (":sortId", sortId);
    query.bindValue (":visiable", isVisiable ? "yes":"no");
    query.exec();
    textDocument->setHtml(html);
    setText(textDocument->toPlainText());
}

void EntryModel::insert(){
    id = getNextId();
    sortId = id;
    createDate = QDateTime::currentDateTime().toString();
    lastViewDate = createDate;
    lastUpdateDate = createDate;
    QString sql = "INSERT INTO [entry]( [id], [sortId], [entry], [text], [mkdown], [html],[visiable], [createdate], [lastUpdateDate], [lastViewDate]) \
                   VALUES ( :id, :sortId, :entry, :text, :mkdown, :html, :visiable, :createDate, :lastUpdateDate, :lastViewDate)";

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    query.bindValue (":sortId", sortId);
    query.bindValue(":entry", entry);
    query.bindValue(":html", html);
    query.bindValue(":text", text);
    query.bindValue(":mkdown", mkdown);
    query.bindValue(":createDate", createDate);
    query.bindValue (":visiable", isVisiable ?"yes":"no");
    query.bindValue(":lastUpdateDate", lastUpdateDate);
    query.bindValue(":lastViewDate", lastViewDate);
    query.exec();

    textDocument->setHtml(html);
    setText(textDocument->toPlainText());
}

int EntryModel::getNextId(){
    QSqlQuery query(AppSqlite::instance()->database);
    query.exec("select * from entry");
    auto model = new QSqlQueryModel();
    model->setQuery(query);
    int rowCount = model->rowCount();
    if(rowCount == 0){
        delete model;
        return 1;
    }

    query.exec("select max(id) from entry");
    while(query.next()){
        return query.value(0).toInt() + 1;
    }
    return 1;
}

bool EntryModel::checkExist(){
    QSqlQuery query(AppSqlite::instance()->database);
    if(id != -1){
        query.prepare("select * from entry where id = :id");
        query.bindValue(":id", id);
    }else {
        query.prepare("select * from entry where entry = :entry");
        query.bindValue(":entry", entry);
    }
    query.exec();
    auto model = new QSqlQueryModel();
    model->setQuery(query);
    int rowCount = model->rowCount();
    return rowCount == 1;
}

void EntryModel::setHtml(QString html){
    this->html = html;
    if(id==-1){
        return;
    }
    QSqlQuery query;
    query.prepare(("update entry set html = :html where id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":html", html);
    query.exec();
}

void EntryModel::setText(QString text){
    this->text = text;
    if(id==-1){
        return;
    }
    QSqlQuery query;
    query.prepare(("update entry set text = :text where id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":text", text);
    query.exec();
}

void EntryModel::setMkDown(QString mkdown){
    this->mkdown = mkdown;
    if(id==-1){
        return;
    }
    QSqlQuery query;
    query.prepare(("update entry set mkdown = :mkdown where id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":mkdown", mkdown);
    query.exec();
    qDebug() << query.lastError().text();
}

void EntryModel::setLastViewDate(){
    this->lastViewDate = QDateTime::currentDateTime().toString();
    if(id==-1){
        return;
    }
    QSqlQuery query;
    query.prepare(("update entry set lastViewDate = :lastViewDate where id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":lastViewDate", this->lastViewDate);
    query.exec();
}

void EntryModel::setLastUpdateDate(){
    this->lastUpdateDate = QDateTime::currentDateTime().toString();
    if(id==-1){
        return;
    }
    QSqlQuery query;
    query.prepare(("update entry set lastUpdateDate = :lastUpdateDate where id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":lastUpdateDate", lastUpdateDate);
    query.exec();
}

int EntryModel::getTotalCount (){
    QSqlQuery query(AppSqlite::instance()->database);
    query.exec("select * from entry");
    auto model = new QSqlQueryModel();
    model->setQuery(query);
    return model->rowCount();
}

void EntryModel::setVisiable (bool visiable){
    this->isVisiable = visiable;
    this->isVisiable = visiable;
    QString sql = "UPDATE [entry] \
            SET [visiable] = :visiable \
            WHERE  [id] = :id";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    query.bindValue (":visiable", this->isVisiable?"yes":"no");
    query.exec ();
}

void EntryModel::setSortId(int sortId){
    this->sortId = sortId;
    QString sql = "UPDATE [entry] \
            SET [sortId] = :sortId \
            WHERE  [id] = :id";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    query.bindValue (":sortId", this->sortId);
    query.exec ();
}

EntryModel::~EntryModel(){
    delete textDocument;
}
