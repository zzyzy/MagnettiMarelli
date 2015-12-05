#pragma once

#include <string>
#include <chrono>
#include <ctime>

class SimpleDate
{
public:
	SimpleDate() = default;
	~SimpleDate() = default;

	void now();
	std::string to_string() const;

private:
	std::string year;
	std::string month;
	std::string day;
};
