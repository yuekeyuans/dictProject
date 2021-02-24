#include "entrymodel.h"
#include <QSqlQuery>
#include "data/appsqlite.h"
#include <QDateTime>
#include <QVariant>
#include <QTextDocument>
#include "extra/utils.h"
#include <QApplication>
#include <QProgressDialog>
#include <QMessageBox>

const QString EntryModel::ENTRY_ID_NULL = "-1";

EntryModel::EntryModel(QObject *parent) : QObject(parent)
{
    textDocument = new QTextDocument;
    id = ENTRY_ID_NULL;
}

EntryModel::EntryModel(QString id):EntryModel(){
    this->id = id;
}

QList<EntryModel*>* EntryModel::loadAll (QString keyWord, bool allTextSearch,  bool showHidden){
    QList<EntryModel*>* list = new QList<EntryModel*>();
    if (SDB == nullptr) {
        return list;
    }

    QSqlQuery query;
    QString sql = "select * from entry ";
    QString whereArgs = "where 1 = 1 ";
    if(keyWord.trimmed() != ""){
        whereArgs += allTextSearch ? QString(" and (entry like '%"+keyWord.trimmed()+"%' or text like '%" + keyWord.trimmed() + "%' )")
                                   : QString(" and entry like '%"+keyWord.trimmed()+"%' ");
    }
    whereArgs += showHidden ? "" :(" and visiable = 'yes'");
    sql.append(whereArgs);
    QString orderBy = " order by sortId asc ";
    sql.append(orderBy);
    query.exec(sql);
    return queryToEntry(query, list);
}

QList<EntryModel*>* EntryModel::loadAllInList (QString keyWord, bool allTextSearch,  bool showHidden){
    QList<EntryModel*>* list = new QList<EntryModel*>();

    if (SDB == nullptr) {
        return list;
    }

    QSqlQuery query;
    QString sql = "select id, entry, tagId, text,visiable from entry ";
    QString whereArgs = "where 1 = 1 ";
    if(keyWord.trimmed() != ""){
        whereArgs += allTextSearch ? QString(" and (entry like '%"+keyWord.trimmed()+"%' or text like '%" + keyWord.trimmed() + "%' )")
                                   : QString(" and entry like '%"+keyWord.trimmed()+"%' ");
    }
    whereArgs += showHidden ? "" :(" and visiable = 'yes'");
    sql.append(whereArgs);
    QString orderBy = " order by sortId asc ";
    sql.append(orderBy);
    query.exec(sql);
    while (query.next()) {
        EntryModel *model = list == nullptr ? this : new EntryModel();
        model->id = query.value("id").toString();
        model->tagId = query.value("tagId").toString();
        model->entry = query.value("entry").toString();
        model->isVisiable = query.value("visiable").toString() == "yes" ? true : false;
        if(allTextSearch){
            model->text = query.value("text").toString();
        }
        if (list != nullptr) {
            list->append(model);
        }
    }
    return list;
}

//只匹配 id;
void EntryModel::load()
{
    QSqlQuery query;
    if (id != ENTRY_ID_NULL) {
        query.prepare("select * from entry where id = :id");
        query.bindValue(":id", id);
    }
    query.exec();
    queryToEntry(query);
}

QList<EntryModel *> *EntryModel::load(QList<TagModel*> tags)
{
    auto list = new QList<EntryModel *>;
    if (SDB == nullptr)
        return list;

    for (auto tag : tags) {
        auto l = loadByTagId(tag->id);
        list->append(*l);
        delete l;
    }
    return list;
}

QList<EntryModel *> *EntryModel::loadByTagId(QString parentId)
{
    auto *list = new QList<EntryModel *>;
    if (SDB == nullptr) {
        return list;
    }
    QSqlQuery query;
    if (parentId != ENTRY_ID_NULL) {
        query.prepare("select * from entry where tagId = :id");
        query.bindValue(":id", parentId);
    }
    query.exec();
    return queryToEntry(query, list);
}

void EntryModel::deleted(){
    QString sql = "delete from entry where id = :id";
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":id", id);
    query.exec();
}

