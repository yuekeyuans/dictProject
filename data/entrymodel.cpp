#include "entrymodel.h"
#include <QSqlQuery>
#include "data/appsqlite.h"
#include <QDateTime>
#include <QVariant>
#include <QTextDocument>

EntryModel::EntryModel(QObject *parent) : QObject(parent)
{
    sorts = new QMap<QString, QString>();
    sorts->insert(tr("timeUp"), "order by createDate asc");
    sorts->insert(tr("timeDown"), "order by createDate desc");
    sorts->insert(tr("nameUp"), "order by entry asc");
    sorts->insert(tr("nameDown"), "order by entry desc");
    sorts->insert(tr("lastViewUp"), "order by lastViewDate desc");
    sorts->insert(tr("lastUpdateUp"), "order by lastUpdateDate desc");
    textDocument = new QTextDocument;
}

QList<EntryModel*>* EntryModel::loadAll(){
    QList<EntryModel*>* list = new QList<EntryModel*>();
    QSqlQuery query;
    query.exec("select * from entry");
    while(query.next()){
        EntryModel* model = new EntryModel();
        model->id = query.value("id").toInt();
        model->text = query.value("text").toString();
        model->mkdown = query.value("mkdown").toString();
        model->entry = query.value("entry").toString();
        model->html = query.value("html").toString();
        model->createDate = query.value("createDate").toString();
        model->lastViewDate = query.value("lastViewDate").toString();
        model->lastUpdateDate = query.value("lastUpdateDate").toString();
        list->append(model);
    }
    return list;
}

// TODO: 这里时间的比较是直接比较的，不知道会不会有影响
void EntryModel::loadAll(QList<QPair<int, QString>>* list, QString keyWord, QString sortType){
    list->clear();
    QSqlQuery query;

    QString whereArgs = "";
    if(keyWord.trimmed() != ""){
        whereArgs = QString(" where entry like '%"+keyWord.trimmed()+"%' ");
    }
    QString orderBy = sorts->value(sortType);
    QString sql = "select id, entry from entry ";
    sql.append(whereArgs);
    sql.append(orderBy);
    query.exec(sql);
    while(query.next()){
        QPair<int, QString> pair;
        pair.first = query.value("id").toInt();
        pair.second = query.value("entry").toString();
        list->append(pair);
    }
}

EntryModel* EntryModel::copyLoad(){
    EntryModel* model = new EntryModel();
    load();
    setLastViewDate();
    model->id = id;
    model->entry = entry;
    model->text = text;
    model->html = html;
    model->mkdown =mkdown;
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
        text = query.value("text").toString();
        mkdown = query.value("mkdown").toString();
        entry = query.value("entry").toString();
        html = query.value("html").toString();
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
            SET [entry] = :entry, [html] = :html WHERE  [id] = :id";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    query.bindValue(":entry", entry);
    query.bindValue(":html", html);
    query.exec();
    textDocument->setHtml(html);
    setText(textDocument->toPlainText());
}

void EntryModel::insert(){
    id = getNextId();
    createDate = QDateTime::currentDateTime().toString();
    lastViewDate = createDate;
    lastUpdateDate = createDate;
    QString sql = "INSERT INTO [entry]( [id], [entry], [text], [mkdown], [html], [createdate], [lastUpdateDate], [lastViewDate]) \
                   VALUES ( :id, :entry, :text, :mkdown, :html, :createDate, :lastUpdateDate, :lastViewDate)";

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    query.bindValue(":entry", entry);
    query.bindValue(":html", html);
    query.bindValue(":text", text);
    query.bindValue(":mkdown", mkdown);
    query.bindValue(":createDate", createDate);
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

EntryModel::~EntryModel(){
    delete sorts;
    delete textDocument;
}
