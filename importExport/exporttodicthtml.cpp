#include "exporttodicthtml.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

ExportToDictHtml::ExportToDictHtml(QObject *parent) : QThread(parent)
{

}

void ExportToDictHtml::run(){
    this->process();
    emit exportComplete();
}

void ExportToDictHtml::process(){
    QString path = QFileDialog::getSaveFileName(nullptr, tr("tips"), "./" + baseName + ".txt", tr("mdict html(*.txt)"));
    if(path == nullptr || path == "") return;
    file = new QFile(path);
    file->open(QIODevice::WriteOnly | QIODevice::Text);

    for(auto entry: *entries){
        writeFile(entry->entry);
        writeFile(entry->html);
        writeFile("</>");
    }
    for(auto entry : *entries){
        delete entry;
    }
    delete entries;
    delete dict;
    file->close();
    QMessageBox::about(nullptr, tr("tips"), tr("export succedd"));
}

void ExportToDictHtml::writeFile(QString content){
    QTextStream out(file);
    QRegExp ex("\"entry://(.*)\"");
    ex.setMinimal(true);
    ex.indexIn(content);
    content.replace(ex, "\"\\1.html\"");
    out << content <<endl;
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
