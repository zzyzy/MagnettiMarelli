#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <Request.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(RequestTest)
	{
	public:

		TEST_METHOD(GetterSetterTest)
		{
			Request request;
			auto requestDate = "2015/12/08";
			auto deliveryDate = "2015/12/15";
			auto team = "Blizzard Entertainment";
			auto item = "Lightsaber";
			auto oic = "Obi 1 Kenobi";
			auto evaluation = false;
			auto *message = L"message";

			request.setId(1);
			request.setQuantity(200);
			request.setRequestDate(requestDate);
			request.setDeliveryDate(deliveryDate);
			request.setTeam(team);
			request.setItem(item);
			request.setOic(oic);

			evaluation = request.getId() == 1;
			if (!evaluation) {
				message = L"Something wrong with Id getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = request.getQuantity() == 200;
			if (!evaluation) {
				message = L"Something wrong with Quantity getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = request.getRequestDate() == requestDate;
			if (!evaluation) {
				message = L"Something wrong with Request Date getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = request.getDeliveryDate() == deliveryDate;
			if (!evaluation) {
				message = L"Something wrong with Delivery Date getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = request.getTeam() == team;
			if (!evaluation) {
				message = L"Something wrong with Team getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = request.getItem() == item;
			if (!evaluation) {
				message = L"Something wrong with Item getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = request.getOic() == oic;
			if (!evaluation) {
				message = L"Something wrong with OIC getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			Assert::IsTrue(evaluation, message, LINE_INFO());
		}

	};
}
