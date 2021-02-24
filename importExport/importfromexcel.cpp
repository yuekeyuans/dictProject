#include "importfromexcel.h"

ImportFromExcel::ImportFromExcel(QObject *parent) : QThread(parent)
{
    entryModel = new EntryModel(parent);
    connect(this, &ImportFromExcel::emitInsertEntries, entryModel, &EntryModel::slotinsertEntries);
    connect(entryModel, &EntryModel::emitInsertEntriesSucceed, this, &ImportFromExcel::emitSuccess);

    dictModel = new DictModel(parent);
    connect(this, &ImportFromExcel::emitInsertDict, dictModel, &DictModel::update);

    tagModel = new TagModel(parent);
    connect(this, &ImportFromExcel::emitInsertTags, tagModel, &TagModel::slotInsertTags);
    connect(tagModel, &TagModel::emitInsertTagsSucceed, this, &ImportFromExcel::emitSuccess);
}

void ImportFromExcel::run(){
    importExcel ();
}

//当前 import 有两个版本, 第一个就是之前所写的软件， 第二个则是现在需要处理的。
void ImportFromExcel::importExcel(){
    xlsR = new Document(filePath);
    auto success = xlsR->load();
    if (!success) {
        emit emitFail();
        return;
    }

    int sheetCount = xlsR->sheetNames ().length ();
    if(sheetCount == 1){ //规定，其他的表必须导出至少两份内容
        processVersion1 ();
    }else{
        processVersion2 ();
    }
    delete xlsR;
    xlsR = nullptr;
}

void ImportFromExcel::processVersion1(){
    auto list = new QList<EntryModel*>;

    for(int r=1;;r++){
        auto cell = xlsR->cellAt(r, 1);
        if (cell == nullptr) {
            break;
        }
        auto model = new EntryModel;
        model->entry =cell->readValue().toString();
        model->text = xlsR->cellAt(r, 2)->readValue().toString();
        model->html = xlsR->cellAt(r, 3)->readValue().toString();
        if(model->html.startsWith ("<!DOCTYPE")){
            model->html = processHtml (model->html);
        }
        list->append(model);
    }
    emit emitInsertEntries(list);
}

void ImportFromExcel::processVersion2(){
    auto entries = new QList<EntryModel *>;
    auto tags = new QList<TagModel *>;
    auto dict = new DictModel;

    QList<QString> sheets = xlsR->sheetNames();

    if(sheets.contains ("tag")){
        xlsR->selectSheet("tag");
        for (int r = 1;; r++) {
            auto tag = new TagModel;
            auto cell = xlsR->cellAt(r, 1);
            if (cell == nullptr) {
                break;
            }
            tag->id = xlsR->cellAt(r, 1)->readValue().toString();
            tag->name = xlsR->cellAt(r, 2)->readValue().toString();
            tag->size = xlsR->cellAt(r, 3)->readValue().toInt();
            tag->type = xlsR->cellAt(r, 4)->readValue().toString();
            tag->sortId = xlsR->cellAt(r, 5)->readValue().toInt();
            tag->fold = xlsR->cellAt(r, 6)->readValue().toString() == "yes" ? true : false;
            tag->locked = xlsR->cellAt(r, 7)->readValue().toString() == "yes" ? true : false;
            tag->parentId = xlsR->cellAt(r, 8)->readValue().toString();
            tags->append(tag);
        }
        emit emitInsertTags(tags);
    }

    if(sheets.contains ("dict")){
        xlsR->selectSheet ("dict");
        dictModel->html = xlsR->cellAt(1, 4)->readValue().toString();
        emit emitInsertDict();
    }


    if (sheets.contains("entries")) {
        xlsR->selectSheet("entries");
        for (int r = 1;; r++) {
            auto cell = xlsR->cellAt(r, 1);
            if (cell == nullptr) {
                break;
            }
            auto model = new EntryModel;
            model->entry = xlsR->cellAt(r, 1)->readValue().toString();
            model->text = xlsR->cellAt(r, 2)->readValue().toString();
            model->html = xlsR->cellAt(r, 3)->readValue().toString();
            model->mkdown = xlsR->cellAt(r, 4)->readValue().toString();
            model->sortId = xlsR->cellAt(r, 5)->readValue().toInt();
            model->isVisiable = xlsR->cellAt(r, 6)->readValue().toBool();
            model->lastViewDate = xlsR->cellAt(r, 7)->readValue().toString();
            model->lastUpdateDate = xlsR->cellAt(r, 8)->readValue().toString();
            model->createDate = xlsR->cellAt(r, 9)->readValue().toString();
            model->tagId = xlsR->cellAt(r, 10)->readValue().toString();
            entries->append(model);
        }
        emit emitInsertEntries(entries);
    }
}

void ImportFromExcel::setFilePath(QString filePath)
{
    this->filePath = filePath;
}

QString ImportFromExcel::processHtml(QString html){
    QList<QString> lines = html.split ("\n");
    QString result = "";
    lines[lines.length ()-1] = lines[lines.length ()-1].replace ("</body></html>", "");
    for(int i=4;i<lines.length ();i++){
        result += lines.at (i);
    }
    return result;
}


ImportFromExcel::~ImportFromExcel()
{
    delete entryModel;
    delete tagModel;
    delete dictModel;
}
