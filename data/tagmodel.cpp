#include "tagmodel.h"
#include <QSqlQuery>
#include "data/appsqlite.h"
#include <QDateTime>
#include <QVariant>
#include <QSettings>
#include "extra/utils.h"
#include <QProgressDialog>

const QString TagModel::TAG_ID_PARENT = "0";
const QString TagModel::TAG_ID_NULL = "-1";
const QString TagModel::TAG_ID_ANCHOR = "anchor_1";
const QString TagModel::TAG_ID_PLUGIN = "plugin_2";

TagModel::TagModel(QObject *parent) : QObject(parent){

}

TagModel::TagModel(QString id):QObject(nullptr){
    this->id = id;
}

bool TagModel::insert(){

    id = getNextId();
    sortId = getNextSortId();

    QSqlQuery query;
    query.prepare ("insert into tag (id, sortId, name, size, type, locked, fold, parentId) \
                    values (:id, :sortId, :name, :size, :type, :locked, :fold, :parentId)");
    query.bindValue (":id", id);
    query.bindValue (":sortId", sortId);
    query.bindValue (":name", name);
    query.bindValue (":size", size);
    query.bindValue (":type", type);
    query.bindValue (":locked", locked ? "yes":"no");
    query.bindValue (":fold", fold? "yes":"no");
    query.bindValue(":parentId", parentId);


    auto res = query.exec();
    SDB->initTagCount();
    return res;

}

void TagModel::slotInsertTags(QList<TagModel *> *tags)
{
    QVariantList _id;
    QVariantList _name;
    QVariantList _sortId;
    QVariantList _size;
    QVariantList _type;
    QVariantList _locked;
    QVariantList _fold;
    QVariantList _parentId;
    for (auto tag : *tags) {
        _id << tag->id;
        _sortId << tag->sortId;
        _name << tag->name;
        _size << tag->size;
        _type << tag->type;
        _locked << (tag->locked ? "yes" : "no");
        _fold << (tag->fold ? "yes" : "no");
        _parentId << tag->parentId;
    }

    QSqlQuery query;
    query.prepare("insert into tag (id, sortId, name, size, type, locked, fold, parentId) \
                    values (:id, :sortId, :name, :size, :type, :locked, :fold, :parentId)");
    query.bindValue(":id", _id);
    query.bindValue(":sortId",_sortId);
    query.bindValue(":name", _name);
    query.bindValue(":size", _size);
    query.bindValue(":type", _type);
    query.bindValue(":locked", _locked);
    query.bindValue(":fold", _fold);
    query.bindValue(":parentId", _parentId);
    query.execBatch ();
    query.clear();

    SDB->initTagCount();

    emit emitInsertTagsSucceed();
    qDeleteAll(*tags);
    delete tags;
}

bool TagModel::update(){
    if(id == TAG_ID_NULL){
        return insert();
    }

    QSqlQuery query;
    query.prepare ("update tag set sortId = :sortId, name = :name, size = :size, \
                   type = :type, locked = :locked, fold = :fold, parentId = :parentId where id = :id");
    query.bindValue (":id", id);
    query.bindValue (":sortId", sortId);
    query.bindValue (":name", name);
    query.bindValue (":size", size);
    query.bindValue (":type", type);
    query.bindValue (":locked", locked ? "yes":"no");
    query.bindValue (":fold", fold? "yes":"no");
    query.bindValue (":parentId", parentId);

    return query.exec ();
}

bool TagModel::deleted(){
    QSqlQuery query;
    query.prepare ("delete from tag where id = :id");
    query.bindValue (":id", id);
    return query.exec ();
}

bool TagModel::deleted(QList<QString>* list){
    if (list == nullptr || list->length () == 0
        || list->contains(TAG_ID_ANCHOR) || list->contains(TAG_ID_PLUGIN)) {
        return false;
    }
    QString ids = "(";
    for(auto l : *list){
        ids = (ids + "'" + l +"',");
    }
    ids = ids.left (ids.length () -1);
    ids = (ids + ")");

    QSqlQuery query;

    auto res = query.exec("delete from tag where id in " + ids);
    SDB->initTagCount();
    return res;

}

void TagModel::load(){
    bool hasTag = false;
    QSqlQuery query;
    if(id != TAG_ID_NULL && id != TAG_ID_PARENT){
        query.prepare ("select * from tag where id = :id");
        query.bindValue (":id", id);
        hasTag = true;
    }
    if(hasTag){
        query.exec ();
        while(query.next ()){
            id = query.value ("id").toString ();
            name = query.value ("name").toString ();
            sortId = query.value ("sortId").toInt ();
            size = query.value ("size").toInt ();
            type = query.value ("type").toString ();
            fold = query.value ("fold").toString () == "yes"? true : false;
            locked = query.value ("locked").toString () == "yes"? true : false;
            parentId = query.value ("parentId").toString ();
        }
    }
}

