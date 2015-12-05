#pragma once

#include <string>

class Item
{
public:
	Item() = default;
	~Item() = default;

	std::string getType() const;
	int getQuantity() const;
	std::string getOic() const;

	void setType(const std::string &type);
	void setQuantity(const int &quantity);
	void setOic(const std::string &oic);

	bool deductQuantity(const int &quantity);
	void addQuantity(const int &quantity);

	struct Hasher {
		size_t operator()(const Item &item) const;
	};
	bool operator==(const Item &item) const;

private:
	std::string type;
	int quantity;
	std::string oic;
};
