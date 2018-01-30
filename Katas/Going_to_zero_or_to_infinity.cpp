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
#include <memory>

#include <numeric>
#include <utility>

#include <assert.h>

/*
Going to zero or to infinity?

Consider the following numbers (where n! is factorial(n)):

u1 = (1 / 1!) * (1!)
u2 = (1 / 2!) * (1! + 2!)
u3 = (1 / 3!) * (1! + 2! + 3!)
un = (1 / n!) * (1! + 2! + 3! + ... + n!)
Which will win: 1 / n! or (1! + 2! + 3! + ... + n!)?

Are these numbers going to 0 because of 1/n! or to infinity due to the sum of factorials?

Task
Calculate (1 / n!) * (1! + 2! + 3! + ... + n!) for a given n, where n is an integer greater or equal to 1.

To avoid discussions about rounding, return the result truncated to 6 decimal places, for example:

1.0000989217538616 will be truncated to 1.000098
1.2125000000000001 will be truncated to 1.2125
Remark
Keep in mind that factorials grow rather rapidly, and you need to handle large inputs.
*/

class Suite {
public:
	static double going(int n) {
		double res = 1.0;

		double f = n;
		for (int i = n - 1; i > 0; --i) {
			res += 1.0 / f;
			f = f * i;
		}

		res = std::floor(res * 1000000.0) / 1000000.0;
		return res;
	}
};


void test_Going_to_zero_or_to_infinity() {
	std::cout << Suite::going(5) << " = " << 1.275 << "\n";
	std::cout << Suite::going(6) << " = " << 1.2125 << "\n";
	std::cout << Suite::going(7) << " = " << 1.173214 << "\n";
	std::cout << Suite::going(8) << " = " << 1.146651 << "\n";

	assert(Suite::going(5) == 1.275);
	assert(Suite::going(6) == 1.2125);
	assert(Suite::going(7) == 1.173214);
	assert(Suite::going(8) == 1.146651);
}
