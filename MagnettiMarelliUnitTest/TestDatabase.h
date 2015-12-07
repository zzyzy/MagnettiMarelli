#pragma once

#include <SQLiteCpp/SQLiteCpp.h>
#include <OICService.h>
#include <ItemService.h>
#include <TeamService.h>
#include <RequestService.h>

class TestDatabase
{
public:
	static SQLite::Database db;
	static OICDAO oicDao;
	static ItemDAO itemDao;
	static TeamDAO teamDao;
	static RequestDAO requestDao;
	static OICService oicService;
	static ItemService itemService;
	static TeamService teamService;
	static RequestService requestService;
};
