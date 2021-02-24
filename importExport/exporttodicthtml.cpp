#include "exporttodicthtml.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardPaths>

ExportToDictHtml::ExportToDictHtml(QObject *parent) : QThread(parent)
{

    QRegExp ex("\"entry://(.*)\"");
    ex.setMinimal(true);
}

void ExportToDictHtml::run(){

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream out(&file);

    for(auto entry: *entries){
        out << wrapFile ((entry->entry)) <<endl;
        out << wrapFile(entry->html) << endl;
        out << "</>" <<endl;
    }
    qDeleteAll(*entries);
    entries->clear();
    delete entries;
    entries = nullptr;
    delete dict;
    dict = nullptr;
    file.close();
    emit emitComplete ();
}

void ExportToDictHtml::process(){
    this->start ();
}

QString ExportToDictHtml::wrapFile(QString content){
    ex.indexIn(content);
    content = content.replace(ex, "\"\\1.html\"");
    content = content.replace ("plugin/summernote-emoji-master/tam-emoji/img/", "./css/");
    return content;
}

void ExportToDictHtml::setDict(DictModel *dict){
    this->dict = dict;
}

void ExportToDictHtml::setEntries(QList<EntryModel *> * entries){
    this->entries = entries;
}

void ExportToDictHtml::setBaseName(QString baseName){
    this->baseName = baseName;
}

ExportToDictHtml::~ExportToDictHtml(){
}

void ExportToDictHtml::setPath(QString path)
{
    this->path = path;
}
