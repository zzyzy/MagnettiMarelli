#include "stdafx.h"
#include "TestDatabase.h"

SQLite::Database TestDatabase::db(MAGNETTIDB, SQLITE_OPEN_READWRITE);
OICDAO TestDatabase::oicDao(db);
ItemDAO TestDatabase::itemDao(db);
TeamDAO TestDatabase::teamDao(db);
RequestDAO TestDatabase::requestDao(db);
OICService TestDatabase::oicService(oicDao);
ItemService TestDatabase::itemService(itemDao);
TeamService TestDatabase::teamService(teamDao);
RequestService TestDatabase::requestService(requestDao);
