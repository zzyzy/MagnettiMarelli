#pragma once

#include <DAO.h>
#include <Item.h>

class ItemDAO : public DAO<std::string, Item>
{
public:
	ItemDAO() = delete;
	~ItemDAO() = default;
	ItemDAO(SQLite::Database &db) : DAO(db) {  };

	void loadTable() override;

private:
	void updateRow(const Item &item) const override;
	void addRow(const Item& item) const override;
	void deleteRow(const Item& item) const override;
};
