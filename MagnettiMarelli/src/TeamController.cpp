#include <TeamController.h>

Team TeamController::getTeam(const std::string &name)
{
	Team team;
	SQLite::Statement teamStmt(db, "SELECT * FROM Team WHERE Name=?");
	teamStmt.bind(1, name);
	teamStmt.executeStep();
	team.setName(teamStmt.getColumn("Name").getText());
	team.setManager(teamStmt.getColumn("Manager").getText());
	team.setBase(teamStmt.getColumn("Base").getText());
	team.setWebsite(teamStmt.getColumn("Website").getText());
	team.setCar(teamStmt.getColumn("Car").getText());
	team.setGroup(teamStmt.getColumn("Group").getText());
	team.setOic(teamStmt.getColumn("OIC").getText());
	team.setPassword(teamStmt.getColumn("Password").getText());
	return team;
}
