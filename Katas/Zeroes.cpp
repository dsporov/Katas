#include "stdafx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

#include <numeric>

#include <assert.h>

/*
The problem

How many zeroes are at the end of the factorial of 10? 10! = 3628800, i.e. there are 2 zeroes. 16! in hexadecimal would be 0x130777758000, which has 3 zeroes.

Scalability

Unfortunately, machine integer numbers has not enough precision for larger values. Floating point numbers drop the tail we need. We can fall back to arbitrary-precision ones -
built-ins or from a library, but calculating the full product isn't an efficient way to find just the tail of a factorial. Calculating 100'000! in compiled language takes around 10 seconds.
1'000'000! would be around 10 minutes, even using efficient Karatsuba algorithm

Your task

is to write a function, which will find the number of zeroes at the end of (number) factorial in arbitrary radix = base for larger numbers.

base is an integer from 2 to 256
number is an integer from 1 to 1'000'000
*/

using namespace std;

struct PrimeCount {
	int prime;
	int count;
};

vector<PrimeCount> primeFactorisation(int base) {
	int factor = 2;
	int count = 0;
	vector<PrimeCount> primeVector = vector<PrimeCount>();
	// cout << "Owww,,," << endl;
	while (true) {
		if (base % factor == 0) {
			base /= factor;
			// cout << "new base" << base << " -- from fact " << factor << endl;
			++count;
		}
		else {
			if (count != 0) {
				primeVector.push_back({ factor, count });
				// cout << "yess" << factor << " -- " << count << " [with base] " << base << endl;
				count = 0;
			}
			// cout << factor << " (the incremented factor)" << endl;
			if (++factor > base) {
				// cout << base << " (the base factor)" << endl;
				return primeVector;
			}
		}
	}
}

int powerPrimeInFactorial(int prime, int factorial) {
	if (factorial < prime) return 0;
	int power = factorial / prime;
	return power + powerPrimeInFactorial(prime, power);
}

int Zeroes_JasoonS(int base, int number)
{
	vector<PrimeCount> pfs = primeFactorisation(base);
	int numZeros = numeric_limits<int>::max();

	for (int i = 0; i < pfs.size(); ++i) {
		int power = powerPrimeInFactorial(pfs[i].prime, number);
		numZeros = min(power / pfs[i].count, numZeros);
	}
	return numZeros;
	// int f;
	// for (f = 1; number > 1; f *= number--);
	// int z = 0;
	// while (f % base == 0) {
	//     f /= base;
	//     z++;
	// }
	// return z;
}

/*
#include <cmath>
// fixme
int Zeroes(int base, int number)
{
int z = 0;
for (long long f = 1; number >= 1; f %= (int)std::pow(base, std::ceil(std::log(number) / std::log(base)) + 1), f *= number--)
while (f % base == 0)
{
f /= base;
z++;
}
return z;
}
*/

/*
// The answer we want (how many zeroes?) is equivalent to
// how many times the base can evenly divide into the factorial.
// That can be expressed in terms of prime factors.
// Factorials can also be analyzed in terms of prime factors.

// In fact, you can tell exactly how many of a prime factor is in
// a large factorial more easily than you can find its value, since
// you need only divide repeatedly to get the multiples, multiples of
// squares, of cubes, etc. of the given prime factor.

// Then you can use those counts to see how many of the base are in there.
// No need to look at every prime factor--just the ones in the base.
// This is done by dividing each of the counted primes by how many are in
// one factor of the base. e.g. 10! has eight factors of two, but only two
// factors of five, so 10 goes into 10! only twice. It might prove fruitful
// for a less generic function to see that there will always be more twos
// than fives in this case, but this *is* generic.

// we will need to prime-factorize a base <=256
std::vector<int> primes = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,
67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,
167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251 };

int Zeroes(int base, int number) {
// Prime-factorize the base.
std::map<int, int> base_factors;
for (int const &i : primes) {
while (base % i == 0) {
if (base_factors.count(i) == 0)
base_factors[i] = 1;
else ++base_factors[i];
base /= i;
}
if (i >= base) break;
}
#ifdef FACTORS_PRINTOUT
for (auto const &i : base_factors) {
for (int j = 0; j < i.second; ++j)
std::cout << i.first << ' ';
}
std::cout << std::endl;
#endif

// For each number that is a prime factor of base, find how many of it
// are factored into factorial. That is, find multiples of it,
// then of those find the multiples of its square, and so forth until
// no power of it could have been in the factorial.
std::map<int, int> factorial_factors;
for (auto const &i : base_factors) {
int factor = i.first,
multiples = number;
factorial_factors[factor] = 0;
while (multiples) {
multiples /= factor; // int math is important; throw out remainder!
factorial_factors[factor] += multiples;
}
}
#ifdef FACTORS_PRINTOUT
for (auto const &i : factorial_factors) {
for (int j = 0; j < i.second; ++j)
std::cout << i.first << ' ';
}
std::cout << std::endl;
#endif

// For each prime factor inspected, find how many bases could be
// constructed. The least of these -is- how many could be constructed.
int least = INT_MAX;
for (auto const &i : base_factors)
least = std::min(least, factorial_factors[i.first] / i.second);
return least;
}
*/

int Zeroes(int base, int number) {
	int z = 0;

	long long val = 1;

	int base2 = base;
	while (base2 < number)
		base2 = base2 * base;

	for (int i = 2; i <= number; ++i) {
		val = val * i;

		while (val % base == 0) {
			++z;
			val = val / base;
		}

		val = val % base2;
	}

	return z;
}


void test_Zeroes() {
	auto nn1 = Zeroes_JasoonS(10, 100);
	auto n_test1 = Zeroes(10, 1000000);
	auto n_test2 = Zeroes(10, 100);

	auto n2 = Zeroes(10, 2);
	auto n5 = Zeroes(10, 5);
	auto n10 = Zeroes(10, 10);
	auto n16 = Zeroes(16, 16);
}
