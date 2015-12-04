#pragma once

#include <string>

class Team
{
public:
	Team() = default;
	~Team() = default;

	std::string getName() const;
	std::string getManager() const;
	std::string getBase() const;
	std::string getWebsite() const;
	std::string getCar() const;
	std::string getGroup() const;
	std::string getOic() const;
	std::string getPassword() const;

	void setName(const std::string &name);
	void setManager(const std::string &manager);
	void setBase(const std::string &base);
	void setWebsite(const std::string &website);
	void setCar(const std::string &car);
	void setGroup(const std::string &group);
	void setOic(const std::string &oic);
	void setPassword(const std::string &password);

private:
	std::string name;
	std::string manager;
	std::string base;
	std::string website;
	std::string car;
	std::string group;
	std::string oic;
	std::string password;
};