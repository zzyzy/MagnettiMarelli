#include <iostream>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>
#include <Utils.h>

using std::string;
using std::getline;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main()
{
	SQLite::Database db("database/MMDatabase.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
	string OICId;
	string OICPassword;
	int tries = 0;
	bool loggedIn = false;
	bool locked = false;

	SQLite::Statement OICIdQuery(db, "SELECT * FROM OICCred WHERE ID=?");
	cout << "Enter OIC ID: ";
	getline(cin, OICId);
	OICIdQuery.bind(1, OICId.c_str());
	OICIdQuery.executeStep();
	while (!OICIdQuery.isOk()) {
		cout << "Invalid OIC Id" << endl;
		cout << "Enter OIC ID: ";
		getline(cin, OICId);
		OICIdQuery.clearBindings();
		OICIdQuery.reset();
		OICIdQuery.bind(1, OICId.c_str());
		OICIdQuery.executeStep();
	}
	if (OICIdQuery.isOk()) {
		// Check whether the OIC account is locked or not
		locked = OICIdQuery.getColumn("Locked").getInt() == 1;

		if (locked) {
			cout << "Your OIC account is locked!" << endl;
			cout << "Contact the administrator in charge to resolve this issue." << endl;
			cout << "Press any key to continue . . . ";
			cin.get();
			return 1;
		}
	}

	SQLite::Statement OICCredQuery(db, "SELECT * FROM OICCred WHERE ID=? AND Password=?");
	cout << "Enter OIC Password: ";
	getline(cin, OICPassword);
	OICCredQuery.bind(1, OICId.c_str());
	OICCredQuery.bind(2, Utils::caesar(OICPassword).c_str());
	OICCredQuery.executeStep();
	++tries;
	while (!OICCredQuery.isOk() && tries < 3) {
		cout << "Invalid OIC Password" << endl;
		cout << "Enter OIC Password: ";
		getline(cin, OICPassword);
		OICCredQuery.clearBindings();
		OICCredQuery.reset();
		OICCredQuery.bind(1, OICId.c_str());
		OICCredQuery.bind(2, Utils::caesar(OICPassword).c_str());
		OICCredQuery.executeStep();
		++tries;
	}
	if (OICCredQuery.isOk()) {
		// Check whether the OIC account is locked or not
		locked = OICCredQuery.getColumn("Locked").getInt() == 1;

		if (!locked) {
			cout << "Welcome!" << endl;
			loggedIn = true;
		}
		else {
			cout << "Your OIC account is locked!" << endl;
			cout << "Contact the administrator in charge to resolve this issue." << endl;
		}
	}
	else {
		if (!locked) {
			cout << "You have failed to login for 3 times." << endl;
			cout << "As such, your account is locked." << endl;
			cout << "Contact the administrator in charge to resolve this issue." << endl;

			// Lock the account
			SQLite::Transaction lockTransaction(db);
			SQLite::Statement lockQuery(db, "UPDATE OICCred SET Locked=1 WHERE ID=?");
			lockQuery.bind(1, OICId.c_str());
			lockQuery.exec();
			lockTransaction.commit();
			locked = true;
		}
		else {
			cout << "Your OIC account is locked!" << endl;
			cout << "Contact the administrator in charge to resolve this issue." << endl;
		}
	}

	if (loggedIn) {

	}
	
	cout << "Press any key to continue . . . ";
	cin.get();
	return 0;
}
