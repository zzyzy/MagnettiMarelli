#pragma once

#include <TeamDAO.h>

class TeamService
{
public:
	TeamService() = delete;
	~TeamService() = default;
	TeamService(TeamDAO &teamDao);

	std::unordered_map<int, Team> getTeamMap(const std::string &oic) const;
	Team fetchTeam(const std::unordered_map<int, Team> &tableMap, const int &index) const;

private:
	TeamDAO *teamDao;
};
