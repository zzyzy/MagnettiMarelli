#include <iostream>
#include <string>
#include <unordered_map>

#include <SQLiteCpp/SQLiteCpp.h>
#include <Item.h>
#include <Request.h>
#include <Utils.h>

using namespace std;

#ifdef _DEBUG
SQLite::Database db(MAGNETTIDB, SQLITE_OPEN_READWRITE);
#else
SQLite::Database db("MagnettiMarelli.db", SQLITE_OPEN_READWRITE);
#endif

const int MAX_TRIES = 3;

unordered_map<std::string, Item> itemTable;
unordered_map<std::string, Item> addItemTable;
unordered_map<std::string, Item> deleteItemTable;
unordered_map<int, Request> requestTable;

void loadItemTable()
{
	SQLite::Statement stmt(db, "SELECT * FROM Item");
	while (stmt.executeStep()) {
		Item item;
		item.setType(stmt.getColumn("Type").getText());
		item.setQuantity(stmt.getColumn("Quantity").getInt());
		item.setOic(stmt.getColumn("OIC").getText());
		itemTable.insert({ item.getType(), item });
	}
}

void saveItem(const Item &item)
{
	SQLite::Statement stmt(db, "UPDATE Item SET Quantity=?, OIC=? WHERE Type=?");
	stmt.bind(1, item.getQuantity());
	stmt.bind(2, item.getOic());
	stmt.bind(3, item.getType());
	stmt.exec();
}

void addItem(const Item &item)
{
	SQLite::Statement stmt(db, "INSERT INTO Item (Type, Quantity, OIC) VALUES (?, ?, ?)");
	stmt.bind(1, item.getType());
	stmt.bind(2, item.getQuantity());
	stmt.bind(3, item.getOic());
	stmt.exec();
}

void deleteItem(const Item &item)
{
	SQLite::Statement stmt(db, "DELETE FROM Item WHERE Type=?");
	stmt.bind(1, item.getType());
	stmt.exec();
}

void saveItemTable()
{
	for (pair<std::string, Item> p : itemTable) {
		saveItem(p.second);
	}
	
	if (!addItemTable.empty()) {
		for (pair<std::string, Item> p : addItemTable) {
			addItem(p.second);
		}
	}

	if (!deleteItemTable.empty()) {
		for (pair<std::string, Item> p : deleteItemTable) {
			deleteItem(p.second);
		}
	}
}

void loadRequestTable()
{
	SQLite::Statement stmt(db, "SELECT * FROM Request");
	while (stmt.executeStep()) {
		Request request;
		request.setId(stmt.getColumn("ID").getInt());
		request.setQuantity(stmt.getColumn("Quantity").getInt());
		request.setRequestDate(stmt.getColumn("Request Date").getText());
		request.setDeliveryDate(stmt.getColumn("Delivery Date").getText());
		request.setStatus(stmt.getColumn("Status").getText());
		request.setTeam(stmt.getColumn("Team").getText());
		request.setItem(stmt.getColumn("Item").getText());
		request.setOic(stmt.getColumn("OIC").getText());
		requestTable.insert({ request.getId(), request });
	}
}

void saveRequest(const Request &request)
{
	SQLite::Statement stmt(db, "UPDATE Request SET Quantity=?, \"Request Date\"=?, \
		\"Delivery Date\"=?, Status=?, Team=?, Item=?, OIC=? WHERE ID=?");
	stmt.bind(1, request.getQuantity());
	stmt.bind(2, request.getRequestDate());
	stmt.bind(3, request.getDeliveryDate());
	stmt.bind(4, request.getStatus());
	stmt.bind(5, request.getTeam());
	stmt.bind(6, request.getItem());
	stmt.bind(7, request.getOic());
	stmt.bind(8, request.getId());
	stmt.exec();
}

void saveRequestTable()
{
	for (pair<int, Request> p : requestTable) {
		saveRequest(p.second);
	}
}

void initInMemoryDb()
{
	loadItemTable();
	loadRequestTable();
}

