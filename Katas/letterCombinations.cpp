#include "stdafx.h"

void letterCombinations(std::vector<std::string> &res, std::string digits) {
	static std::vector<char> mapping[] = {
		{'a', 'b', 'c'},
		{'d', 'e', 'f'},
		{'g', 'h', 'i'},
		{'j', 'k', 'l'},
		{'m', 'n', 'o'},
		{'p', 'q', 'r', 's'},
		{'t', 'u', 'v'},
		{'w', 'x', 'y', 'z'}
	};

	if (digits.empty())
		return;

	char digit = digits[0];
	std::vector<char> const& letters = mapping[digit - '2'];
	int count = res.size();
	
	std::vector<std::string> newRes;
	for (auto letter : letters) {
		for (size_t i = 0; i < count; ++i)
			newRes.push_back(res[i]+letter);
		if (count == 0)
			newRes.push_back(std::string(1, letter));
	}
	std::swap(res, newRes);

	letterCombinations(res, digits.substr(1));
}

std::vector<std::string> letterCombinations(std::string digits) {
	std::vector<std::string> res;

	letterCombinations(res, digits);

	return res;
}

void test_letterCombinations() {
	std::vector<std::string> res = letterCombinations("23");

	for (auto const& str : res) {
		std::cout << str << "\n";
	}
}