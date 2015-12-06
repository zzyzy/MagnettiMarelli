#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <OIC.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(OICTest)
	{
	public:

		TEST_METHOD(GetterSetterTest)
		{
			OIC oic;
			std::string name = "Sarah Kerrigan";
			std::string password = "st4rcr@ft";
			bool evaluation = false;

			oic.setName(name);
			oic.setPassword(password);
			oic.setLocked(OIC::UNLOCKED);

			evaluation = oic.getName() == name
				&& oic.getPassword() == password
				&& oic.getLocked() == OIC::UNLOCKED;

			Assert::IsTrue(evaluation, L"message", LINE_INFO());
		}

		TEST_METHOD(IsLockedTest)
		{
			OIC oic;

			oic.setLocked(OIC::LOCKED);

			Assert::IsTrue(oic.isLocked(), L"message", LINE_INFO());
		}

	};
}
