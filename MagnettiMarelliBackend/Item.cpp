#include <Item.h>

std::string Item::getType() const
{
	return type;
}

int Item::getQuantity() const
{
	return quantity;
}

std::string Item::getOic() const
{
	return oic;
}

void Item::setType(const std::string &type)
{
	this->type = type;
}

void Item::setQuantity(const int &quantity)
{
	this->quantity = quantity;
}

void Item::setOic(const std::string &oic)
{
	this->oic = oic;
}

bool Item::deductQuantity(const int &quantity)
{
	if (this->quantity >= quantity) {
		this->quantity -= quantity;
		return true;
	}
	else {
		return false;
	}
}

void Item::addQuantity(const int &quantity)
{
	this->quantity += quantity;
}

size_t Item::Hasher::operator()(const Item &item) const
{
	return std::hash<std::string>()(item.getType())
		^ std::hash<int>()(item.getQuantity())
		^ std::hash<std::string>()(item.getOic());
}

bool Item::operator==(const Item &item) const
{
	return type == item.getType() &&
		quantity == item.getQuantity() &&
		oic == item.getOic();
}
