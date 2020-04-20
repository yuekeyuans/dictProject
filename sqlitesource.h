#ifndef SQLITESOURCE_H
#define SQLITESOURCE_H

#define SQL_CREATE_DICT_TABLE QString("create table if not exists dict( [id] INTEGER NOT NULL, [title] TEXT NOT NULL,[description] TEXT,[image] BLOB,[html] BLOB, Primary Key(id))")

#define SQL_CREATE_ENTRY_TABLE QString("CREATE TABLE IF NOT EXISTS [entry]( [id] integer PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, [entry] text NOT NULL UNIQUE, [text] blob, [mkdown] blob, [html] blob, [createdate] char(8), [lastUpdateDate] char(8), [lastViewDate] char(8))")

#endif // SQLITESOURCE_H
