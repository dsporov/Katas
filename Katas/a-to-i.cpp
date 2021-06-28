#include "stdafx.h"

#include <assert.h>

static int myAtoi(std::string s) {
	int i = 0;
	while (s[i] == ' ') ++i;

	int sign = 1;
	if (s[i] == '-') {
		sign = -1;
		++i;
	} else if (s[i] == '+') {
		++i;
	}

	long long res = 0;
	while (s[i] >= '0' && s[i] <= '9') {
		res = res * 10 + static_cast<int>(s[i] - '0');
		++i;

		if ((res*sign) >= std::numeric_limits<int>::max())
			return std::numeric_limits<int>::max();
		if ((res*sign) <= std::numeric_limits<int>::min())
			return std::numeric_limits<int>::min();
	}

	return res * sign;
}

int myAtoi_leetcode(std::string str) {
	int i = 0;
	int sign = 1;
	int result = 0;
	if (str.length() == 0) return 0;

	//Discard whitespaces in the beginning
	while (i < str.length() && str[i] == ' ')
		i++;

	// Check if optional sign if it exists
	if (i < str.length() && (str[i] == '+' || str[i] == '-'))
		sign = (str[i++] == '-') ? -1 : 1;

	// Build the result and check for overflow/underflow condition
	while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
		if (result > INT_MAX / 10 ||
			(result == INT_MAX / 10 && str[i] - '0' > INT_MAX % 10)) {
			return (sign == 1) ? INT_MAX : INT_MIN;
		}
		result = result * 10 + (str[i++] - '0');
	}
	return result * sign;
}

void test_atoi() {
	assert(myAtoi("") == 0);

	assert(myAtoi("-0") == 0);
	assert(myAtoi("+0") == 0);

	assert(myAtoi("+11") == 11);
	assert(myAtoi("-11") == -11);
}
