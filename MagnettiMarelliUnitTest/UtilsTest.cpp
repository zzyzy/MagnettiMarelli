#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <Utils.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{		
	TEST_CLASS(UtilsTest)
	{
	public:

		TEST_METHOD(CaesarEncryptionTest)
		{
			std::string pwBefore = "Googl3Pluz";
			std::string pwAfter = "Tbbty3Cyhm";
			Assert::AreEqual(pwAfter, Utils::caesar(pwBefore), L"message", LINE_INFO());
		}

	};
}
