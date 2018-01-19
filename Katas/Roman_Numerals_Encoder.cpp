#include "stdafx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <deque>
#include <map>
#include <set>
#include <cctype>

#include <numeric>
#include <utility>

#include <assert.h>

/*
Roman Numerals Encoder

Create a function taking a positive integer as its parameter and returning a string containing the Roman Numeral representation of that integer.

Modern Roman numerals are written by expressing each digit separately starting with the left most digit and skipping any digit with a
value of zero. In Roman numerals 1990 is rendered: 1000=M, 900=CM, 90=XC; resulting in MCMXC.
2008 is written as 2000=MM, 8=VIII; or MMVIII.
1666 uses each Roman symbol in descending order: MDCLXVI.

Example:

solution(1000); // should return "M"
Help:

Symbol    Value
I          1
V          5
X          10
L          50
C          100
D          500
M          1,000
Remember that there can't be more than 3 identical symbols in a row.
*/

std::string solution(int number) {
	static std::map<int, std::string> romanNumbers = {
		{ 1, "I" },
		{ 4, "IV" },
		{ 5, "V" },
		{ 9, "IX" },
		{ 10, "X" },
		{ 40, "XL" },
		{ 50, "L" },
		{ 90, "XC" },
		{ 100, "C" },
		{ 400, "CD" },
		{ 500, "D" },
		{ 900, "CM" },
		{ 1000, "M" },
	};

	std::string roman;

	while (number > 0) {
		auto it = romanNumbers.lower_bound(number);
		if (it == romanNumbers.end())
			--it;
		if (it->first > number)
			--it;

		roman += it->second;
		number -= it->first;
	}

	return roman;
}

void test_roman_numerals_encoder() {
	for (int i = 1; i <= 20; ++i) {
		std::cout << solution(i) << "\n";
	}

	assert(solution(182) == "CLXXXII");
	assert(solution(1990) == "MCMXC");
	assert(solution(1875) == "MDCCCLXXV");
}
