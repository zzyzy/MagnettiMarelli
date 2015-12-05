#include <RequestDAO.h>

void RequestDAO::loadTable()
{
	SQLite::Statement stmt(*db, "SELECT * FROM Request");
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
		table.insert({ request.getId(), {request, RowStatus::DEFAULT} });
	}
}

void RequestDAO::updateRow(const Request &request) const
{
	SQLite::Statement stmt(*db, "UPDATE Request SET Quantity=?, \"Request Date\"=?, \
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
