#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <unordered_map>

#include "TestDatabase.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(ItemServiceTest)
	{
	public:

		static ItemDAO *itemDao;
		static ItemService *itemService;

		TEST_CLASS_INITIALIZE(LoadTable)
		{
			itemDao->clear();
			itemDao->loadTable();
			std::string log = "Rows fetched: " + std::to_string(itemDao->size());
			Logger::WriteMessage("ItemServiceTest");
			Logger::WriteMessage(log.c_str());
		}

		TEST_METHOD(ItemMapTest)
		{
			std::unordered_map<int, Item> itemMap;
			std::string oic = "Chong Ee Xen";
			itemMap = itemService->getItemMap(oic);
			size_t expectedSize = 3;
			size_t actualSize = itemMap.size();
			Assert::AreEqual(expectedSize, actualSize, L"Size mismatch", LINE_INFO());
		}

		TEST_METHOD(FetchItemTest1)
		{
			std::unordered_map<int, Item> itemMap;
			std::string oic = "Chong Ee Xen";
			itemMap = itemService->getItemMap(oic);
			Item item = itemService->fetchItem(itemMap, 1);
			std::string expectedItem = "Spark Plug";
			Assert::AreEqual(expectedItem, item.getType(), L"Fetch mismatch", LINE_INFO());
		}

		TEST_METHOD(FetchItemTest2)
		{
			std::string type = "Wiper Blade";
			Item item = itemService->fetchItem(type);
			Assert::AreEqual(type, item.getType(), L"Fetch mismatch", LINE_INFO());
		}

		TEST_METHOD(AddStockTest)
		{
			Item item;
			item.setType("Wiper Blade");
			itemService->addStock(item, 100);
			Item fetchedItem = itemService->fetchItem(item.getType());
			Assert::AreEqual(105, fetchedItem.getQuantity(), L"Quantity mismatch", LINE_INFO());
		}

		TEST_METHOD(AddItemTest)
		{
			Item item;
			item.setType("Google Glass");
			item.setQuantity(200);
			item.setOic("Huhu Lala");
			itemService->addItem(item);
			Item fetchedItem = itemService->fetchItem(item.getType());
			Assert::AreEqual(item.getType(), fetchedItem.getType(), L"Item mismatch", LINE_INFO());
		}

		TEST_METHOD(FindItemTest)
		{
			Assert::IsFalse(itemService->findItem("Jelly Deep"));
		}

		TEST_METHOD(RemoveItemTest)
		{
			Item item;
			item.setType("Wiper Blade");
			itemService->removeItem(item);
			Assert::IsFalse(itemService->findItem("Wiper Blade"));
		}

		TEST_METHOD(RequestItemTest)
		{
			Request request;
			request.setItem("Spark Plug");
			request.setQuantity(2);
			Assert::IsTrue(itemService->requestItem(request));
		}

	};

	ItemDAO *ItemServiceTest::itemDao = &TestDatabase::itemDao;
	ItemService *ItemServiceTest::itemService = &TestDatabase::itemService;
}
