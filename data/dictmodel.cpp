#include "dictmodel.h"
#include <QDateTime>
#include <QtSql>
#include "appsqlite.h"

using namespace QtJson;

DictModel::DictModel(QObject *parent) : QObject(parent)
{

}

int DictModel::getNextId(){
    QSqlQuery query(AppSqlite::instance()->database);
    query.exec("select * from dict");
    auto model = new QSqlQueryModel();
    model->setQuery(query);
    int rowCount = model->rowCount();
    if(rowCount == 0){
        delete model;
        return 1;
    }

    query.exec("select max(id) from dict");
    while(query.next()){
        return query.value(0).toInt() + 1;
    }
    return 1;
}

void DictModel::insert(){
    id = getNextId();
    if(id != 1){
        update();
        return;
    }
    QSqlQuery query(AppSqlite::instance()->database);
    query.prepare("INSERT INTO [dict]  \
                            ([id], [title], [description], [image], [html]) \
                     VALUES (:id, :title, :description, '', :html)");
    query.bindValue(":id", id);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":html", html);
    query.exec();
}


void DictModel::update(){
    QSqlQuery query(AppSqlite::instance()->database);
    query.prepare("UPDATE [dict] SET [title] = :title, [description] = :description, [html] = :html");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":html", html);
    query.exec();
}

void DictModel::load(){
    QSqlQuery query(AppSqlite::instance()->database);
    query.exec("select * from dict where id = 1");
    while(query.next()){
        id = query.value("id").toInt();
        title = query.value("title").toString();
        description = query.value("description").toString();
        html = query.value("html").toString();
        image = query.value("image").toString();
    }
}

DictModel* DictModel::loadAll(){
    this->load();
    DictModel* model = new DictModel();
    model->id = id;
    model->image = image;
    model->title = title;
    model->html = html;
    model->description = description;
    return model;
}
