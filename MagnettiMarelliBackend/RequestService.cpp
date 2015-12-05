#include <RequestService.h>

RequestService::RequestService(RequestDAO &requestDao)
{
	this->requestDao = &requestDao;
}

std::unordered_map<int, Request> RequestService::getRequestMap(const std::string &team, const std::string &status) const
{
	std::unordered_map<int, Request> tableMap;
	int i = 0;
	for (std::pair<int, std::pair<Request, RowStatus>> record : *requestDao) {
		if (record.second.second == RowStatus::REMOVED
			|| record.second.second == RowStatus::IGNORED) continue;
		if (record.second.first.getTeam() == team && record.second.first.getStatus() == status) {
			tableMap.insert({ ++i, record.second.first });
		}
	}
	return tableMap;
}

Request RequestService::fetchRequest(const std::unordered_map<int, Request> &tableMap, const int &index) const
{
	return requestDao->at(tableMap.at(index).getId()).first;
}

bool RequestService::approveRequest(const Request &request, const ItemService &itemService, const int &workingDays) const
{
	if (itemService.requestItem(request)) {
		std::pair<Request, RowStatus> &record = requestDao->at(request.getId());
		SimpleDate deliveryDate;
		deliveryDate.now();
		deliveryDate.addDay(workingDays);
		record.first.setDeliveryDate(deliveryDate.toString());
		record.first.setStatus(Request::APPROVED);
		record.second = RowStatus::CHANGED;
		return true;
	}

	return false;
}
