#pragma once

#include <DAO.h>
#include <Team.h>

class TeamDAO : public DAO<std::string, Team>
{
public:
	TeamDAO() = delete;
	~TeamDAO() = default;
	TeamDAO(SQLite::Database &db) : DAO(db) {  };

	void loadTable() override;

private:
	void updateRow(const Team &team) const override { throw std::runtime_error("Not yet implemented"); };
	void addRow(const Team &team) const override { throw std::runtime_error("Not yet implemented"); };
	void deleteRow(const Team &team) const override { throw std::runtime_error("Not yet implemented"); };
};
