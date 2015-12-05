#include <iostream>
#include <string>
#include <unordered_map>

#include <SQLiteCpp/SQLiteCpp.h>
#include <ItemService.h>
#include <Team.h>
#include <RequestService.h>
#include <Utils.h>

using namespace std;

#ifdef _DEBUG
SQLite::Database db(MAGNETTIDB, SQLITE_OPEN_READWRITE);
#else
SQLite::Database db("MagnettiMarelli.db", SQLITE_OPEN_READWRITE);
#endif

const int MAX_TRIES = 3;
const int WORKING_DAYS = 7;

ItemDAO itemDao(db);
RequestDAO requestDao(db);
ItemService itemService(itemDao);
RequestService requestService(requestDao);

void initInMemoryDb()
{
	cout << "Loading Item table. . ." << endl;
	itemDao.loadTable();
	cout << "Loading Item table. . . done!" << endl;
	cout << "Loading Request table. . ." << endl;
	requestDao.loadTable();
	cout << "Loading Request table. . . done!" << endl;
}

void commitInMemoryDb()
{
	cout << "Saving Item table. . ." << endl;
	itemDao.saveTable();
	cout << "Saving Item table. . . done!" << endl;
	cout << "Saving Request table" << endl;
	requestDao.saveTable();
	cout << "Saving Request table. . . done!" << endl;
}

void showTeams(const unordered_map<int, std::string> &teams)
{
	if (teams.empty()) { cout << "No managed teams" << endl; return; }
	for (pair<int, std::string> p : teams) {
		cout << p.first << " - " << p.second << endl;
	}
}

void showRequests(const unordered_map<int, Request> &requests)
{
	if (requests.empty()) { cout << "No requests" << endl; return; }
	for (pair<int, Request> p : requests) {
		cout << p.first << " - " << p.second.getTeam() << " - " << p.second.getItem() << " - " << p.second.getStatus() << endl;
	}
}

void showItems(const unordered_map<int, Item> &items)
{
	if (items.empty()) { cout << "No managed items" << endl; return; }
	for (pair<int, Item> p : items) {
		cout << p.first << " - " << p.second.getType() << " - " << p.second.getQuantity() << " ea" << endl;
	}
}

void showItemDetails(const Item& item)
{
	cout << "Item type - " << item.getType() << endl;
	cout << "Quantity - " << item.getQuantity() << endl;
	cout << "In charge by - " << item.getOic() << endl;
}

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

unordered_map<int, string> fetchTeams(const std::string &name)
{
	int i = 0;
	unordered_map<int, string> managedTeams;
	SQLite::Statement stmt(db, "SELECT * FROM Team WHERE OIC=?");
	stmt.bind(1, name);
	while (stmt.executeStep()) {
		managedTeams.insert({ ++i, stmt.getColumn("Name").getText() });
	}
	return managedTeams;
}

void RequestProcessPage(const Request &request)
{
	char choice;

	system("cls");
	cout << request.getTeam() << " - " << request.getItem() << endl;
	cout << "Y - Approve" << endl;
	cout << "N - Decline" << endl;
	cout << "> "; cin >> choice; cin.ignore();
	while (choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n') {
		cout << "Invalid choice. Try again" << endl;
		cout << "> "; cin >> choice; cin.ignore();
	}

	if (choice == 'y' || choice == 'Y') {
		if (requestService.approveRequest(request, itemService, WORKING_DAYS)) {
			cout << "Request processed successfully!" << endl;
		}
		else {
			cout << "Not enough stock to process request" << endl;
		}
	}
	system("cls");
}

void TeamRequestPage(const std::string &team)
{
	char choice;
	unordered_map<int, Request> requests;

	system("cls");
	do {
		cout << team << endl;
		requests = requestService.getRequestMap(team, Request::PENDING);
		showRequests(requests);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && requests.find(choice - '0') == requests.end()) {
			cout << "Invalid Request ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			RequestProcessPage(requestService.fetchRequest(requests, choice - '0'));
		}
	} while (choice != '#');
	system("cls");
}

void TeamPage(const std::string &name)
{
	char choice;
	unordered_map<int, string> teams;

	system("cls");
	do {
		cout << "Team Request Management" << endl;
		teams = fetchTeams(name);
		showTeams(teams);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && teams.find(choice - '0') == teams.end()) {
			cout << "Invalid Team ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			TeamRequestPage(teams.at(choice - '0'));
		}
	} while (choice != '#');
	system("cls");
}

