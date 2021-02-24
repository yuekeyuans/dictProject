#include "exporttopdb.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "data/dictmodel.h"
#include "data/entrymodel.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QDebug>
#include "globalsetting.h"
#include "data/setting.h"

ExportToPdb::ExportToPdb(QObject *parent) : QThread(parent) {

    Setting setting;
    basePath = setting.getData ("exePath") + COPY_PATH;
    qDebug() << basePath;

    //主页
    QFile index(basePath + "pdb/index.html");
    if(index.open(QIODevice::ReadOnly | QIODevice::Text)){
         index_page = QString::fromStdString(index.readAll().toStdString());
         index.close();
    }
    //目录页
    QFile indexList(basePath + "pdb/index_list.html");
    if(indexList.open(QIODevice::ReadOnly | QIODevice::Text)){
         index_list_page = QString::fromStdString(indexList.readAll().toStdString());
         indexList.close();
    }
    //项目页
    QFile item(basePath + "pdb/template.html");
    if(item.open(QIODevice::ReadOnly | QIODevice::Text)){
         item_page = QString::fromStdString(item.readAll().toStdString());
         item.close();
    }
}

void ExportToPdb::run(){
    QDir destDir(dir);
    {   // copy nessary file
        QDir sourceDir{basePath+"pdb/css/"};
        destDir.mkdir("css");

        QFileInfoList file_list = sourceDir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

        for(int i = 0; i != file_list.size(); i++)
        {
            QString srcPath = file_list.at(i).absoluteFilePath();
            QString destPath = destDir.path () + "/css/" + file_list.at (i).fileName ();
            QFile::copy(srcPath, destPath);
        }
    }
    { //generate dict
        QString path = destDir.filePath("index.html");
        QString temp = index_page;
        temp.replace(":title", dict->title);
        temp.replace(":content_to_be_load", dict->html);
        writeFile(path, temp);
    }
    { //generate dict_list
        QString path = destDir.filePath("index_list.html");
        QString temp = index_list_page;
        temp.replace(":title", dict->title);

        QString entries_list = "";
        for(auto entry: *entries){
            entries_list += ("<li><a href=\"" + entry->entry + ".html\">"+ entry->entry+ "</a></li>");
        }
        temp.replace(":content_to_be_load", entries_list);
        writeFile(path, temp);
    }
    for(auto entry: *entries){  //generate entries
        QString path = destDir.filePath(entry->entry + ".html");
        QString temp = item_page;
        temp.replace(":title", entry->entry);
        temp.replace(":content_to_be_load", entry->html);
        writeFile(path, temp);
    }
    qDeleteAll(*entries);
    entries->clear();
    delete entries;
    entries = nullptr;
    delete dict;
    dict = nullptr;
    emit emitComplete ();
}


void ExportToPdb::process(){
    this->start ();
}

void ExportToPdb::writeFile(QString path, QString content){
    QFile file(path);
    if (file.open(QFile::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("GBK");
        QRegExp ex("\"entry://(.*)\"");
        ex.setMinimal(true);
        ex.indexIn(content);
        content = content.replace(ex, "\"\\1.html\"");
        content = content.replace ("plugin/summernote-emoji-master/tam-emoji/img/", "./css/");

        out << content;
        out.flush();
        file.close();
    }
}

void ExportToPdb::setDict(DictModel *dict){
    this->dict = dict;
}

void ExportToPdb::setEntries(QList<EntryModel *> * entries){
    this->entries = entries;
}

void ExportToPdb::setBaseName(QString baseName){
    this->baseName = baseName;
}

void ExportToPdb::setDir(QString dir)
{
    this->dir = dir;
}

ExportToPdb::~ExportToPdb(){

}
