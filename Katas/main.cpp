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
Large Factorials

In mathematics, the factorial of integer n is written as n!.
It is equal to the product of n and every integer preceding it. For example: 5! = 1 x 2 x 3 x 4 x 5 = 120

Your mission is simple: write a function that takes an integer n and returns the value of n!.

You are guaranteed an integer argument.
For any values outside the non-negative range, return null, nil or None (return an empty string "" in C and C++).
For non-negative numbers a full length number is expected for example, return 25! = "15511210043330985984000000" as a string.

For more on factorials, see http://en.wikipedia.org/wiki/Factorial
*/

std::string factorial1(int factorial) {
	int a[200]; //array will have the capacity to store 200 digits.
	int n, i, j, temp, m, x;

	n = factorial;
	a[0] = 1;  //initializes array with only 1 digit, the digit 1.
	m = 1;    // initializes digit counter

	temp = 0; //Initializes carry variable to 0.
	for (i = 1; i <= n; i++)
	{
		for (j = 0; j<m; j++)
		{
			x = a[j] * i + temp; //x contains the digit by digit product
			a[j] = x % 10; //Contains the digit to store in position j
			temp = x / 10; //Contains the carry value that will be stored on later indexes
		}
		while (temp>0) //while loop that will store the carry value on array.
		{
			a[m] = temp % 10;
			temp = temp / 10;
			m++; // increments digit counter
		}
	}

	std::string str;
	for (i = m - 1; i >= 0; i--) //printing answer
		str += '0' + a[i];

	return str;
}

std::string factorial(int factorial) {
	std::vector<char> digits(200);

	digits[0] = 1;
	size_t len = 1;

	int carry = 0;
	for (int i = 2; i <= factorial; ++i) {
		// multiply currrent value by i
		for (int j = 0; j < len; ++j) {
			int val = digits[j] * i + carry;
			digits[j] = val % 10;
			carry = val / 10;
		}

		while (carry > 0) {
			// length increased
			if (len >= digits.size())
				digits.resize(len * 2);

			digits[len++] = carry % 10;
			carry = carry / 10;
		}
	}

	std::string str(len, 0);
	for (int i = 0; i < len; ++i)
		str[i] = '0' + digits[len - i - 1];
	return str;
}


int main() {
	std::cout << factorial(6) << "\n";
}
