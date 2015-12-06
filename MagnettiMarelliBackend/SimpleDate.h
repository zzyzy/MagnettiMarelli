#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

class SimpleDateException;

class SimpleDate
{
public:
	SimpleDate() = default;
	~SimpleDate() = default;
	SimpleDate(const unsigned int &year, const unsigned int &month, const unsigned int &day);

	void now();
	void addDay(const unsigned int &day);
	bool isLeapYear() const;

	std::string toString() const;
	friend std::ostream &operator<<(std::ostream& out, const SimpleDate &simpleDate);

	unsigned int getYear() const { return year; }
	unsigned int getMonth() const { return month; }
	unsigned int getDay() const { return day; }

private:
	unsigned int year;
	unsigned int month;
	unsigned int day;
	const unsigned int daysInMonths[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
};

class SimpleDateException : public std::runtime_error
{
public:
	SimpleDateException(const std::string &what_arg) : runtime_error(what_arg) {  };
	~SimpleDateException() = default;
};
