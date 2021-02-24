#include "exporttotag.h"
#include "data/tagmodel.h"
#include <QDebug>
#include "xlsxdocument.h"
#include <QSqlDatabase>

using namespace QXlsx;

ExportToTag::ExportToTag(QObject *parent) : QThread(parent){
}

void ExportToTag::setTag(TagModel *model)
{
    this->model = model;
}

void ExportToTag::run()
{
    if (tagOption == TagExportOptionsDialog::EXPORT_FLAT) {
        exportFlat();
    }else if (tagOption == TagExportOptionsDialog::EXPORT_ORIGNAL) {
        exportOrignal ();
    }else if (tagOption == TagExportOptionsDialog::EXPORT_TO_PARENT) {
        exportToParent ();
    }else if (tagOption == TagExportOptionsDialog::EXPORT_TO_PLUGIN) {
        exportToPlugin ();
    }

    writeTags();
    writeEntries();
    emit emitComplete();
}

void ExportToTag::writeTags()
{
    QXlsx::Document xlsxW(filePath);
    xlsxW.addSheet("tag");
    int row = 1;
    for (int i = 0; i < tags->length(); i++) {
        qDebug() << tags->at(i)->name;
        auto tag = tags->at(i);
        auto id = tag->id;
        if (id == TagModel::TAG_ID_ANCHOR || id == TagModel::TAG_ID_PLUGIN) {
            continue;
        }
        xlsxW.write(row, 1, tag->id);
        xlsxW.write(row, 2, tag->name);
        xlsxW.write(row, 3, tag->size);
        xlsxW.write(row, 4, tag->type);
        xlsxW.write(row, 5, tag->sortId);
        xlsxW.write(row, 6, tag->fold ? "yes":"no");
        xlsxW.write(row, 7, tag->locked ? "yes" :"no");
        xlsxW.write(row, 8, tag->parentId);
        row++;
    }
    qDeleteAll(*tags);
    delete tags;
    xlsxW.save();
}

void ExportToTag::writeEntries()
{
    QXlsx::Document xlsxW(filePath);
    xlsxW.addSheet("entries");
    for (int i = 0; i < entries->size(); i++) {
        xlsxW.write(i + 1, 1, entries->at(i)->entry);
        xlsxW.write(i + 1, 2, entries->at(i)->text);
        xlsxW.write(i + 1, 3, entries->at(i)->html);
        xlsxW.write(i + 1, 4, entries->at(i)->mkdown);
        xlsxW.write(i + 1, 5, entries->at(i)->sortId);
        xlsxW.write(i + 1, 6, entries->at(i)->isVisiable ? "yes" : "no");
        xlsxW.write(i + 1, 7, entries->at(i)->lastViewDate);
        xlsxW.write(i + 1, 8, entries->at(i)->lastUpdateDate);
        xlsxW.write(i + 1, 9, entries->at(i)->createDate);
        xlsxW.write(i + 1, 10, entries->at(i)->tagId);
    }
    xlsxW.save();

    qDeleteAll(*entries);
    delete entries;
}

void ExportToTag::setExportType(TagExportOptionsDialog::TagVal val)
{
    this->tagOption = val;
}

void ExportToTag::setFilePath(QString filePath)
{
    this->filePath = filePath;
}

void ExportToTag::setTags(QList<TagModel *> *tags)
{
    this->tags = tags;
}

void ExportToTag::setEntries(QList<EntryModel *> *entries)
{
    this->entries = entries;
}

void ExportToTag::exportToPlugin()
{
    tags->first()->parentId = TagModel::TAG_ID_PLUGIN;
}


void ExportToTag::exportToParent()
{
    tags->first()->parentId = TagModel::TAG_ID_PARENT;
}

void ExportToTag::exportFlat()
{
    qDeleteAll(*tags);
    tags->clear();
    for (auto entry : *entries) {
        entry->tagId = TagModel::TAG_ID_PARENT;
    }
}

void ExportToTag::exportOrignal() {
    TagModel tag;
    auto firstTag = tags->first();
    while (firstTag->parentId != TagModel::TAG_ID_PARENT) {
        tag.id = firstTag->parentId;
        tag.load();
        tags->prepend(tag.copy ());
    }
}

ExportToTag::~ExportToTag()
{
}