void EntryModel::deleted(QList<QString>* tags){
    if (tags == nullptr || tags->length () == 0
        || tags->contains(TagModel::TAG_ID_ANCHOR)
        || tags->contains(TagModel::TAG_ID_PLUGIN)) {
        return;
    }

    QString ids = "(";
    for(auto l : *tags){
        ids = ids + "'" + l +"',";
    }
    ids = ids.left (ids.length () -1);
    ids = ids + ")";

    QSqlQuery query;
    query.exec ("delete from entry where tagId in " + ids);
}

bool EntryModel::insertOrUpdate(){
    if(checkExist()){
        if(id == ENTRY_ID_NULL){
            return false;
        }
        return update();
    }else{
        return insert();
    }
}

bool EntryModel::update(){
    setLastUpdateDate();
    QString sql = "UPDATE [entry] \
            SET [entry] = :entry, [html] = :html, [tagId] = :tagId, [sortId] = :sortId, [visiable] = :visiable \
            WHERE  [id] = :id";
    QSqlQuery query;
    query.prepare(sql);
    bindParameter(query, this);
    auto res = query.exec();
    textDocument->setHtml(html);
    setText(textDocument->toPlainText());
    return res;
}

bool EntryModel::insert(){
    id = getNextId();
    sortId = getNextSortId ();
    createDate = QDateTime::currentDateTime().toString();
    lastViewDate = createDate;
    lastUpdateDate = createDate;
    textDocument->setHtml(html);
    text = textDocument->toPlainText();

    QString sql = "INSERT INTO [entry] ( \
     [id], [sortId],[tagId], [entry], [text], [mkdown], [html],[visiable], [createDate], [lastUpdateDate], [lastViewDate]) \
     VALUES (:id, :sortId, :tagId, :entry, :text, :mkdown, :html, :visiable, :createDate, :lastUpdateDate, :lastViewDate)";

    QSqlQuery query(SDB->database);
    query.prepare(sql);
    bindParameter(query, this);
    return query.exec();
}

//内存泄漏问题。
void EntryModel::slotinsertEntries(QList<EntryModel *> *entries)
{
    QProgressDialog progress;
    progress.setWindowTitle(tr("tips"));
    progress.setLabelText(tr("数据保存中，请稍候..."));
    progress.setCancelButtonText(QString());
    progress.setRange(0, entries->length() - 1);
    progress.setModal(true);
    progress.setMinimumDuration(1);
    int count = 0;

    SDB->database.transaction();
    QSqlQuery query;

    QVariantList _id;
    QVariantList _sortId;
    QVariantList _tagId;
    QVariantList _entry;
    QVariantList _text;
    QVariantList _mkdown;
    QVariantList _html;
    QVariantList _visiable;
    QVariantList _createDate;

    QString sql = "INSERT INTO [entry] ( \
             [id], [sortId],[tagId], [entry], [text], [mkdown], [html], \
             [visiable], [createdate], [lastUpdateDate], [lastViewDate]) \
             VALUES (:id, :sortId, :tagId, :entry, :text, :mkdown, :html, :visiable, :createDate, :lastUpdateDate, :lastViewDate)";
    query.prepare(sql);

    for(auto entry : *entries){
        progress.setValue(count++);
        QString id_ = getNextId();
        _id << id_;
        qDebug() << id_;
        _sortId << getNextSortId(); // sort id 依次往下排列
        _tagId << entry->tagId;
        _entry << entry->entry;
        _mkdown << entry->mkdown;
        _html << entry->html;
        _visiable << (entry->isVisiable ? "yes" : "no");
        _createDate << (entry->createDate == "" ? QDateTime::currentDateTime().toString():entry->createDate);

        if (entry->text == "") {
            textDocument->setHtml(html);
            _text << textDocument->toPlainText();
        } else {
            _text << entry->text;
        }
    }
    query.bindValue(":id", _id);
    query.bindValue(":sortId", _sortId);
    query.bindValue(":tagId", _tagId);
    query.bindValue(":entry", _entry);
    query.bindValue(":text", _text);
    query.bindValue(":mkdown", _mkdown);
    query.bindValue(":html", _html);
    query.bindValue(":visiable", _visiable);
    query.bindValue(":createDate", _createDate);
    query.bindValue(":lastUpdateDate", _createDate);
    query.bindValue(":lastViewDate", _createDate);
    query.execBatch();

    SDB->database.commit();

    emit emitInsertEntriesSucceed();
    QMessageBox::information(nullptr, tr("tips"), tr("insert succeed"));

    qDeleteAll(*entries);
    entries->clear();
    delete entries;
}