void AddItemPage(const std::string &oic)
{
	std::string type;
	int quantity;

	system("cls");
	cout << "Welcome" << endl;
	cout << "New item type (# to cancel)" << endl;
	cout << "> "; getline(cin, type);
	if (type != "#") {
		if (itemService.findItem(type)) {
			Item item = itemService.fetchItem(type);
			cout << endl << "Item already exists in inventory" << endl;
			cout << "Stock level - " << item.getQuantity() << endl;
			cout << "In charge by - " << item.getOic() << endl;
			cout << "Contact the officer in charge for any enquiry" << endl;
		}
		else {
			cout << "New item quantity (-1 to cancel)" << endl;
			cout << "> "; cin >> quantity; cin.ignore();
			while (quantity != -1 && quantity <= 0) {
				cout << "Invalid quantity. Try again" << endl;
				cout << "> "; cin >> quantity; cin.ignore();
			}

			if (quantity != -1) {
				Item newItem;
				newItem.setType(type);
				newItem.setQuantity(quantity);
				newItem.setOic(oic);
				itemService.addItem(newItem);
				cout << "New item is added." << endl;
				system("pause");
			}
		}
	}
	system("cls");
}

void StockUpdateProcessPage(Item &item)
{
	int quantity;

	system("cls");
	cout << "Welcome" << endl;
	cout << "Item type - " << item.getType() << endl;
	cout << "Current quantity - " << item.getQuantity() << endl;
	cout << "New add-in quantity (-1 to cancel)" << endl;
	cout << "> "; cin >> quantity; cin.ignore();
	while (quantity != -1 && quantity <= 0) {
		cout << "Invalid quantity. Try again" << endl;
		cout << "> "; cin >> quantity; cin.ignore();
	}

	if (quantity != -1) {
		itemService.addStock(item, quantity);
		cout << "Quantity of item is updated." << endl;
		system("pause");
	}
	system("cls");
}

void UpdateStockPage(const std::string &name)
{
	char choice;
	unordered_map<int, Item> items;;

	system("cls");
	do {
		cout << "Update item" << endl;
		items = itemService.getItemMap(name);
		showItems(items);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && items.find(choice - '0') == items.end()) {
			cout << "Invalid Item ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			StockUpdateProcessPage(itemService.fetchItem(items, choice - '0'));
		}
	} while (choice != '#');
	system("cls");
}

void ItemDetailsPage(const std::string &type)
{
	system("cls");
	cout << "Item Details" << endl;
	if (itemService.findItem(type)) {
		showItemDetails(itemService.fetchItem(type));
	}
	else {
		cout << "The item does not exist in the inventory." << endl;
	}
	system("pause");
	system("cls");
}

void SearchItemPage()
{
	std::string type;

	system("cls");
	do {
		cout << "Search Item" << endl;
		cout << "Item type (# to back)" << endl;
		cout << "> "; getline(cin, type);

		if (type != "#") {
			ItemDetailsPage(type);
		}
	} while (type != "#");
	system("cls");
}

void ItemRemoveProcessPage(const Item &item)
{
	char choice;

	system("cls");
	cout << "Remove item confirmation";
	showItemDetails(item);
	cout << "Are you sure to you want to remove this item?" << endl;
	cout << "Y - Delete" << endl;
	cout << "N - Cancel" << endl;
	cout << "> "; cin >> choice; cin.ignore();
	while (choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n') {
		cout << "Invalid choice. Try again" << endl;
		cout << "> "; cin >> choice; cin.ignore();
	}

	if (choice == 'y' || choice == 'Y') {
		itemService.removeItem(item);
		cout << "Item is removed." << endl;
		system("pause");
	}
	system("cls");
}

void RemoveItemPage(const std::string &oic)
{
	char choice;
	unordered_map<int, Item> items;

	system("cls");
	do {
		cout << "Remove item" << endl;
		items = itemService.getItemMap(oic);
		showItems(items);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && items.find(choice - '0') == items.end()) {
			cout << "Invalid Item ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			ItemRemoveProcessPage(itemService.fetchItem(items, choice - '0'));
		}
	} while (choice != '#');
	system("cls");
}

void InventoryPage(const std::string &oic)
{
	char choice;

	system("cls");
	do {
		cout << "Inventory Management" << endl;
		cout << "1 - Add Item" << endl;
		cout << "2 - Update Stock" << endl;
		cout << "3 - Search Item" << endl;
		cout << "4 - Remove Item" << endl;
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '1' && choice != '2'
			&& choice != '3' && choice != '4' && choice != '#') {
			cout << "Invalid choice. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		switch (choice) {
		case '1':
			AddItemPage(oic);
			break;
		case '2':
			UpdateStockPage(oic);
			break;
		case '3':
			SearchItemPage();
			break;
		case '4':
			RemoveItemPage(oic);
			break;
		}
	} while (choice != '#');
	system("cls");
}

void OICPage(const std::string &oic)
{
	char choice;

	system("cls");
	do {
		cout << "Welcome " << oic << endl;
		cout << "1 - Manage Team" << endl;
		cout << "2 - Manage Inventory" << endl;
		cout << "# - Logout" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '1' && choice != '2' && choice != '#') {
			cout << "Invalid choice. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		switch (choice) {
		case '1':
			TeamPage(oic);
			break;
		case '2':
			InventoryPage(oic);
			break;
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
	char choice;
	unordered_map<string, int> tries;

	initInMemoryDb();
	system("cls");
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
	commitInMemoryDb();
}

int main()
{
	MainPage();
	return 0;
}
