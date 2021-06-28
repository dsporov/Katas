#include "stdafx.h"

#include <assert.h>

namespace {
	static std::map<int, std::string> romanValues = {
		{    1, "I"  },
		{    4, "IV" },
		{    5, "V"  },
		{    9, "IX" },
		{   10, "X"  },
		{   40, "XL" },
		{   50, "L"  },
		{   90, "XC" },
		{  100, "C"  },
		{  400, "CD" },
		{  500, "D"  },
		{  900, "CM" },
		{ 1000, "M"  }
	};

	static std::map<char, int> intValues = {
		{'I',    1 },
		{'V',    5 },
		{'X',   10 },
		{'X',   40 },
		{'L',   50 },
		{'C',  100 },
		{'D',  500 },
		{'M', 1000 }
	};

	std::string intToRoman(int num) {
		std::string roman;

		for (auto it = romanValues.rbegin(); it != romanValues.rend(); it++) {
			while (num >= it->first) {
				num -= it->first;
				roman += it->second;

			}
		}

		return roman;
	}

	int romanToInt(std::string s) {
		int decimal = 0;
		for (size_t i = 0; i < s.length(); ++i) {
			int val = intValues[s[i]];
			
			if ((i < s.length() - 1) && (val < intValues[s[i + 1]])) {
				val = intValues[s[i + 1]] - val;
				++i;
			}

			decimal += val;
		}

		return decimal;
	}
}

void test_integer_to_roman() {
	assert(romanToInt("III") == 3);
	assert(romanToInt("IV") == 4);
	assert(romanToInt("VI") == 6);

	assert(romanToInt("IX") == 9);
	assert(romanToInt("LVIII") == 58);
	assert(romanToInt("MCMXCIV") == 1994);
	assert(romanToInt("") == 0);

}
