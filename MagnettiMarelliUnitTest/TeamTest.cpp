#include "stdafx.h"
#include "CppUnitTest.h"

// Library headers
#include <Team.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MagnettiMarelliUnitTest
{
	TEST_CLASS(TeamTest)
	{
	public:

		TEST_METHOD(GetterSetterTest)
		{
			Team team;
			auto name = "Orange Esports";
			auto base = "Malaysia";
			auto website = "www.orangeesports.com.my";
			auto password = "badfo23";
			auto group = "Group R";
			auto manager = "Jost Capito";
			auto car = "Ford Fiesta RS";
			auto oic = "Tan Shou Heng";
			auto evaluation = false;
			auto *message = L"message";

			team.setName(name);
			team.setBase(base);
			team.setWebsite(website);
			team.setPassword(password);
			team.setGroup(group);
			team.setManager(manager);
			team.setCar(car);
			team.setOic(oic);

			evaluation = team.getName() == name;
			if (!evaluation) {
				message = L"Something wrong with Name getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = team.getBase() == base;
			if (!evaluation) {
				message = L"Something wrong with Base getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = team.getWebsite() == website;
			if (!evaluation) {
				message = L"Something wrong with Website getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = team.getPassword() == password;
			if (!evaluation) {
				message = L"Something wrong with Password getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = team.getGroup() == group;
			if (!evaluation) {
				message = L"Something wrong with Group getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = team.getManager() == manager;
			if (!evaluation) {
				message = L"Something wrong with Manager getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = team.getCar() == car;
			if (!evaluation) {
				message = L"Something wrong with Car getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			evaluation = team.getOic() == oic;
			if (!evaluation) {
				message = L"Something wrong with OIC getter setter";
				Assert::Fail(message, LINE_INFO());
			}

			Assert::IsTrue(evaluation, message, LINE_INFO());
		}

	};
}
