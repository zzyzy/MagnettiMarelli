#include <ItemDAO.h>

void ItemDAO::loadTable()
{
	SQLite::Statement stmt(*db, "SELECT * FROM Item");
	while (stmt.executeStep()) {
		Item item;
		item.setType(stmt.getColumn("Type").getText());
		item.setQuantity(stmt.getColumn("Quantity").getInt());
		item.setOic(stmt.getColumn("OIC").getText());
		table.insert({ item.getType(), {item, RowStatus::DEFAULT} });
	}
}

void ItemDAO::updateRow(const Item &item) const
{
	SQLite::Statement stmt(*db, "UPDATE Item SET Quantity=?, OIC=? WHERE Type=?");
	stmt.bind(1, item.getQuantity());
	stmt.bind(2, item.getOic());
	stmt.bind(3, item.getType());
	stmt.exec();
}

void ItemDAO::addRow(const Item &item) const
{
	SQLite::Statement stmt(*db, "INSERT INTO Item VALUES (?,?,?)");
	stmt.bind(1, item.getType());
	stmt.bind(2, item.getQuantity());
	stmt.bind(3, item.getOic());
	stmt.exec();
}

void ItemDAO::deleteRow(const Item &item) const
{
	SQLite::Statement stmt(*db, "DELETE FROM Item WHERE Type=?");
	stmt.bind(1, item.getType());
	stmt.exec();
}
