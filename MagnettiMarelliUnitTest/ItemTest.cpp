#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <Item.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(ItemTest)
	{
	public:

		TEST_METHOD(GetterSetterTest)
		{
			Item item;
			std::string type = "Google Glass";
			std::string oic = "Sarah Kerrigan";
			bool evaluation = false;

			item.setType(type);
			item.setQuantity(200);
			item.setOic(oic);

			evaluation = item.getType() == type
				&& item.getQuantity() == 200
				&& item.getOic() == oic;

			Assert::IsTrue(evaluation, L"message", LINE_INFO());
		}

		TEST_METHOD(DeductQuantityTest)
		{
			Item item;

			item.setQuantity(200);
			item.deductQuantity(50);

			Assert::IsTrue(item.getQuantity() == 150, L"message", LINE_INFO());
		}

		TEST_METHOD(AddQuantityTest)
		{
			Item item;

			item.setQuantity(200);
			item.addQuantity(50);

			Assert::IsTrue(item.getQuantity() == 250, L"message", LINE_INFO());
		}

		TEST_METHOD(EqualityTest)
		{
			Item item1;
			Item item2;

			item1.setType("Google Glass");
			item1.setQuantity(200);
			item1.setOic("Sarah Kerrigan");

			item2.setType("Microsoft HoloLens");
			item2.setQuantity(100);
			item2.setOic("James Bond");

			Assert::IsFalse(item1 == item2, L"message", LINE_INFO());
		}

	};
}
