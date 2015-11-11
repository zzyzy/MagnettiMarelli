#include <Utils.h>

std::string Utils::caesar(std::string input)
{
	std::string temp;

	for (char c : input) {
		if (isalpha(c))
		{
			c = toupper(c);
			c = (((c - 65) + 13) % 26) + 65;
		}

		temp += c;
	}

	return temp;
}