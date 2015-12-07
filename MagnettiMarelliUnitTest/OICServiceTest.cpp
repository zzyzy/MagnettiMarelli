#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include "TestDatabase.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(OICServiceTest)
	{
	public:

		static OICDAO *oicDao;
		static OICService *oicService;

		TEST_CLASS_INITIALIZE(LoadTable)
		{
			oicDao->clear();
			oicDao->loadTable();
			std::string log = "Rows fetched: " + std::to_string(oicDao->size());
			Logger::WriteMessage("OICServiceTest");
			Logger::WriteMessage(log.c_str());
		}

		TEST_METHOD(VerifyUsernameTest)
		{
			std::string name = "Tan Shou Heng";
			bool evaluation = oicService->verifyUsername(name);
			std::string loginError = oicService->getLoginError();
			std::wstring message(loginError.begin(), loginError.end());
			Assert::IsTrue(oicService->verifyUsername(name), message.c_str(), LINE_INFO());
		}

		TEST_METHOD(VerifyPasswordTest)
		{
			std::string name = "Tan Shou Heng";
			std::string password = "123hsy";
			const int maxTries = 3;
			bool evaluation = oicService->verifyPassword(name, password, maxTries);
			std::string loginError = oicService->getLoginError();
			std::wstring message(loginError.begin(), loginError.end());
			Assert::IsTrue(evaluation, message.c_str(), LINE_INFO());
		}

		TEST_METHOD(LockOICTest)
		{
			std::string name = "Tan Shou Heng";
			std::string password = "aaaaaa";
			const int maxTries = 3;
			oicService->verifyPassword(name, password, maxTries);
			oicService->verifyPassword(name, password, maxTries);
			oicService->verifyPassword(name, password, maxTries);
			OIC oic = oicDao->at(name).first;
			Assert::IsTrue(oic.isLocked());
		}

		TEST_METHOD(LoginLockedAccountTest)
		{
			std::string name = "Lee Zhen Zhi";
			Assert::IsFalse(oicService->verifyUsername(name));
		}

	};

	OICDAO *OICServiceTest::oicDao = &TestDatabase::oicDao;
	OICService *OICServiceTest::oicService = &TestDatabase::oicService;
}
