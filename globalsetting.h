#ifndef SQLITESOURCE_H
#define SQLITESOURCE_H

#include <QCoreApplication>

#define SQL_CREATE_DICT_TABLE QString("create table if not exists [dict] ( \
  [id] INTEGER NOT NULL, \
  [title] TEXT NOT NULL, \
  [description] TEXT, \
  [image] BLOB,\
  [html] BLOB,\
  Primary Key(id))")

#define SQL_CREATE_ENTRY_TABLE QString("CREATE TABLE IF NOT EXISTS [entry]( \
  [id] TEXT PRIMARY KEY NOT NULL UNIQUE, \
  [sortId] INT NOT NULL, \
  [tagId] TEXT NOT NULL, \
  [entry] text NOT NULL,  \
  [text] blob,  \
  [mkdown] blob, \
  [html] blob, \
  [visiable] TEXT, \
  [createdate] char(8), \
  [lastUpdateDate] char(8),  \
  [lastViewDate] char(8))")

#define SQL_CREATE_TAG_TABLE QString("CREATE TABLE IF NOT EXISTS [tag] \
([id] TEXT PRIMARY KEY NOT NULL,  \
  [sortId] INT NOT NULL, \
  [name] TEXT NOT NULL, [size] INT NOT NULL,  \
  [type] TEXT, \
  [parentId] TEXT NOT NULL, \
  [fold] TEXT NOT NULL, \
  [locked] TEXT NOT NULL \
 );")

#define SQL_INIT_DICT_TABLE QString("INSERT INTO [dict] \
  ([id],[title],[description],[image],[html]) \
  VALUES (1,:title,'','','')")

// TODO: 这个地方使用 汉字会产生错误。
#define SQL_INIT_TAG_TABLE_ANCHOR QString("insert into tag \
(id, sortId, name,size,type, parentId,fold,locked) \
values('anchor_1', 1, 'anchor list', 0, 'USER', '0', 'no', 'no')")

#define SQL_INIT_TAG_TABLE_PLUGIN QString("insert into tag \
(id, sortId, name,size,type, parentId,fold,locked) \
values('plugin_2', 2, 'plugin', 0, 'USER', '0', 'no', 'no')")

// 更新tag 数量
#define SQL_INIT_TAG_COUNT QString("update tag set size = \
(select count(1) from entry where entry.tagId = tag.id) +  \
(select count(1) from tag as t where t.parentId = tag.id)")

//#if COMPILE_IN_CODING
    #define COPY_PATH QString("G:/qtproject/dictProject-v5/source/")
    #define SUMMERNOTE_PATH QString("G:/qtproject/dictProject-v5/summernote/index.html")
//#else
//    #define COPY_PATH QString("source/")
//    #define SUMMERNOTE_PATH QString("summernote/index.html")
//#endif

#endif // SQLITESOURCE_H
