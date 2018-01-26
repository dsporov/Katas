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
Number of Proper Fractions with Denominator d

Caution: This kata does not currently have any known supported versions for C++.
It may not be completable due to dependencies on out-dated libraries/language versions.

If n is the numerator and d the denominator of a fraction, that fraction is defined a (reduced) proper fraction if and only if GCD(n,d)==1.

For example 5/16 is a proper fraction, while 6/16 is not, as both 6 and 16 are divisible by 2, thus the fraction can be reduced to 3/8.

Now, if you consider a given number d, how many proper fractions can be built using d as a denominator?

For example, let's assume that d is 15:
you can build a total of 8 different proper fractions between 0 and 1 with it:
1/15, 2/15, 4/15, 7/15, 8/15, 11/15, 13/15 and 14/15.

You are to build a function that computes how many proper fractions you can build with a given denominator:

proper_fractions(1)==0
proper_fractions(2)==1
proper_fractions(5)==4
proper_fractions(15)==8
proper_fractions(25)==20
Be ready to handle big numbers.

Edit: to be extra precise, the term should be "reduced" fractions, thanks to girianshiido for pointing this out and sorry for the use
of an improper word :)
*/

void calcPrimeNumbers(long n, long *primeNumbers, long *numPrimeNumbers) {
	long isPrime = false;

	*numPrimeNumbers = 0;
	primeNumbers[(*numPrimeNumbers)++] = 2;
	primeNumbers[(*numPrimeNumbers)++] = 3;

	for (long i = 5; i < n; i += 2) {
		isPrime = true;
		for (long j = 0; j < *numPrimeNumbers; ++j) {
			if (i % primeNumbers[j] == 0) {
				isPrime = false;
				break;
			}
		}

		if (isPrime)
			primeNumbers[(*numPrimeNumbers)++] = i;
	}
}

long gcd(long a, long b) {
	//	return b == 0 ? a : gcd(b, a % b);

	while (b != 0) {
		unsigned r = a % b;
		a = b;
		b = r;
	}

	return a;
}

long properFractions(long n) {
	int numPropFracts = 0;
	if (n > 1)
		++numPropFracts;

	//if (n % 2 != 0) {
	//	numPropFracts += log(n) / log(2);
	//}

	for (long i = 3; i < n; i += 2) {
		if ((n % i) == 0)
			continue;
		//if ((i % 2) == 0)
		//	continue;

		if (gcd(n, i) == 1)
			++numPropFracts;
	}

	return numPropFracts;
}

void test_Number_of_Proper_Fractions_with_Denominator_d() {
	PerfMeasure perfMeasure("Test");
	//	std::cout << properFractions(9999999) << "\n";

	gcd(15, 6);
	std::cout << properFractions(15) << "\n";

	assert(properFractions(1) == 0);
	assert(properFractions(2) == 1);
	assert(properFractions(5) == 4);
	assert(properFractions(15) == 8);
	assert(properFractions(25) == 20);
}
