#include <Team.h>

std::string Team::Team::getName() const
{
	return name;
}

std::string Team::getBase() const
{
	return base;
}

std::string Team::getWebsite() const
{
	return website;
}

std::string Team::getPassword() const
{
	return password;
}

std::string Team::getGroup() const
{
	return group;
}

std::string Team::getManager() const
{
	return manager;
}

std::string Team::getCar() const
{
	return car;
}

std::string Team::getOic() const
{
	return oic;
}

void Team::setName(const std::string &name)
{
	this->name = name;
}

void Team::setBase(const std::string &base)
{
	this->base = base;
}

void Team::setWebsite(const std::string &website)
{
	this->website = website;
}

void Team::setPassword(const std::string &password)
{
	this->password = password;
}

void Team::setGroup(const std::string &group)
{
	this->group = group;
}

void Team::setManager(const std::string &manager)
{
	this->manager = manager;
}

void Team::setCar(const std::string &car)
{
	this->car = car;
}

void Team::setOic(const std::string &oic)
{
	this->oic = oic;
}
