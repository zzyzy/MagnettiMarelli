#pragma once

#include <string>

class Team
{
public:
	Team() = default;
	~Team() = default;

	std::string getName() const;
	std::string getBase() const;
	std::string getWebsite() const;
	std::string getPassword() const;
	std::string getGroup() const;
	std::string getManager() const;
	std::string getCar() const;
	std::string getOic() const;

	void setName(const std::string &name);
	void setBase(const std::string &base);
	void setWebsite(const std::string &website);
	void setPassword(const std::string &password);
	void setGroup(const std::string &group);
	void setManager(const std::string &manager);
	void setCar(const std::string &car);
	void setOic(const std::string &oic);

private:
	std::string name;
	std::string base;
	std::string website;
	std::string password;
	std::string group;
	std::string manager;
	std::string car;
	std::string oic;
};
