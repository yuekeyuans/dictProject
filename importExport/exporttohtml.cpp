#include "exporttohtml.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QStandardPaths>
#include "data/setting.h"

ExportToHtml::ExportToHtml(QObject *parent) : QThread(parent)
{
    Setting setting;
    basePath = setting.getData ("exePath")+ COPY_PATH;

    dict_title = readFile(basePath + "html/frame_dict_title.html");
    dict_content = readFile(basePath + "html/frame_dict_content.html");
    entry_menu = readFile(basePath + "html/entry_list.html");
    entries_list = "";
}

void ExportToHtml::run(){
    QDir destDir(dir);
    {   // copy nessary file
        QDir sourceDir{basePath + "html/css/"};
        destDir.mkdir("css");

        QFileInfoList file_list = sourceDir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

        for(int i = 0; i != file_list.size(); i++)
        {
            QString srcPath = file_list.at(i).absoluteFilePath();
            QString destPath = destDir.path () + "/css/" + file_list.at (i).fileName ();
            QFile::copy(srcPath, destPath);
        }

        QFile::copy(basePath + "html/index.html", destDir.path () + "/index.html");
    }

    //导出dict
    writeFile(destDir.filePath("frame_dict_title.html"),
              dict_title.replace(":content_to_be_load", dict->title));
    writeFile(destDir.filePath("frame_dict_content.html"),
              dict_content.replace(":content_to_be_load", dict->html));

    //导出 item 页面
    QString entry_content = readFile(basePath + "html/entry_content.html");
    for(auto entry:*entries){
        QString content = entry_content;
        entries_list += ("\"" + entry->entry + "\",");
        writeFile(destDir.filePath(entry->entry + ".html"),
                  content.replace(":content_to_be_load", entry->html));
    }

    writeFile(destDir.filePath("entry_list.html"),
              entry_menu.replace(":content_to_be_load", entries_list));

    qDeleteAll(*entries);
    entries->clear();
    delete entries;
    entries = nullptr;
    delete dict;
    dict = nullptr;
    emit emitComplete ();
}

void ExportToHtml::process(){
    this->start();
}

void ExportToHtml::setDict(DictModel *dict){
    this->dict = dict;
}

void ExportToHtml::setEntries(QList<EntryModel *> *entries){
    this->entries = entries;
}

void ExportToHtml::setBaseName(QString baseName){
    this->baseName = baseName;
}

void ExportToHtml::writeFile(QString path, QString content){
    QFile file(path);
    if (file.open(QFile::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8");
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

QString ExportToHtml::readFile(QString path){
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream s(&file);
    QString result = s.readAll();
    file.close();
    return result;
}

void ExportToHtml::setDir(QString dir)
{
    this->dir = dir;
}
