#include "SimpleDate.h"

void SimpleDate::now()
{
	std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
	time_t t = std::chrono::system_clock::to_time_t(p);

}

std::string SimpleDate::to_string() const
{
	return year + "/" + month + "/" + day;
}
