#pragma once

#include <DAO.h>
#include <Request.h>

class RequestDAO : public DAO<int, Request>
{
public:
	RequestDAO() = delete;
	~RequestDAO() = default;
	RequestDAO(SQLite::Database &db) : DAO(db) {  };

	void loadTable() override;

private:
	void updateRow(const Request &request) const override;
	void addRow(const Request &request) const override { throw std::runtime_error("Not yet implemented"); };
	void deleteRow(const Request &request) const override { throw std::runtime_error("Not yet implemented"); };
};
