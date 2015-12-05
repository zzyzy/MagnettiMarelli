#include <OIC.h>

const int OIC::LOCKED = 1;
const int OIC::UNLOCKED = 0;

std::string OIC::getName() const
{
	return name;
}

std::string OIC::getPassword() const
{
	return password;
}

int OIC::getLocked() const
{
	return locked;
}

void OIC::setName(const std::string &name)
{
	this->name = name;
}

void OIC::setPassword(const std::string &password)
{
	this->password = password;
}

void OIC::setLocked(const int &locked)
{
	this->locked = locked;
}

bool OIC::isLocked() const
{
	return locked == LOCKED;
}