QString EntryModel::getNextId(){
    return Utils::getUid ();
}

bool EntryModel::checkExist(){
    QSqlQuery query(AppSqlite::instance()->database);
    if(id != ENTRY_ID_NULL){
        query.prepare("select * from entry where id = :id");
        query.bindValue(":id", id);
        query.exec();
        auto model = new QSqlQueryModel();
        model->setQuery(query);
        int rowCount = model->rowCount();
        return rowCount == 1;
    }
    return false;
}

void EntryModel::setHtml(QString html){
    this->html = html;
    if(id==ENTRY_ID_NULL){
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
    if(id== ENTRY_ID_NULL){
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
    if(id==ENTRY_ID_NULL){
        return;
    }
    QSqlQuery query;
    query.prepare(("update entry set mkdown = :mkdown where id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":mkdown", mkdown);
    query.exec();
}

void EntryModel::setLastViewDate(){
    this->lastViewDate = QDateTime::currentDateTime().toString();
    if(id==ENTRY_ID_NULL){
        return;
    }
    QSqlQuery query;
    query.prepare(("update entry set lastViewDate = :lastViewDate where id = :id"));
    query.bindValue(":id", id);
    query.bindValue(":lastViewDate", this->lastViewDate);
    query.exec();
}

QList<QMap<QString, QString>>* EntryModel::loadNames(QString searchText, bool isAllTextSearch)
{
    auto list = new QList<QMap<QString, QString>>();

    if (SDB == nullptr)
        return list;

    QString sql = "select entry, id from entry ";
    if (searchText.trimmed() != "") {
        QString search = "'%" + searchText.trimmed() + "%'";
        if (isAllTextSearch) {
            sql = sql.append("where entry like " + search).append(" or text like" + search);
        } else {
            sql = sql.append("where entry like " + search);
        }
    }
    QSqlQuery query;    
    query.exec(sql);
    while (query.next()) {
        QMap<QString, QString> map;
        auto entry = query.value("entry").toString();
        auto id = query.value("id").toString();
        map.insert(id, entry);
        list->append(map);
    }
    return list;
}

//TODO
QList<QString>* EntryModel::loadAchors(){
    auto list = new QList<QString>();


    if (SDB == nullptr) {
        return list;
    }
    auto all = loadAll ();

    QRegExp matchLink("<a.*</a>");
    matchLink.setMinimal (true);
    QRegExp matchName("name=\"(.*)\"");
    matchName.setMinimal (true);

    for(auto entry : *all){
        QString text = entry->html;

        int linkPos = 0;
        while((linkPos = matchLink.indexIn (text, linkPos)) != -1){
            linkPos += matchLink.matchedLength();
            QString link = matchLink.cap (0);
            int namePos = matchName.indexIn (link);
            if(namePos != -1){
                textDocument->setHtml (matchName.cap (1));
                QString name = textDocument->toPlainText ();
                if(name == "#000507" || name == "#096481"){ //不知道是啥，但是出现了
                    continue;
                }
                list->append ("entry://" + entry->entry + "#" + name);
            }
        }
    }
    return list;
}

QList<QMap<QString, QString>> *EntryModel::loadAchors(QString id)
{
    auto list = new QList<QMap<QString, QString>>();

    if (SDB == nullptr) {
        return list;
    }

    EntryModel model;
    model.id = id;
    model.load();

    QRegExp matchLink("<a.*</a>");
    matchLink.setMinimal(true);
    QRegExp matchName("name=\"(.*)\"");
    QRegExp matchValue(">(.*)<");
    matchValue.setMinimal(true);
    matchName.setMinimal(true);

    QString text = model.html;
    int linkPos = 0;
    while ((linkPos = matchLink.indexIn(text, linkPos)) != -1) {
        QString name{""}, value{""};

        linkPos += matchLink.matchedLength();
        QString link = matchLink.cap(0);

        if (matchName.indexIn(link) != -1) {
            QMap<QString, QString> map;
            //name

            name = matchName.cap(1);
            if (name == "#000507" || name == "#096481") { //不知道是啥，但是出现了
                continue;
            }

            //value
            if (matchValue.indexIn(link) != -1) {
                value = matchValue.cap(1);
            }
            map.insert(name, value);
            list->append(map);
        }
    }
    return list;
}

void EntryModel::setLastUpdateDate(){
    this->lastUpdateDate = QDateTime::currentDateTime().toString();
    if(id==ENTRY_ID_NULL){
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
    query.exec("select count(*) from entry");
    while (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

int EntryModel::getShowCount (){
    QSqlQuery query(AppSqlite::instance()->database);
    query.exec("select count(*) from entry where visiable = 'yes'");
    while (query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}

int EntryModel::getHideCount (){
    QSqlQuery query(AppSqlite::instance()->database);
    query.exec("select count(*) from entry where visiable = 'no'");
    while (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

void EntryModel::setVisiable (bool visiable){
    this->isVisiable = visiable;
    this->isVisiable = visiable;
    QString sql = "UPDATE [entry] SET [visiable] = :visiable WHERE  [id] = :id";
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
    query.bindValue (":sortId", sortId);
    query.exec ();
}

void EntryModel::setTag(QString tagId){
    this->tagId = tagId;
    QSqlQuery query;
    query.prepare ("update entry set tagId = :tagId where id = :id");
    query.bindValue (":id", id);
    query.bindValue (":tagId", tagId);
    query.exec ();
}

int EntryModel::getNextSortId (){
    QSqlQuery query;
    query.exec("select * from entry");
    auto model = new QSqlQueryModel();
    model->setQuery(query);
    int rowCount = model->rowCount();
    if(rowCount == 0){
        delete model;
        return 1;
    }

    query.exec("select max(sortId) from entry");
    while(query.next()){
        return query.value(0).toInt() + 1;
    }
    return 1;
}

//当 list 为空时，执行 拷贝到this, 否则，执行 复制到 list 中。
QList<EntryModel *> *EntryModel::queryToEntry(QSqlQuery &query, QList<EntryModel *> *list)
{
    while (query.next()) {
        EntryModel *model = list == nullptr ? this : new EntryModel();
        model->id = query.value("id").toString();
        model->sortId = query.value("sortId").toInt();
        model->tagId = query.value("tagId").toString();
        model->text = query.value("text").toString();
        model->mkdown = query.value("mkdown").toString();
        model->entry = query.value("entry").toString();
        model->html = query.value("html").toString();
        model->createDate = query.value("createDate").toString();
        model->isVisiable = query.value("visiable").toString() == "yes" ? true : false;
        model->lastViewDate = query.value("lastViewDate").toString();
        model->lastUpdateDate = query.value("lastUpdateDate").toString();
        if (list != nullptr) {
            list->append(model);
        }
    }
    return list;
}

void EntryModel::bindParameter(QSqlQuery &query, EntryModel *model)
{
    if (model == nullptr) {
        model = this;
    }
    query.bindValue (":id", model->id);
    query.bindValue (":sortId", model->sortId);
    query.bindValue (":tagId", model->tagId);
    query.bindValue (":entry", model->entry);
    query.bindValue (":text", model->text);
    query.bindValue (":mkdown", model->mkdown);
    query.bindValue (":html", model->html);
    query.bindValue (":visiable", model->isVisiable ?"yes":"no");
    query.bindValue (":createDate", model->createDate);
    query.bindValue (":lastUpdateDate", model->lastUpdateDate);
    query.bindValue (":lastViewDate", model->lastViewDate);
}

EntryModel *EntryModel::copy()
{
    EntryModel *model = new EntryModel();
    model->id = id;
    model->sortId = sortId;
    model->tagId = tagId;
    model->entry = entry;
    model->text = text;
    model->html = html;
    model->mkdown = mkdown;
    model->isVisiable = isVisiable;
    model->createDate = createDate;
    model->lastViewDate = lastViewDate;
    model->lastUpdateDate = lastUpdateDate;
    return model;
}

EntryModel::~EntryModel(){
    delete textDocument;
}
