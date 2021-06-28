#include "stdafx.h"

#include <assert.h>

static int reverse(int x) {
	long long res = 0;
	
	while (x != 0) {
		res = res * 10 + (x % 10);
		x = x / 10;

		if (res > std::numeric_limits<int>::max())
			return 0;
		if (res < std::numeric_limits<int>::min())
			return 0;
	}

	return res;
}

int reverse_leetcode(int x) {
	int rev = 0;
	while (x != 0) {
		int pop = x % 10;
		x /= 10;
		if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
		if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
		rev = rev * 10 + pop;
	}
	return rev;
}

void test_reverse_int() {
	assert(reverse(1463847412) == 2147483641);

	assert(reverse(1) == 1);
	assert(reverse(77) == 77);
	assert(reverse(12) == 21);

	assert(reverse(-123) == -321);
	assert(reverse(-12) == -21);

	assert(reverse(1534236469) == 0);
}
