#pragma once

#include <string>

class Request
{
public:
	static const std::string PENDING;
	static const std::string APPROVED;

	Request() = default;
	~Request() = default;

	int getId() const;
	int getQuantity() const;
	std::string getRequestDate() const;
	std::string getDeliveryDate() const;
	std::string getStatus() const;
	std::string getTeam() const;
	std::string getItem() const;
	std::string getOic() const;

	void setId(const int &id);
	void setQuantity(const int &quantity);
	void setRequestDate(const std::string &requestDate);
	void setDeliveryDate(const std::string &deliveryDate);
	void setStatus(const std::string &status);
	void setTeam(const std::string &team);
	void setItem(const std::string &item);
	void setOic(const std::string &oic);

	struct Hasher {
		size_t operator()(const Request &request) const;
	};
	bool operator==(const Request &request) const;

private:
	int id;
	int quantity;
	std::string requestDate;
	std::string deliveryDate;
	std::string status;
	std::string team;
	std::string item;
	std::string oic;
};
