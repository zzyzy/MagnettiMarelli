#pragma once

#include <unordered_map>

#include <SQLiteCpp/SQLiteCpp.h>

enum class RowStatus
{
	DEFAULT, CHANGED, NEW, REMOVED, IGNORED
};

template <class PKEY, class ROWTYPE>
class DAO
{
public:
	void insert(std::pair<PKEY, std::pair<ROWTYPE, RowStatus>> record)
	{
		table.insert(record);
	}

	typename std::unordered_map<PKEY, std::pair<ROWTYPE, RowStatus>>::iterator begin()
	{
		return table.begin();
	}

	typename std::unordered_map<PKEY, std::pair<ROWTYPE, RowStatus>>::iterator end()
	{
		return table.end();
	}

	typename std::unordered_map<PKEY, std::pair<ROWTYPE, RowStatus>>::iterator find(const PKEY &key)
	{
		return table.find(key);
	}

	size_t size() const
	{
		return table.size();
	}

	std::pair<ROWTYPE, RowStatus> &at(const PKEY &key)
	{
		return table.at(key);
	}

	virtual void saveTable() const;

protected:
	DAO() = delete;
	virtual ~DAO() = default;
	DAO(SQLite::Database &db)
	{ 
		this->db = &db;
	};

	virtual void loadTable() = 0;

	virtual void updateRow(const ROWTYPE &row) const = 0;
	virtual void addRow(const ROWTYPE &row) const = 0;
	virtual void deleteRow(const ROWTYPE &row) const = 0;

	std::unordered_map<PKEY, std::pair<ROWTYPE, RowStatus>> table;
	SQLite::Database *db;
};

template <class PKEY, class ROWTYPE>
void DAO<PKEY, ROWTYPE>::saveTable() const
{
	for (std::pair<PKEY, std::pair<ROWTYPE, RowStatus>> p : table) {
		if (p.second.second == RowStatus::CHANGED) {
			updateRow(p.second.first);
		}
		else if (p.second.second == RowStatus::NEW) {
			addRow(p.second.first);
		}
		else if (p.second.second == RowStatus::REMOVED) {
			deleteRow(p.second.first);
		}
	}
}
