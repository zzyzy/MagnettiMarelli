#pragma once

#include <Controller.h>
#include <Team.h>
#include <string>

class TeamController : public Controller
{
public:
	static Team getTeam(const std::string &name);

private:
	TeamController() = default;
	~TeamController() = default;
};