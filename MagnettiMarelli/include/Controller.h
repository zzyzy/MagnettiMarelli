#pragma once

#include <SQLiteCpp\SQLiteCpp.h>
#include <string>

class Controller
{
protected:
	Controller() = default;
	~Controller() = default;

	static const std::string path;
	static const int flags;
	static SQLite::Database db;
};