#include "stdafx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <deque>

#include <numeric>

#include <assert.h>

/*
A Chain adding function

We want to create a function that will add numbers together when called in succession.

add(1)(2);
// returns 3
We also want to be able to continue to add numbers to our chain.

add(1)(2)(3); // 6
add(1)(2)(3)(4); // 10
add(1)(2)(3)(4)(5); // 15
and so on.

A single call should return the number passed in.

add(1); // 1
We should be able to store the returned values and reuse them.

var addTwo = add(2);
addTwo; // 2
addTwo + 5; // 7
addTwo(3); // 5
addTwo(3)(5); // 10
We can assume any number being passed in will be valid whole number.
*/

class Add {
public:
	Add(int n) : m_val(n) {}

	operator int() const {
		return m_val;
	}

	Add operator()(int val) const {
		return Add(m_val + val);
	}

	// does not compile on codewars without this operator
	inline friend std::ostream& operator<<(std::ostream &os, Add const& add) {
		os << (int)add;
		return os;
	}

private:
	int m_val;
};

auto add(int n) {
	return Add(n);
}

void test_chain_adding_function() {
	auto addTwo = add(2);
	auto x = addTwo + 5;
	std::cout << x;

	std::cout << "add(1)(2)(3) " << "== " << add(1)(2)(3) << " == 6\n";

	assert(add(1) == 1);
	assert(add(1)(2) == 3);
	assert(add(1)(2)(3) == 6);
}

