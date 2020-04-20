#include "export.h"
#include <QWidget>
#include <thread>
#include <QMessageBox>
#include "importExport/exporttoexcel.h"
#include "data/appsqlite.h"

using namespace std;


Export::Export(QObject *parent) : QObject(parent)
{
    exportToExcel = new ExportToExcel(this);
    exportToPdb = new ExportToPdb(this);
    exportToDictHtml = new ExportToDictHtml(this);
    exportToHtml = new ExportToHtml(this);
}

void Export::toHtml(){
    EntryModel entryModel;
    auto entries = entryModel.loadAll();
    DictModel dictModel;
    auto dict = dictModel.loadAll();
    exportToHtml->setEntries(entries);
    exportToHtml->setDict(dict);
    exportToHtml->setBaseName(SDB->dictName);
    exportToHtml->process();
}

void Export::toPdb(){
    EntryModel entryModel;
    auto entries = entryModel.loadAll();
    DictModel dictModel;
    auto dict = dictModel.loadAll();
    exportToPdb->setEntries(entries);
    exportToPdb->setDict(dict);
    exportToPdb->setBaseName(SDB->dictName);
    exportToPdb->process();
}

void Export::toExcel(){
    EntryModel entryModel;
    auto entries = entryModel.loadAll();
    DictModel dictModel;
    auto dict = dictModel.loadAll();
    exportToExcel->setEntries(entries);
    exportToExcel->setDict(dict);
    exportToExcel->setBaseName(SDB->dictName);
    exportToExcel->process();
}

void Export::toDictHtml(){
    EntryModel entryModel;
    auto entries = entryModel.loadAll();
    DictModel dictModel;
    auto dict = dictModel.loadAll();
    exportToDictHtml->setEntries(entries);
    exportToDictHtml->setDict(dict);
    exportToDictHtml->setBaseName(SDB->dictName);
    exportToDictHtml->start();
}

Export::~Export(){
    delete exportToExcel;
    delete exportToPdb;
}
