#include <iostream>
#include <string>
#include <unordered_map>

#include <SQLiteCpp/SQLiteCpp.h>
#include <Utils.h>

using namespace std;

SQLite::Database db("database/MagnettiMarelli.db", SQLITE_OPEN_READWRITE);

const int MAX_TRIES = 3;

bool findOIC(const std::string &name)
{
	SQLite::Statement stmt(db, "SELECT * FROM OIC WHERE Name=?");
	stmt.bind(1, name);
	stmt.executeStep();
	return stmt.isOk();
}

bool findOIC(const std::string &name, const std::string &password)
{
	SQLite::Statement stmt(db, "SELECT * FROM OIC WHERE Name=? AND Password=?");
	stmt.bind(1, name);
	stmt.bind(2, Utils::caesar(password).c_str());
	stmt.executeStep();
	return stmt.isOk();
}

bool isLocked(const std::string &name)
{
	SQLite::Statement stmt(db, "SELECT Locked FROM OIC WHERE Name=?");
	stmt.bind(1, name);
	stmt.executeStep();
	if (stmt.isOk()) {
		return stmt.getColumn("Locked").getInt() == 1;
	}
	else {
		return false;
	}
}

void lockOIC(const std::string &name)
{
	SQLite::Statement stmt(db, "UPDATE OIC SET Locked=1 WHERE Name=?");
	stmt.bind(1, name);
	stmt.exec();
}

void OICPage(const std::string &name)
{
	system("cls");
	char choice;

	do {
		cout << "Welcome" << endl;
		cout << "1 - Manage Team" << endl;
		cout << "2 - Manage Inventory" << endl;
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '1' && choice != '2' && choice != '#') {
			cout << "Invalid choice. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#') {
			switch (choice) {
			case '1':
				//TeamPage(name);
				break;
			case '2':
				//InventoryPage(name);
				break;
			}
		}

	} while (choice != '#');
	system("cls");
}

void verifyOICPassword(const std::string &name, unordered_map<string, int> &tries)
{
	std::string password;

	if (tries[name] < MAX_TRIES) {
		cout << "Enter OIC password: ";
		getline(cin, password);
		++tries[name];
		if (findOIC(name, password)) {
			tries[name] = 0;
			OICPage(name);
		}
		else {
			cout << "Unable to authenticate OIC account" << endl;
		}
	}
	else {
		lockOIC(name);
		cout << "OIC account has been locked" << endl;
	}
}

void verifyOICName(unordered_map<string, int> &tries)
{
	std::string name;

	cout << "Enter OIC name: ";
	getline(cin, name);
	if (findOIC(name)) {
		if (!isLocked(name)) {
			verifyOICPassword(name, tries);
		}
		else {
			cout << "OIC account is locked" << endl;
		}
	}
	else {
		cout << "OIC account not found" << endl;
	}
}

void MainPage()
{
	system("cls");
	char choice;
	unordered_map<string, int> tries;

	do {
		cout << "1 - Login" << endl;
		cout << "2 - Quit" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '1' && choice != '2') {
			cout << "Invalid choice. Try again." << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice == '1') {
			verifyOICName(tries);
		}
	} while (choice != '2');
	system("cls");
}

int main()
{
	MainPage();
	return 0;
}
