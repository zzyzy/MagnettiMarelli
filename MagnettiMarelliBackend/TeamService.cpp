#include <TeamService.h>

TeamService::TeamService(TeamDAO &teamDao)
{
	this->teamDao = &teamDao;
}

std::unordered_map<int, Team> TeamService::getTeamMap(const std::string &oic) const
{
	std::unordered_map<int, Team> tableMap;
	int i = 0;
	for (std::pair<std::string, std::pair<Team, RowStatus>> record : *teamDao) {
		if (record.second.second == RowStatus::REMOVED
			|| record.second.second == RowStatus::IGNORED) continue;
		if (record.second.first.getOic() == oic) {
			tableMap.insert({ ++i, record.second.first });
		}
	}
	return tableMap;
}

Team TeamService::fetchTeam(const std::unordered_map<int, Team> &tableMap, const int &index) const
{
	return teamDao->at(tableMap.at(index).getName()).first;
}