QList<TagModel *> *TagModel::load(QString ids, QList<TagModel *> *tags)
{
    if (SDB == nullptr) {
        return new QList<TagModel *>;
    }
    if (tags == nullptr) {
        tags = new QList<TagModel *>;
    }
    if (ids == TAG_ID_NULL || ids == TAG_ID_PARENT) {
        return tags;
    }
    TagModel model;
    model.id = ids;
    model.load();

    tags->append(model.copy());
    QSqlQuery query;
    query.prepare("select * from tag where parentId = :parentId");
    query.bindValue(":parentId", model.id);
    query.exec();
    while (query.next()) {
        TagModel tag;

        tag.id = query.value("id").toString();
        tag.name = query.value("name").toString();
        tag.sortId = query.value("sortId").toInt();
        tag.size = query.value("size").toInt();
        tag.type = query.value("type").toString();
        tag.fold = query.value("fold").toString() == "yes" ? true : false;
        tag.locked = query.value("locked").toString() == "yes" ? true : false;
        tag.parentId = query.value("parentId").toString();

        bool isContain = false;
        for (auto a : *tags) {
            if (a->id == tag.id) {
                isContain = true;
            }
        }
        if(!isContain){
            tags->append (tag.copy ());
            load (name, tags);
        }
    }
    return tags;
}

QList<TagModel*>* TagModel::loadAll(){
    auto list = new QList<TagModel *>;

    if (SDB == nullptr) {
        return list;
    }

    QList<QString> sort;
    sort.append (TAG_ID_PARENT);

    while(sort.length () > 0){
        auto parentIds = sort.front ();
        sort.pop_front ();

        QSqlQuery query;
        query.prepare("select * from tag  where parentId = :parentId order by sortId asc");
        query.bindValue(":parentId", parentIds);
        query.exec();
        while (query.next()) {
            auto tag = new TagModel();
            tag->id = query.value("id").toString();
            tag->name = query.value("name").toString();
            tag->sortId = query.value("sortId").toInt();
            tag->size = query.value("size").toInt();
            tag->type = query.value("type").toString();
            tag->fold = query.value("fold").toString() == "yes" ? true : false;
            tag->locked = query.value("locked").toString() == "yes" ? true : false;
            tag->parentId = query.value("parentId").toString();
            if (!sort.contains(tag->id)) {
                sort.append(tag->id);
            }
            list->append(tag);
        }
    }
    return list;
}

int TagModel::getTotalCount(QString _parentId){
    QString sql = "select * from tag where parentId = :parentId";

    QSqlQuery query;
    query.prepare (sql);
    query.bindValue (":parentId", _parentId);
    query.exec();
    auto model = new QSqlQueryModel();
    model->setQuery(query);
    return model->rowCount();
}

int TagModel::getNextSortId(){
    QSqlQuery query;
    query.exec("select * from tag");
    auto model = new QSqlQueryModel();
    model->setQuery(query);
    int rowCount = model->rowCount();
    if(rowCount == 0){
        delete model;
        return 1;
    }

    query.exec("select max(sortId) from tag");
    while(query.next()){
        return query.value(0).toInt() + 1;
    }
    return 1;
}

void TagModel::setFold(bool fold){
    QSqlQuery query;
    query.prepare ("update tag set fold = :fold where id = :id");
    query.bindValue (":fold", fold ? "yes":"no");
    query.bindValue (":id", id);
    query.exec ();
}

QList<QString>* TagModel::loadAllTagsAndSubtags(QString ids, QList<QString>* tags){
    if (SDB == nullptr) {
        return new QList<QString>;
    }
    if(tags == nullptr){
        tags = new QList<QString>;
    }
    if(ids == TAG_ID_NULL || ids == TAG_ID_PARENT){
        return tags;
    }
    tags->append (ids);
    QSqlQuery query;
    query.prepare ("select name from tag where parentId = :parentId");
    query.bindValue (":parentId", ids);
    query.exec ();
    while(query.next ()){
        name = query.value("name").toString ();
        if(!tags->contains (name)){
            tags->append (name);
            loadAllTagsAndSubtags (name, tags);
        }
    }
    return tags;
}

void TagModel::setSize(int sz)
{
    this->size = sz;
    QSqlQuery query;
    query.prepare("update tag set size = :size where id = :id");
    query.bindValue(":size", id);
    query.bindValue(":id", id);
    query.exec ();
}

int TagModel::getSize() const
{
    return this->size;
}

TagModel *TagModel::copy()
{
    TagModel *model = new TagModel;
    model->id = id;
    model->name = name;
    model->size = size;
    model->sortId = sortId;
    model->type = type;
    model->locked = locked;
    model->parentId = parentId;
    model->fold = fold;
    return model;
}

QString TagModel::getNextId(){
    return Utils::getUid ();
}

