#include "setting.h"
#include <QtCore>
#include <QMap>
#include <QSettings>
#include <json.h>

using namespace QtJson;

Setting::Setting(QObject *parent) : QObject(parent){
    dicts = QList<QMap<QString, QString>>();
    loadDict();
}

bool Setting::checkDictExist(const QString &path){
    QFile file(path);
    return file.exists();
}

bool Setting::addDict(QString name, QString path){
    //check
    QMap<QString, QString> i_map;
    foreach (i_map, dicts) {
        if(i_map.values().contains(name)) {
            return false;
        }
    }
    if(!checkDictExist(path)){
        return false;
    }

    QMap<QString, QString> map;
    map.insert("name", name);
    map.insert("path", path);
    dicts.append(map);
    saveDict();
    return true;
}

void Setting::saveDict(){
    QSettings setting;
    JsonArray array;

    QMap<QString, QString> i_map;
    foreach(i_map, dicts){
        JsonObject obj;
        obj.insert("name", i_map.value("name"));
        obj.insert("path", i_map.value("path"));
        array.append(obj);
    }
    setting.setValue("menu/dict", QtJson::serializeStr(array));
}

bool Setting::loadDict(){
    bool ok;
    QSettings setting;
    if(!setting.contains("menu/dict"))
        return false;

    JsonArray array = QtJson::parse(setting.value("menu/dict").toString(), ok).toList();
    if(!ok)
        return false;
    JsonObject obj;
    for(const auto &i:array){
        QMap<QString, QString> map;
        obj = i.toMap();
        if(!QFile(obj.value("path").toString()).exists()){
            continue;
        }
        map.insert("name", obj.value("name").toString());
        map.insert("path", obj.value("path").toString());
        dicts.append(map);
    }
    saveDict();
    return true;
}

void Setting::delectDict(QString name){
    QMap<QString, QString> i_map;
    foreach(i_map, dicts){
        if(i_map.value("name") == name){
            dicts.removeOne(i_map);
            return;
        }
    }
}

QString Setting::getName(QString path){
    QMap<QString, QString> i_map;
    foreach(i_map, dicts){
        if(i_map.value("path") == path){
            return i_map.value("name");
        }
    }
    return "";
}

QString Setting::getPath(QString name){
    QMap<QString, QString> i_map;
    foreach(i_map, dicts){
        if(i_map.value("name") == name){
            return i_map.value("path");
        }
    }
    return "";
}


QList<QMap<QString, QString>> Setting::getSubMenu(){
    return this->dicts;
}
