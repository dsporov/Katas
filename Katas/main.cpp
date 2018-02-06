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
k-Primes

A natural number is called k-prime if it has exactly k prime factors, counted with multiplicity.

A natural number is thus prime if and only if it is 1-prime.

Examples:
k = 2 -> 4, 6, 9, 10, 14, 15, 21, 22, …
k = 3 -> 8, 12, 18, 20, 27, 28, 30, …
k = 5 -> 32, 48, 72, 80, 108, 112, …
#Task:

Write function count_Kprimes (or countKprimes or count-K-primes or kPrimes in C) which given parameters k, start, end (or nd) returns an array 
    (or a list in C) of the k-primes between start (inclusive) and end (inclusive).
#Example:

countKprimes(5, 500, 600) --> [500, 520, 552, 567, 588, 592, 594]
...............................................................................

for all languages except Bash shell
Given positive integers s and a, b, c where a is 1-prime, b 3-prime, c 7-prime find the number of solutions of a + b + c = s. Call this function puzzle(s).

Examples:

puzzle(138) --> 1 ([2 + 8 + 128] is solution)
puzzle(143) --> 2 ([3 + 12 + 128, 7 + 8 + 128] are solutions)
...............................................................................

Notes:

The first function would have been better named: findKprimes or kPrimes :-)

In C some helper functions are given (see declarations in 'Solution').

For Go: nil slice is expected when there are no k-primes between start and end.
*/

class KPrimes {
public:

	static std::vector<long long> calcPrimes2(long long v) {
		if (v < 2)
			return {};

		std::vector<long long> primes = { 2 };

		for (long long i = 3; i <= v; i += 2) {
			bool isPrime = true;

			for (long long prime : primes) {
				isPrime = (i % prime) != 0;
				if (!isPrime)
					break;
			}

			if (isPrime)
				primes.push_back(i);
		}

		return primes;
	}

	static std::vector<long long> calcPrimes(long long v) {
		std::vector<bool> A(v+1, true);

		int v_sqrt = std::sqrt(v);

		for (long long i = 2; i <= v_sqrt; ++i) {
			if (!A[i])
				continue;

			for (long long j = 0; j <= v; ++j) {
				auto idx = i * i + j * i;
				if (idx > v)
					break;
				A[idx] = false;
			}
		}

		std::vector<long long> primes;
		for (long long i = 2; i <= v; ++i) {
			if (A[i])
				primes.push_back(i);
		}
		return primes;
	}

	static std::vector<long long> getNextPrimeLevel(std::vector<long long> const& primes, std::vector<long long> &values, long long end) {
		std::set<long long> nextValues;

		for (auto prime : primes) {
			for (auto v : values) {
				if (v * prime > end)
					break;
				nextValues.insert(v * prime);
			}
		}

		values.clear();
		std::copy(nextValues.begin(), nextValues.end(), std::back_inserter(values));
		return values;
	}

	static std::vector<long long> countKprimes(int k, long long start, long long end) {
		auto primes = calcPrimes(end / k);

		std::vector<long long> values = primes;

		while (--k > 0) {
			getNextPrimeLevel(primes, values, end);
		}

		auto itStart = std::lower_bound(values.begin(), values.end(), start);
		std::vector<long long> res(itStart, values.end());

		return res;
	}

	static int puzzle(int s) {
		std::vector<long long> primes1 = calcPrimes(s);

		std::vector<long long> primes3 = primes1;
		getNextPrimeLevel(primes1, primes3, s);
		getNextPrimeLevel(primes1, primes3, s);

		std::vector<long long> primes7 = primes3;
		getNextPrimeLevel(primes1, primes7, s);
		getNextPrimeLevel(primes1, primes7, s);
		getNextPrimeLevel(primes1, primes7, s);
		getNextPrimeLevel(primes1, primes7, s);

		int count = 0;

		for (auto prime1 : primes1) {
			if (prime1 >= s)
				break;
			for (auto prime3 : primes3) {
				if (prime1 + prime3 >= s)
					break;

				for (auto prime7 : primes7) {
					long long val = prime1 + prime3 + prime7;
					if (val == s)
						++count;
					if (val >= s)
						break;
				}
			}
		}

		return count;
	}
};

int main() {
	{
		PerfMeasure perfMeas("test");
		KPrimes::calcPrimes(4000000);

		//KPrimes::countKprimes(2, 7263891-1, 7265780+1);
		KPrimes::puzzle(10000000);
	}


	{
		std::vector<long long> sol = { 4,6,9,10,14,15,21,22,25,26,33,34,35,38,39,46,49,51,55,57,58,62,65,69,74,77,82,85,86,87,91,93,94,95 };
		assert(KPrimes::countKprimes(2, 0, 100) == sol);

		sol = { 8, 12, 18, 20, 27, 28, 30, 42, 44, 45, 50, 52, 63, 66, 68, 70, 75, 76, 78, 92, 98, 99 };
		assert(KPrimes::countKprimes(3, 0, 100) == sol);

		sol = { 500, 520, 552, 567, 588, 592, 594 };
		assert(KPrimes::countKprimes(5, 500, 600) == sol);
	}

	{
		assert(KPrimes::puzzle(138) == 1);
		assert(KPrimes::puzzle(143) == 2);
		assert(KPrimes::puzzle(250) == 7);
	}
}
