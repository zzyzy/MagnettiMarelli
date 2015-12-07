#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <unordered_map>

#include "TestDatabase.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(TeamServiceTest)
	{
	public:

		static TeamDAO *teamDao;
		static TeamService *teamService;

		TEST_CLASS_INITIALIZE(LoadTable)
		{
			teamDao->clear();
			teamDao->loadTable();
			std::string log = "Rows fetched: " + std::to_string(teamDao->size());
			Logger::WriteMessage("TeamServiceTest");
			Logger::WriteMessage(log.c_str());
		}

		TEST_METHOD(TeamMapTest)
		{
			std::unordered_map<int, Team> teamMap;
			std::string oic = "Tan Shou Heng";
			teamMap = teamService->getTeamMap(oic);
			size_t expectedSize = 2;
			size_t actualSize = teamMap.size();
			Assert::AreEqual(expectedSize, actualSize, L"Size mismatch", LINE_INFO());
		}

		TEST_METHOD(FetchTeamTest)
		{
			std::unordered_map<int, Team> teamMap;
			std::string oic = "Tan Shou Heng";
			teamMap = teamService->getTeamMap(oic);
			Team team = teamService->fetchTeam(teamMap, 1);
			std::string expectedTeam = "Hyundai Mobis World Rally Team";
			Assert::AreEqual(expectedTeam, team.getName(), L"Fetch mismatch", LINE_INFO());
		}

	};

	TeamDAO *TeamServiceTest::teamDao = &TestDatabase::teamDao;
	TeamService *TeamServiceTest::teamService = &TestDatabase::teamService;
}
