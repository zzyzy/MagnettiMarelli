#include <Utils.h>

std::string Utils::caesar(std::string input)
{
	std::string temp;

	for (char c : input) {
		if (isalpha(c)) {
			if (isupper(c)) {
				//converting capitalized chars
				c = (((c - 65) + 13) % 26) + 65;
			}
			else {
				//converting small chars
				c = (((c - 97) + 13) % 26) + 97;
			}
		}

		temp += c;
	}

	return temp;
}