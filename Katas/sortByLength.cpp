#include "stdafx.h"

#include <string>
#include <vector>
#include <algorithm>

class Kata
{
public:
	std::vector<std::string> sortByLength(std::vector<std::string> array)
	{
		std::sort(array.begin(), array.end(), [](std::string const& s1, std::string const& s2) { return s1.size() < s2.size(); });
		/*
		qsort(&array[0], array.size(), sizeof(array.front()), [](const void *el1, const void *el2) {
		auto len1 = static_cast<const std::string*>(el1)->length();
		auto len2 = static_cast<const std::string*>(el2)->length();

		if (len1 < len2)
		return -1;
		if (len1 > len2)
		return 1;
		return 0;
		});*/

		return array;
	}
};

/*
int main() {
	Kata kata;
	auto re1 = kata.sortByLength({ "Telescopes", "Glasses", "Eyes", "Monocles" });
	return 0;
}
*/
