#include <OICDAO.h>

void OICDAO::loadTable()
{
	SQLite::Statement stmt(*db, "SELECT * FROM OIC");
	while (stmt.executeStep()) {
		OIC oic;
		oic.setName(stmt.getColumn("Name").getText());
		oic.setPassword(stmt.getColumn("Password").getText());
		oic.setLocked(stmt.getColumn("Locked").getInt());
		table.insert({ oic.getName(), {oic, RowStatus::DEFAULT} });
	}
}

void OICDAO::updateRow(const OIC &oic) const
{
	SQLite::Statement stmt(*db, "UPDATE OIC SET Password=?, Locked=? WHERE Name=?");
	stmt.bind(1, oic.getPassword());
	stmt.bind(2, oic.getLocked());
	stmt.bind(3, oic.getName());
	stmt.exec();
}
