#pragma once

#include <RequestDAO.h>
#include <ItemService.h>
#include <SimpleDate.h>

class RequestService
{
public:
	RequestService() = delete;
	~RequestService() = default;
	RequestService(RequestDAO &requestDao);

	std::unordered_map<int, Request> getRequestMap(const std::string &team, const std::string &status) const;
	Request fetchRequest(const std::unordered_map<int, Request> &tableMap, const int &index) const;
	bool approveRequest(const Request &request, const ItemService &itemService, const int &workingDays) const;

private:
	RequestDAO *requestDao;
};
