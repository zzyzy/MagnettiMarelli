#include <TeamDAO.h>

void TeamDAO::loadTable()
{
	SQLite::Statement stmt(*db, "SELECT * FROM Team");
	while (stmt.executeStep()) {
		Team team;
		team.setName(stmt.getColumn("Name").getText());
		team.setBase(stmt.getColumn("Base").getText());
		team.setWebsite(stmt.getColumn("Website").getText());
		team.setPassword(stmt.getColumn("Password").getText());
		team.setGroup(stmt.getColumn("Group").getText());
		team.setManager(stmt.getColumn("Manager").getText());
		team.setCar(stmt.getColumn("Car").getText());
		team.setOic(stmt.getColumn("OIC").getText());
		table.insert({ team.getName(), {team, RowStatus::DEFAULT} });
	}
}
