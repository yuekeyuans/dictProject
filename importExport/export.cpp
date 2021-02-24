#include "export.h"
#include <QWidget>
#include <thread>
#include <QMessageBox>
#include "importExport/exporttoexcel.h"
#include "data/appsqlite.h"
#include <QFileDialog>

using namespace std;


Export::Export(QObject *parent) : QObject(parent)
{
    exportToExcel = new ExportToExcel();
    exportToPdb = new ExportToPdb();
    exportToDictHtml = new ExportToDictHtml();
    exportToHtml = new ExportToHtml();
    exportToTag = new ExportToTag();
    connect (exportToExcel, &ExportToExcel::emitComplete, this, &Export::slotShowInfo);
    connect (exportToPdb, &ExportToPdb::emitComplete, this, &Export::slotShowInfo);
    connect (exportToHtml, &ExportToHtml::emitComplete, this, &Export::slotShowInfo);
    connect (exportToDictHtml, &ExportToDictHtml::emitComplete, this, &Export::slotShowInfo);
    connect(exportToTag, &ExportToTag::emitComplete, this, &Export::slotShowInfo);
}

void Export::toHtml(){
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString dir = QFileDialog::getExistingDirectory(nullptr, tr("getDir"),desktopPath);
    if(dir == "")
        return;

    EntryModel entryModel;
    DictModel dictModel;
    exportToHtml->setEntries(entryModel.loadAll());
    exportToHtml->setDict(dictModel.loadAll());
    exportToHtml->setBaseName(SDB->dictName);
    exportToHtml->setDir(dir);
    exportToHtml->process();
}

void Export::toPdb(){

    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString dir = QFileDialog::getExistingDirectory(nullptr, tr("getDir"),desktopPath);
    if(dir == ""){
        return;
    }

    EntryModel entryModel;
    DictModel dictModel;
    exportToPdb->setEntries(entryModel.loadAll());
    exportToPdb->setDict(dictModel.loadAll());
    exportToPdb->setBaseName(SDB->dictName);
    exportToPdb->setDir(dir);
    exportToPdb->process();
}

void Export::toExcel()
{
    QString baseName = SDB->dictName;
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString fileName = QFileDialog::getSaveFileName(nullptr,
                                            tr("open"),
                                            desktopPath + "/" + baseName,
                                            tr("xlsx(*.xlsx)"));
    if (fileName == "") {
        return;
    }

    EntryModel entryModel;
    exportToExcel->setEntries(entryModel.loadAll());
    DictModel dictModel;
    exportToExcel->setDict(dictModel.loadAll());
    TagModel tag;
    exportToExcel->setTags(tag.loadAll());
    exportToExcel->setBaseName(SDB->dictName);
    exportToExcel->setFileName(fileName);
    exportToExcel->start ();
}

void Export::toDictHtml(){
    QString baseName = SDB->dictName;
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString path = QFileDialog::getSaveFileName(nullptr, tr("tips"),
                                                desktopPath + "/" + baseName + ".txt",
                                                tr("mdict html(*.txt)"));
    if(path == nullptr || path == "") return;

    EntryModel entryModel;
    auto entries = entryModel.loadAll();
    DictModel dictModel;
    auto dict = dictModel.loadAll();
    exportToDictHtml->setEntries(entries);
    exportToDictHtml->setDict(dict);
    exportToDictHtml->setBaseName(SDB->dictName);
    exportToDictHtml->setPath(path);
    exportToDictHtml->start();
}

void Export::toTag(TagModel *model)
{
    QString baseName = model->name;
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString file = QFileDialog::getSaveFileName(nullptr,tr("open"),desktopPath + "/" + baseName, tr("xlsx(*.xlsx)"));
    if(file == "")
        return;

    TagExportOptionsDialog exportToTagDialog;
    if (exportToTagDialog.exec() == QDialog::Rejected) return;

    TagModel tag;
    EntryModel entry;
    auto tags = tag.load(model->id);
    auto entries = entry.load(*tags);

    exportToTag->setTag(model);
    exportToTag->setTags(tags);
    exportToTag->setEntries(entries);
    exportToTag->setExportType(exportToTagDialog.getResult());
    exportToTag->setFilePath(file);
    exportToTag->start();
}

void Export::slotShowInfo (){
    QMessageBox::about(nullptr, tr("tip"), tr("succeed"));
}

Export::~Export(){
    delete exportToExcel;
    delete exportToPdb;
    delete exportToTag;
    delete exportToHtml;
    delete exportToDictHtml;
}
