#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <unordered_map>

#include "TestDatabase.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(RequestServiceTest)
	{
	public:

		static RequestDAO *requestDao;
		static RequestService *requestService;
		static ItemDAO *itemDao;
		static ItemService *itemService;

		TEST_CLASS_INITIALIZE(LoadTable)
		{
			requestDao->clear();
			requestDao->loadTable();
			itemDao->clear();
			itemDao->loadTable();
			std::string log1 = "Request Rows fetched: " + std::to_string(requestDao->size());
			std::string log2 = "Item Rows fetched: " + std::to_string(itemDao->size());
			Logger::WriteMessage("RequestServiceTest");
			Logger::WriteMessage(log1.c_str());
			Logger::WriteMessage(log2.c_str());
		}

		TEST_METHOD(RequestMapTest)
		{
			std::unordered_map<int, Request> requestMap;
			std::string team = "F.W.R.T.";
			requestMap = requestService->getRequestMap(team, Request::PENDING);
			size_t expectedSize = 1;
			size_t mapSize = requestMap.size();
			Assert::AreEqual(expectedSize, mapSize, L"Size mismatch", LINE_INFO());
		}

		TEST_METHOD(FetchRequestTest)
		{
			std::unordered_map<int, Request> requestMap;
			std::string team = "F.W.R.T.";
			requestMap = requestService->getRequestMap(team, Request::PENDING);
			Request request = requestService->fetchRequest(requestMap, 1);
			std::string expectedItem = "Brake Disc";
			Assert::AreEqual(expectedItem, request.getItem(), L"Fetch mismatch", LINE_INFO());
		}

		TEST_METHOD(ApproveRequestTest)
		{
			std::unordered_map<int, Request> requestMap;
			std::string team = "F.W.R.T.";
			requestMap = requestService->getRequestMap(team, Request::PENDING);
			Request request = requestService->fetchRequest(requestMap, 1);
			bool evaluation = requestService->approveRequest(request, *itemService, 7);
			Assert::IsTrue(evaluation, L"Unable to approve request", LINE_INFO());
		}

	};

	RequestDAO *RequestServiceTest::requestDao = &TestDatabase::requestDao;
	RequestService *RequestServiceTest::requestService = &TestDatabase::requestService;
	ItemDAO *RequestServiceTest::itemDao = &TestDatabase::itemDao;
	ItemService *RequestServiceTest::itemService = &TestDatabase::itemService;
}
