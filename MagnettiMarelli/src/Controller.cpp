#include <Controller.h>

const std::string Controller::path = "database/MMDatabase.db";
const int Controller::flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
SQLite::Database Controller::db(path, flags);