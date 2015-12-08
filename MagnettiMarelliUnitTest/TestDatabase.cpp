#include "stdafx.h"
#include "TestDatabase.h"

#ifdef _DEBUG
SQLite::Database TestDatabase::db(MAGNETTIDB, SQLITE_OPEN_READWRITE);
#else
SQLite::Database TestDatabase::db("MagnettiMarelli.db", SQLITE_OPEN_READWRITE);
#endif

OICDAO TestDatabase::oicDao(db);
ItemDAO TestDatabase::itemDao(db);
TeamDAO TestDatabase::teamDao(db);
RequestDAO TestDatabase::requestDao(db);
OICService TestDatabase::oicService(oicDao);
ItemService TestDatabase::itemService(itemDao);
TeamService TestDatabase::teamService(teamDao);
RequestService TestDatabase::requestService(requestDao);
