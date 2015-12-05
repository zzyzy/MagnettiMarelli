#include "Request.h"

const std::string Request::PENDING = "Pending";
const std::string Request::APPROVED = "Approved";

int Request::getId() const
{
	return id;
}

int Request::getQuantity() const
{
	return quantity;
}

std::string Request::getRequestDate() const
{
	return requestDate;
}

std::string Request::getDeliveryDate() const
{
	return deliveryDate;
}

std::string Request::getStatus() const
{
	return status;
}

std::string Request::getTeam() const
{
	return team;
}

std::string Request::getItem() const
{
	return item;
}

std::string Request::getOic() const
{
	return oic;
}

void Request::setId(const int &id)
{
	this->id = id;
}

void Request::setQuantity(const int &quantity)
{
	this->quantity = quantity;
}

void Request::setRequestDate(const std::string &requestDate)
{
	this->requestDate = requestDate;
}

void Request::setDeliveryDate(const std::string &deliveryDate)
{
	this->deliveryDate = deliveryDate;
}

void Request::setStatus(const std::string &status)
{
	this->status = status;
}

void Request::setTeam(const std::string &team)
{
	this->team = team;
}

void Request::setItem(const std::string &item)
{
	this->item = item;
}

void Request::setOic(const std::string &oic)
{
	this->oic = oic;
}

size_t Request::Hasher::operator()(const Request &request) const
{
	return std::hash<int>()(request.getId())
		^ std::hash<int>()(request.getQuantity())
		^ std::hash<std::string>()(request.getRequestDate())
		^ std::hash<std::string>()(request.getDeliveryDate())
		^ std::hash<std::string>()(request.getStatus())
		^ std::hash<std::string>()(request.getTeam())
		^ std::hash<std::string>()(request.getItem())
		^ std::hash<std::string>()(request.getOic());
}

bool Request::operator==(const Request &request) const
{
	return id == request.getId() &&
		quantity == request.getQuantity() &&
		requestDate == request.getRequestDate() &&
		deliveryDate == request.getDeliveryDate() &&
		status == request.getStatus() &&
		team == request.getTeam() &&
		item == request.getItem() &&
		oic == request.getOic();
}
