#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>

#include <SQLiteCpp/SQLiteCpp.h>
#include <OICService.h>
#include <ItemService.h>
#include <TeamService.h>
#include <RequestService.h>

using namespace std;

#ifdef _DEBUG
SQLite::Database db(MAGNETTIDB, SQLITE_OPEN_READWRITE);
#else
SQLite::Database db("MagnettiMarelli.db", SQLITE_OPEN_READWRITE);
#endif

const int MAX_TRIES = 3;
const int WORKING_DAYS = 7;

OICDAO oicDao(db);
ItemDAO itemDao(db);
TeamDAO teamDao(db);
RequestDAO requestDao(db);
OICService oicService(oicDao);
ItemService itemService(itemDao);
TeamService teamService(teamDao);
RequestService requestService(requestDao);

void initInMemoryDb()
{
	cout << "Loading OIC table. . ." << endl;
	oicDao.loadTable();
	cout << "Loading OIC table. . . done!" << endl;
	cout << "Loading Item table. . ." << endl;
	itemDao.loadTable();
	cout << "Loading Item table. . . done!" << endl;
	cout << "Loading Team table. . ." << endl;
	teamDao.loadTable();
	cout << "Loading Team table. . . done!" << endl;
	cout << "Loading Request table. . ." << endl;
	requestDao.loadTable();
	cout << "Loading Request table. . . done!" << endl;
}

void commitInMemoryDb()
{
	cout << "Saving OIC table. . ." << endl;
	oicDao.saveTable();
	cout << "Saving OIC table. . . done!" << endl;
	cout << "Saving Item table. . ." << endl;
	itemDao.saveTable();
	cout << "Saving Item table. . . done!" << endl;
	cout << "Saving Team table" << endl;
	teamDao.saveTable();
	cout << "Saving Team table. . . done!" << endl;
	cout << "Saving Request table" << endl;
	requestDao.saveTable();
	cout << "Saving Request table. . . done!" << endl;
}

void showTeams(const unordered_map<int, Team> &teams)
{
	if (teams.empty()) { cout << "No managed teams" << endl; return; }
	for (pair<int, Team> p : teams) {
		cout << p.first << " - " << p.second.getName() << endl;
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

void TeamRequestPage(const Team &team)
{
	char choice;
	unordered_map<int, Request> requests;

	system("cls");
	do {
		cout << team.getName() << endl;
		requests = requestService.getRequestMap(team.getName(), Request::PENDING);
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

void TeamPage(const std::string &oic)
{
	char choice;
	unordered_map<int, Team> teams;

	system("cls");
	do {
		cout << "Team Request Management" << endl;
		teams = teamService.getTeamMap(oic);
		showTeams(teams);
		cout << "# - Back" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '#' && isdigit(choice) && teams.find(choice - '0') == teams.end()) {
			cout << "Invalid Team ID. Try again" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice != '#' && isdigit(choice)) {
			TeamRequestPage(teamService.fetchTeam(teams, choice - '0'));
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

void StockUpdateProcessPage(const Item &item)
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

void UpdateStockPage(const std::string &oic)
{
	char choice;
	unordered_map<int, Item> items;;

	system("cls");
	do {
		cout << "Update item" << endl;
		items = itemService.getItemMap(oic);
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
		cout << "===============================================================================" << endl;
		cout << "||                     Magnetti Marelli Management System                    ||" << endl;
		cout << "||___________________________________________________________________________||" << endl;
		cout << "||                          Inventory Management Page                        ||" << endl;
		cout << "===============================================================================" << endl;
		cout << "*" << endl;
		cout << "* 1 - Add Item" << endl;
		cout << "* 2 - Update Stock" << endl;
		cout << "* 3 - Search Item" << endl;
		cout << "* 4 - Remove Item" << endl;
		cout << "* # - Back" << endl;
		cout << "*" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '1' && choice != '2'
			&& choice != '3' && choice != '4' && choice != '#') {
			cout << "*" << endl;
			cout << "* Invalid choice. Try again" << endl;
			cout << "*" << endl;
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
		cout << "===============================================================================" << endl;
		cout << "||                     Magnetti Marelli Management System                    ||" << endl;
		cout << "||___________________________________________________________________________||" << endl;
		cout << "||                            Officer In Charge Page                         ||" << endl;
		cout << "===============================================================================" << endl;
		cout << "*" << endl;
		cout << "* Welcome, Officer " << oic << endl;
		cout << "*" << endl;
		cout << "* 1 - Manage Team" << endl;
		cout << "* 2 - Manage Inventory" << endl;
		cout << "* # - Logout" << endl;
		cout << "*" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '1' && choice != '2' && choice != '#') {
			cout << "*" << endl;
			cout << "* Invalid choice. Try again" << endl;
			cout << "*" << endl;
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

void OICLogin()
{
	std::string name;
	std::string password;

	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "*" << endl;
	cout << "* Enter OIC name" << endl;
	cout << "*" << endl;
	cout << "> "; getline(cin, name);
	if (oicService.verifyUsername(name)) {
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "*" << endl;
		cout << "* Enter OIC password" << endl;
		cout << "*" << endl;
		cout << "> "; getline(cin, password);
		if (oicService.verifyPassword(name, password, 3)) {
			OICPage(name);
		}
		else {
			cout << "*" << endl;
			cout << "* " << oicService.getLoginError() << endl;
			cout << "* ";
			system("pause");
			system("cls");
		}
	}
	else {
		cout << "*" << endl;
		cout << "* " << oicService.getLoginError() << endl;
		cout << "* ";
		system("pause");
		system("cls");
	}
}

void MainPage()
{
	char choice;

	initInMemoryDb();
	system("cls");
	do {
		cout << "===============================================================================" << endl;
		cout << "||                     Magnetti Marelli Management System                    ||" << endl;
		cout << "||___________________________________________________________________________||" << endl;
		cout << "||                                 Main Page                                 ||" << endl;
		cout << "===============================================================================" << endl;
		cout << "*" << endl;
		cout << "* Welcome to Magnetti Marelli Manager" << endl;
		cout << "*" << endl;
		cout << "* 1 - Login" << endl;
		cout << "* 2 - Quit" << endl;
		cout << "*" << endl;
		cout << "> "; cin >> choice; cin.ignore();
		while (choice != '1' && choice != '2') {
			cout << "*" << endl;
			cout << "* Invalid choice. Try again." << endl;
			cout << "*" << endl;
			cout << "> "; cin >> choice; cin.ignore();
		}

		if (choice == '1') {
			OICLogin();
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