void commitInMemoryDb()
{
	saveItemTable();
	saveRequestTable();
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

void showTeams(const unordered_map<int, string> &managedTeams)
{
	for (pair<int, string> p : managedTeams) {
		cout << p.first << " - " << p.second << endl;
	}
}

unordered_map<int, Request> fetchRequests(const std::string &team, const std::string &status)
{
	int i = 0;
	unordered_map<int, Request> requests;
	for (pair<int, Request> p : requestTable) {
		if (p.second.getTeam() == team && p.second.getStatus() == status) {
			requests.insert({ ++i, p.second });
		}
	}
	return requests;
}

void showRequests(const unordered_map<int, Request> &requests)
{
	for (pair<int, Request> p : requests) {
		cout << p.first << " - " << p.second.getTeam() << " - " << p.second.getItem() << " - " << p.second.getStatus() << endl;
	}
}

void approveRequest(Request &request)
{
	Item& item = itemTable.at(request.getItem());
	if (item.getQuantity() >= request.getQuantity()) {
		request.setStatus("Approved");
		item.deductQuantity(request.getQuantity());
	}
	else {
		cout << "Not enough stock to process request" << endl;
	}
}

void RequestProcessPage(Request &request)
{
	system("cls");
	char choice;

	cout << request.getTeam() << " - " << request.getItem() << endl;
	cout << "Y - Approve" << endl;
	cout << "N - Decline" << endl;
	cout << "> "; cin >> choice; cin.ignore();
	while (choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n') {
		cout << "Invalid choice. Try again" << endl;
		cout << "> "; cin >> choice; cin.ignore();
	}

	if (choice == 'y' || choice == 'Y') {
		approveRequest(request);
	}
	system("cls");
}

void TeamRequestPage(const string &name)
{
	system("cls");
	char choice;
	unordered_map<int, Request> requests;

	cout << name << endl;
	do {
		requests = fetchRequests(name, Request::PENDING);
		showRequests(requests);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && requests.find(choice - '0') == requests.end()) {
			cout << "Invalid Request ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			RequestProcessPage(requestTable.at(requests.at(choice - '0').getId()));
		}
	} while (choice != '#');
	system("cls");
}

void TeamPage(const std::string &name)
{
	system("cls");
	char choice;
	unordered_map<int, string> managedTeams;

	cout << "Welcome" << endl;
	do {
		managedTeams = fetchTeams(name);
		showTeams(managedTeams);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && managedTeams.find(choice - '0') == managedTeams.end()) {
			cout << "Invalid Team ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			TeamRequestPage(managedTeams.at(choice - '0'));
		}
	} while (choice != '#');
	system("cls");
}

unordered_map<int, Item> fetchItems(const std::string &name)
{
	int i = 0;
	unordered_map<int, Item> items;

	for (pair<string, Item> p : itemTable) {
		if (p.second.getOic() == name) {
			items.insert({ ++i, p.second });
		}
	}

	if (!addItemTable.empty()) {
		for (pair<string, Item> p : addItemTable) {
			if (p.second.getOic() == name) {
				items.insert({ ++i, p.second });
			}
		}
	}

	return items;
}

Item fetchLocalItem(const std::string &type)
{
	Item item;

	for (pair<string, Item> p : itemTable) {
		if (p.second.getType() == type) {
			item.setOic(p.second.getOic());
			item.setQuantity(p.second.getQuantity());
			item.setType(p.second.getType());
			break;
		}
	}

	if (!addItemTable.empty()) {
		for (pair<string, Item> p : addItemTable) {
			if (p.second.getType() == type) {
				item.setOic(p.second.getOic());
				item.setQuantity(p.second.getQuantity());
				item.setType(p.second.getType());
				break;
			}
		}
	}

	return item;
}

bool isItemExist(const std::string &type)
{
	for (pair<string, Item> p : itemTable) {
		if (p.second.getType() == type) {
			return true;
		}
	}

	if (!addItemTable.empty()) {
		for (pair<string, Item> p : addItemTable) {
			if (p.second.getType() == type) {
				return true;
			}
		}
	}

	return false;
}

bool isItemNew(const std::string &type)
{
	if (!addItemTable.empty()) {
		for (pair<string, Item> p : addItemTable) {
			if (p.second.getType() == type) {
				return true;
			}
		}
	}

	return false;
}

void showItems(const unordered_map<int, Item> &managedItems)
{
	for (pair<int, Item> p : managedItems) {
		cout << p.first << " - " << p.second.getType() << " - " << p.second.getQuantity() << " ea" << endl;
	}
}

void updateStock(Item &item, const int &quantity) {
	item.setQuantity(item.getQuantity() + quantity);
}

void addLocalItem(const std::string &type, const int &quantity, const std::string &name)
{
	Item item;
	item.setType(type);
	item.setQuantity(quantity);
	item.setOic(name);
	addItemTable.insert({ item.getType(), item });
}

