#pragma once

#include <string>

class OIC
{
public:
	static const int LOCKED;
	static const int UNLOCKED;

	OIC() = default;
	~OIC() = default;

	std::string getName() const;
	std::string getPassword() const;
	int getLocked() const;

	void setName(const std::string &name);
	void setPassword(const std::string &password);
	void setLocked(const int &locked);

	bool isLocked() const;

private:
	std::string name;
	std::string password;
	int locked;
};
