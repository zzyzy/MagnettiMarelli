#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <SimpleDate.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(SimpleDateTest)
	{
	public:

		TEST_METHOD(ConstructorGetterTest)
		{
			SimpleDate date(2015, 12, 8);
			bool evaluation = false;

			evaluation = date.getYear() == 2015
				&& date.getMonth() == 12
				&& date.getDay() == 8;

			Assert::IsTrue(evaluation, L"message", LINE_INFO());
		}

		TEST_METHOD(CurrentTimeTest)
		{
			SimpleDate date;
			time_t now;
			tm t;
			bool evaluation = false;

			date.now();
			now = time(0);
			localtime_s(&t, &now);

			evaluation = date.getYear() == t.tm_year + 1900
				&& date.getMonth() == t.tm_mon + 1
				&& date.getDay() == t.tm_mday;

			Assert::IsTrue(evaluation, L"message", LINE_INFO());
		}

		TEST_METHOD(AddDayTest)
		{
			SimpleDate date(2015, 12, 8);
			bool evaluation = false;

			date.addDay(500);

			evaluation = date.getYear() == 2017
				&& date.getMonth() == 4
				&& date.getDay() == 21;

			Assert::IsTrue(evaluation, L"message", LINE_INFO());
		}

		TEST_METHOD(LeapYearTest1)
		{
			SimpleDate date(2017, 4, 21);
			Assert::IsFalse(date.isLeapYear(), L"message", LINE_INFO());
		}

		TEST_METHOD(LeapYearTest2)
		{
			SimpleDate date(2016, 8, 12);
			Assert::IsTrue(date.isLeapYear(), L"message", LINE_INFO());
		}

		TEST_METHOD(ToStringTest)
		{
			SimpleDate date(2015, 12, 8);
			std::string expectedDate = "2015/12/08";
			Assert::AreEqual(expectedDate, date.toString(), L"message", LINE_INFO());
		}

	};
}