void showItemDetails(const Item& item)
{
	cout << "Item type - " << item.getType() << endl;
	cout << "Quantity - " << item.getQuantity() << endl;
	cout << "In charge by - " << item.getOic() << endl;
}

void deleteLocalItem(const char &id, const std::string &type)
{
	Item item;
	item = fetchLocalItem(type);

	deleteItemTable.insert({ item.getType(), item });

	if (!isItemNew(type)) {
		itemTable.erase(type);
	}
	else {
		addItemTable.erase(type);
	}
}

void AddItemPage(const std::string &name)
{
	system("cls");
	std::string type;
	int quantity;

	cout << "Welcome" << endl;
	cout << "New item type (# to cancel)" << endl;
	cout << "> "; getline(cin, type);
	if (type != "#") {
		if (isItemExist(type)) {
			Item item = fetchLocalItem(type);
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
				addLocalItem(type, quantity, name);

				cout << "New item is added." << endl;
				system("pause");
			}
		}
	}
	system("cls");
}

void StockUpdateProcessPage(Item &item)
{
	system("cls");
	int quantity;

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
		updateStock(item, quantity);

		cout << "Quantity of item is updated." << endl;
		system("pause");
	}
	system("cls");
}

void UpdateStockPage(const std::string &name)
{
	system("cls");
	char choice;
	unordered_map<int, Item> managedItems;

	do {
		cout << "Welcome" << endl;
		managedItems = fetchItems(name);
		showItems(managedItems);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && managedItems.find(choice - '0') == managedItems.end()) {
			cout << "Invalid Item ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			StockUpdateProcessPage(itemTable.at(managedItems.at(choice - '0').getType()));
		}
	} while (choice != '#');
	system("cls");
}

void ItemDetailsPage(const std::string &type)
{
	system("cls");
	cout << "Welcome" << endl;
	if (isItemExist(type)) {
		showItemDetails(fetchLocalItem(type));
	}
	else {
		cout << "The item does not exist in the inventory." << endl;
	}
	system("pause");
	system("cls");
}

void SearchItemPage(const std::string &name)
{
	system("cls");
	std::string type;

	do {
		cout << "Welcome" << endl;
		cout << "Item type (# to back)" << endl;
		cout << "> "; getline(cin, type);
		if (type != "#") {
			ItemDetailsPage(type);
		}
	} while (type != "#");
	system("cls");
}

void ItemRemoveProcessPage(const char &id, const std::string &type)
{
	system("cls");
	char choice;

	cout << "Welcome";
	showItemDetails(fetchLocalItem(type));
	cout << "Are you sure to remove this item?" << endl;
	cout << "Y - Delete" << endl;
	cout << "N - Cancel" << endl;
	cout << "> "; cin >> choice; cin.ignore();
	while (choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n') {
		cout << "Invalid choice. Try again" << endl;
		cout << "> "; cin >> choice; cin.ignore();
	}

	if (choice == 'y' || choice == 'Y') {
		deleteLocalItem(id, type);

		cout << "Item is removed." << endl;
		system("pause");
	}

	system("cls");
}

void RemoveItemPage(const std::string &name)
{
	system("cls");
	char choice;
	unordered_map<int, Item> managedItems;

	do {
		cout << "Welcome" << endl;
		managedItems = fetchItems(name);
		showItems(managedItems);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && managedItems.find(choice - '0') == managedItems.end()) {
			cout << "Invalid Item ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			ItemRemoveProcessPage(choice, managedItems.at(choice - '0').getType());
		}
	} while (choice != '#');
	system("cls");
}

void InventoryPage(const std::string &name)
{
	system("cls");
	char choice;

	do {
		cout << "Welcome" << endl;
		cout << "1 - Add Item" << endl;
		cout << "2 - Update Stock" << endl;
		cout << "3 - Search Item" << endl;
		cout << "4 - Remove Item" << endl;
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '#') {
			cout << "Invalid Team ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#') {
			switch (choice) {
			case '1':
				AddItemPage(name);
				break;
			case '2':
				UpdateStockPage(name);
				break;
			case '3':
				SearchItemPage(name);
				break;
			case '4':
				RemoveItemPage(name);
				break;
			}
		}
	} while (choice != '#');
	system("cls");
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
				TeamPage(name);
				break;
			case '2':
				InventoryPage(name);
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

	initInMemoryDb();
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
	commitInMemoryDb();
	system("cls");
}

int main()
{
	MainPage();
	return 0;
}
