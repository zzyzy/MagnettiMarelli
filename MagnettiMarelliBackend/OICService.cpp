#include <OICService.h>

OICService::OICService(OICDAO &oicDao)
{
	this->oicDao = &oicDao;
}

bool OICService::verifyUsername(const std::string &name)
{
	if (findOIC(name)) {
		if (!isLocked(name)) {
			return true;
		}
		else {
			loginError = "OIC account locked";
		}
	}
	else {
		loginError = "OIC account not found";
	}

	return false;
}

bool OICService::verifyPassword(const std::string &name, const std::string &password, const int &maxTries)
{
	if (loginTries[name] < maxTries - 1) {
		++loginTries[name];
		if (findOIC(name, password)) {
			loginTries[name] = 0;
			return true;
		}
		else {
			loginError = "Unable to authenticate OIC account";
		}
	}
	else {
		lockOIC(name);
		loginError = "OIC account has been locked";
	}

	return false;
}

std::string OICService::getLoginError()
{
	std::string temp = loginError;
	loginError.clear();
	return temp;
}

bool OICService::findOIC(const std::string &name) const
{
	return oicDao->find(name) != oicDao->end()
		&& oicDao->at(name).second != RowStatus::REMOVED
		&& oicDao->at(name).second != RowStatus::IGNORED;
}

bool OICService::findOIC(const std::string &name, const std::string &password) const
{
	for (std::pair<std::string, std::pair<OIC, RowStatus>> record : *oicDao) {
		if (record.second.first.getName() == name && record.second.first.getPassword() == Utils::caesar(password)) {
			return true;
		}
	}

	return false;
}

bool OICService::isLocked(const std::string &name) const
{
	return oicDao->at(name).first.getLocked() == OIC::LOCKED;
}

void OICService::lockOIC(const std::string &name) const
{
	std::pair<OIC, RowStatus> &record = oicDao->at(name);
	record.first.setLocked(OIC::LOCKED);
	record.second = RowStatus::CHANGED;
}
