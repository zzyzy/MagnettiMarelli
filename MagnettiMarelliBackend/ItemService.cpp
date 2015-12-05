#include <ItemService.h>

ItemService::ItemService(ItemDAO &itemDao)
{
	this->itemDao = &itemDao;
}

std::unordered_map<int, Item> ItemService::getItemMap(const std::string &oic) const
{
	std::unordered_map<int, Item> tableMap;
	int i = 0;
	for (std::pair<std::string, std::pair<Item, RowStatus>> record : *itemDao) {
		if (record.second.second == RowStatus::REMOVED
			|| record.second.second == RowStatus::IGNORED) continue;
		if (record.second.first.getOic() == oic) {
			tableMap.insert({ ++i, record.second.first });
		}
	}
	return tableMap;
}

Item ItemService::fetchItem(const std::unordered_map<int, Item> &tableMap, const int &index) const
{
	return itemDao->at(tableMap.at(index).getType()).first;
}

Item ItemService::fetchItem(const std::string &type) const
{
	return itemDao->at(type).first;
}

void ItemService::addStock(const Item &item, const int &quantity) const
{
	std::pair<Item, RowStatus> &record = itemDao->at(item.getType());
	record.first.addQuantity(quantity);
	if (record.second != RowStatus::NEW) {
		record.second = RowStatus::CHANGED;
	}
}

void ItemService::addItem(const Item &item) const
{
	auto record = itemDao->find(item.getType());
	if (record != itemDao->end()) {
		if (record->second.second == RowStatus::REMOVED
			|| record->second.second == RowStatus::IGNORED) {
			record->second.first = item;
			record->second.second = RowStatus::CHANGED;
		}
	}
	else {
		std::pair<std::string, std::pair<Item, RowStatus>> row;
		row.first = item.getType();
		row.second.first = item;
		row.second.second = RowStatus::NEW;
		itemDao->insert(row);
	}
}

bool ItemService::findItem(const std::string &type) const
{
	return itemDao->find(type) != itemDao->end()
		&& itemDao->at(type).second != RowStatus::REMOVED
		&& itemDao->at(type).second != RowStatus::IGNORED;
}

void ItemService::removeItem(const Item &item) const
{
	std::pair<Item, RowStatus> &record = itemDao->at(item.getType());
	if (record.second == RowStatus::NEW) {
		record.second = RowStatus::IGNORED;
	}
	else {
		record.second = RowStatus::REMOVED;
	}
}

bool ItemService::requestItem(const Request &request) const
{
	std::pair<Item, RowStatus> &record = itemDao->at(request.getItem());
	if (record.first.getQuantity() >= request.getQuantity()) {
		record.first.deductQuantity(request.getQuantity());
		if (record.second != RowStatus::NEW) {
			record.second = RowStatus::CHANGED;
		}
		return true;
	}
	
	return false;
}
