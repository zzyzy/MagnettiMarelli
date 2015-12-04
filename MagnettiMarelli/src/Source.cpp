#include <TeamController.h>
#include <iostream>

using namespace std;

int main()
{
	Team team = TeamController::getTeam("CITROEN TOTAL ABU DHABI WRT");
	cout << team.getName() << endl;
	cout << team.getCar() << endl;
	cout << team.getOic() << endl;
	cin.get();
	return 0;
}