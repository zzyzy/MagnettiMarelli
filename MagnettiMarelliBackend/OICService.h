#pragma once

#include <OICDAO.h>
#include <Utils.h>

class OICService
{
public:
	OICService() = delete;
	~OICService() = default;
	OICService(OICDAO &oicDao);

	bool verifyUsername(const std::string &name);
	bool verifyPassword(const std::string &name, const std::string &password, const int &maxTries);
	std::string getLoginError();

private:
	OICDAO *oicDao;
	std::unordered_map<std::string, int> loginTries;
	std::string loginError;

	bool findOIC(const std::string &name) const;
	bool findOIC(const std::string &name, const std::string &password) const;
	bool isLocked(const std::string &name) const;
	void lockOIC(const std::string &name) const;
};
