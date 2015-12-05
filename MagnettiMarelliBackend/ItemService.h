#pragma once

#include <ItemDAO.h>
#include <Request.h>

class ItemService
{
public:
	ItemService() = delete;
	~ItemService() = default;
	ItemService(ItemDAO &itemDao);

	std::unordered_map<int, Item> getItemMap(const std::string &oic) const;
	Item fetchItem(const std::unordered_map<int, Item> &tableMap, const int &index) const;
	Item fetchItem(const std::string &type) const;
	void addStock(const Item &item, const int &quantity) const;
	void addItem(const Item &item) const;
	bool findItem(const std::string &type) const;
	void removeItem(const Item &item) const;
	bool requestItem(const Request &request) const;

private:
	ItemDAO *itemDao;
};
