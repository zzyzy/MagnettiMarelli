#include <Team.h>

std::string Team::getName() const
{
	return name;
}

std::string Team::getManager() const
{
	return manager;
}

std::string Team::getBase() const
{
	return base;
}

std::string Team::getWebsite() const
{
	return website;
}

std::string Team::getCar() const
{
	return car;
}

std::string Team::getGroup() const
{
	return group;
}

std::string Team::getOic() const
{
	return oic;
}

std::string Team::getPassword() const
{
	return password;
}

void Team::setName(const std::string &name)
{
	this->name = name;
}

void Team::setManager(const std::string &manager)
{
	this->manager = manager;
}

void Team::setBase(const std::string &base)
{
	this->base = base;
}

void Team::setWebsite(const std::string &website)
{
	this->website = website;
}

void Team::setCar(const std::string &car)
{
	this->car = car;
}

void Team::setGroup(const std::string &group)
{
	this->group = group;
}

void Team::setOic(const std::string &oic)
{
	this->oic = oic;
}

void Team::setPassword(const std::string &password)
{
	this->password = password;
}