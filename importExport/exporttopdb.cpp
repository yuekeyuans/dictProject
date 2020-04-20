#include "exporttopdb.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include "data/dictmodel.h"
#include "data/entrymodel.h"
#include <QMessageBox>

ExportToPdb::ExportToPdb(QObject *parent) : QThread(parent)
{
    //主页
    QFile index(":/res/html/index.html");
    if(index.open(QIODevice::ReadOnly | QIODevice::Text)){
         index_page = QString::fromStdString(index.readAll().toStdString());
         index.close();
    }
    //目录页
    QFile indexList(":/res/html/index_list.html");
    if(indexList.open(QIODevice::ReadOnly | QIODevice::Text)){
         index_list_page = QString::fromStdString(indexList.readAll().toStdString());
         indexList.close();
    }
    //项目页
    QFile item(":/res/html/item.html");
    if(item.open(QIODevice::ReadOnly | QIODevice::Text)){
         item_page = QString::fromStdString(item.readAll().toStdString());
         item.close();
    }
    //需要拷贝的文件
}

void ExportToPdb::process(){
    QString dir = QFileDialog::getExistingDirectory(nullptr, tr("getDir"),"./");
    QDir destDir(dir);
    {// copy nessary file
        QFile::copy(":/res/exportHtml/jquery.jsx", destDir.filePath("jquery.js"));
        QString listPath = destDir.filePath(":/res/other/file_to_copy.txt");
        QFile file(listPath);
        destDir.mkdir("emoji");
        if(file.open(QIODevice::ReadOnly| QIODevice::Text)){
            while (!file.atEnd()){
                QString line = file.readLine().trimmed();
                QString srcPath = ":/simditor/" + line;
                QString destPath = destDir.filePath(line);
                QFile::copy(srcPath, destPath);
            }
            file.close();
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
    for(auto entry:*entries){
        delete entry;
    }
    delete entries;
    delete dict;
    QMessageBox::about(nullptr, tr("tip"), tr("success"));
}

void ExportToPdb::writeFile(QString path, QString content){
    QFile file(path);
    if (file.open(QFile::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("GBK");
        QRegExp ex("\"entry://(.*)\"");
        ex.setMinimal(true);
        ex.indexIn(content);
        content.replace(ex, "\"\\1.html\"");
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

ExportToPdb::~ExportToPdb(){

}
