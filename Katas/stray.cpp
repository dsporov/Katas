#include "stdafx.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <vector>

int stray1(const std::vector<int>& numbers) {
	return std::accumulate(numbers.begin(), numbers.end(), 0, std::bit_xor<>());
}

int stray2(const std::vector<int>& numbers) {
	auto pos = std::mismatch(numbers.begin(), numbers.end(), numbers.begin() + numbers.size() / 2);
	return *pos.second == numbers[0] ? *pos.first : *pos.second;
}

int stray(std::vector<int> numbers) {
	if (numbers[0] != numbers[1]) {
		if (numbers[2] == numbers[0])
			return numbers[1];
		return numbers[0];
	}

	size_t i = 2;
	while (numbers[i] == numbers[i - 1]) ++i;
	return numbers[i];
};

/*
auto n1 = stray({ 1, 1, 2 });
auto n2 = stray({ 2, 1, 1 });
auto n3 = stray({ 1, 2, 1 });
auto n4 = stray({ 17, 17, 3, 17, 17, 17, 17 });
*/