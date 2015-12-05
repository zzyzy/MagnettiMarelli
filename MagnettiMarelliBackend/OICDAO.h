#pragma once

#include <DAO.h>
#include <OIC.h>

class OICDAO : public DAO<std::string, OIC>
{
public:
	OICDAO() = delete;
	~OICDAO() = default;
	OICDAO(SQLite::Database &db) : DAO(db) {  };

	void loadTable() override;

private:
	void updateRow(const OIC &oic) const override;
	void addRow(const OIC& oic) const override { throw std::runtime_error("Not yet implemented"); };
	void deleteRow(const OIC &oic) const override { throw std::runtime_error("Not yet implemented"); };
};
