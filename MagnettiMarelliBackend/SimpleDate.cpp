#include <SimpleDate.h>

SimpleDate::SimpleDate(const unsigned int &year, const unsigned int &month, const unsigned int &day)
{
	if (year < 1900 || year > 9999)
		throw SimpleDateException("Year out of range");
	else if (month < 1 || month > 12)
		throw SimpleDateException("Month out of range");
	else if (day < 1 || day > 31)
		throw SimpleDateException("Day out of range");
	this->year = year;
	this->month = month;
	this->day = day;
}

void SimpleDate::now()
{
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(p);
#ifdef _WIN32
	tm timeinfo;
	localtime_s(&timeinfo, &t);
	year = 1900 + timeinfo.tm_year;
	month = 1 + timeinfo.tm_mon;
	day = timeinfo.tm_mday;
#else
	tm *timeinfo = localtime(&t);
	year = std::to_string(1900 + timeinfo->tm_year);
	month = std::to_string(1 + timeinfo->tm_mon);
	day = std::to_string(timeinfo->tm_mday);
#endif
}

void SimpleDate::addDay(const unsigned int &day)
{
	this->day += day;
	while (this->day > daysInMonths[month - 1]) {
		if (month == 2 && isLeapYear()) {
			this->day -= daysInMonths[month - 1] + 1;
		}
		else {
			this->day -= daysInMonths[month - 1];
		}
		month += 1;
		if (month > 12) {
			month -= 12;
			year += 1;
		}
	}
}

bool SimpleDate::isLeapYear() const
{
	if (year % 4 != 0) return false;
	if (year % 400 == 0) return true;
	if (year % 100 == 0) return false;
	return true;
}

std::string SimpleDate::toString() const
{
	std::string simpleDate;
	simpleDate += std::to_string(year) + "/";
	if (std::to_string(month).length() < 2) simpleDate += "0";
	simpleDate += std::to_string(month) + "/";
	if (std::to_string(day).length() < 2) simpleDate += "0";
	simpleDate += std::to_string(day);
	return simpleDate;
}

std::ostream& operator<<(std::ostream& out, const SimpleDate &simpleDate)
{
	out << simpleDate.toString();
	return out;
}
