#include "exporttohtml.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

ExportToHtml::ExportToHtml(QObject *parent) : QObject(parent)
{
}

void ExportToHtml::process(){
    QString dir = QFileDialog::getExistingDirectory(nullptr, tr("getDir"),"./");
    QDir destDir(dir);

    //copy static file
    QFile::copy(":/res/exportHtml/jquery.jsx", destDir.filePath("jquery.js"));
    QFile::copy(":/res/exportHtml/index.html", destDir.filePath("index.html"));
    QString listPath = destDir.filePath(":/res/other/file_to_copy.txt");
    QFile file(listPath);
    destDir.mkdir("emoji");
    if(file.open(QIODevice::ReadOnly| QIODevice::Text)){
        while (!file.atEnd()){
            QString line = file.readLine().trimmed();
            QFile::copy(":/simditor/" + line, destDir.filePath(line));
        }
        file.close();
    }

    //导出dict
    QString dict_title = readFile(":/res/exportHtml/frame_dict_title.html").replace(":title_to_be_replace", dict->title);
    writeFile(destDir.filePath("frame_dict_title.html"), dict_title);
    QString dict_content = readFile(":/res/exportHtml/frame_dict_content.html").replace(":dict_content", dict->html);
    writeFile(destDir.filePath("frame_dict_content.html"), dict_content);

    //导出 item 页面
    QString entries_list = "";
    QString entry_content = readFile(":/res/exportHtml/entry_content.html");
    for(auto entry:*entries){
        entries_list += ("\"" + entry->entry + "\",");
        QString temp = entry_content;
        writeFile(destDir.filePath(entry->entry + ".html"),  temp.replace(":content_to_be_load", entry->html));
    }
    QString entry_menu = readFile(":/res/exportHtml/entry_list.html").replace("\":entry_to_load\"", entries_list);
    writeFile(destDir.filePath("entry_list.html"), entry_menu);

    //clear;
    for(auto entry:*entries){
        delete entry;
    }
    delete entries;
    delete dict;
    QMessageBox::about(nullptr, tr("tip"), tr("success"));

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
        content.replace(ex, "\"\\1.html\"");
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
