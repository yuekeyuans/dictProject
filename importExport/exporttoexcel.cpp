#include "exporttoexcel.h"
#include <thread>
#include <QMessageBox>
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "data/entrymodel.h"
#include "data/dictmodel.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QStandardPaths>
#include "data/appsqlite.h"

using namespace QXlsx;

ExportToExcel::ExportToExcel(QObject *parent) : QThread(parent)
{

}

void ExportToExcel::run()
{
    writeDict(dict);
    writeTag(tags);
    writeEntry(entries);
    emit emitComplete();
}

bool ExportToExcel::writeTag(QList<TagModel *> *tags)
{
    QXlsx::Document xlsxW(fileName);
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
    return xlsxW.save();
}

bool ExportToExcel::writeDict(DictModel *dict)
{
    QXlsx::Document xlsxW(fileName);
    xlsxW.addSheet("dict");
    xlsxW.write(1, 1, dict->id);
    xlsxW.write(1, 2, dict->title);
    xlsxW.write(1, 3, dict->description);
    xlsxW.write(1, 4, dict->html);
    delete dict;
    dict = nullptr;
    return xlsxW.save();
}

bool ExportToExcel::writeEntry(QList<EntryModel *> *entries)
{
    QXlsx::Document xlsxW(fileName);
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

    qDeleteAll(*entries);
    entries->clear();
    delete entries;
    entries = nullptr;
    return xlsxW.save();
}

void ExportToExcel::setEntries(QList<EntryModel *> *entries)
{
    this->entries = entries;
}

void ExportToExcel::setDict(DictModel *dict)
{
    this->dict = dict;
}

void ExportToExcel::setTags(QList<TagModel *> *tags)
{
    this->tags = tags;
}

void ExportToExcel::setFileName(QString fileName)
{
    this->fileName = fileName;
}

void ExportToExcel::setBaseName(QString baseName)
{
    this->baseName = baseName;
}
