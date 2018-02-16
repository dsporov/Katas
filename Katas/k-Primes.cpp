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

class KPrimes_my {
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

	static std::set<long long> calcPrimes(long long v) {
		std::vector<bool> A(v + 1, true);

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

		std::set<long long> primes;
		for (long long i = 2; i <= v; ++i) {
			if (A[i])
				primes.insert(i);
		}
		return primes;
	}

	static std::set<long long> getNextPrimeLevel(std::set<long long> const& primes, std::set<long long> &values, long long end) {
		std::set<long long> nextValues;

		for (auto prime : primes) {
			for (auto v : values) {
				if (v * prime > end)
					break;
				nextValues.insert(v * prime);
			}
		}

		return nextValues;
	}

	static std::vector<long long> countKprimes(int k, long long start, long long end) {
		auto primes = calcPrimes(end / k);

		std::set<long long> values = primes;

		while (--k > 0) {
			values = getNextPrimeLevel(primes, values, end);
		}

		auto itStart = std::lower_bound(values.begin(), values.end(), start);
		std::vector<long long> res(itStart, values.end());

		return res;
	}

	static int puzzle(int s) {
		std::vector<long long> primes1 = countKprimes(1, 0, s);
		std::vector<long long> primes3 = countKprimes(3, 0, s);
		std::vector<long long> primes7 = countKprimes(7, 0, s);
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

class KPrimes
{
public:
	static std::vector<long long> countKprimes(int k, long long start, long long end) {
		std::vector<long long> kPrimes;
		for (long long i = start; i <= end; i++)
		{
			if (countPrimeFactors(i) == k)
				kPrimes.push_back(i);
		}
		return kPrimes;
	}

	static int puzzle(int s) {
		int sums = 0;
		//s - 10 being the largest possible sum of a 1- and 3-prime number - 2 + 8
		for (int i = 128; i <= s - 10; i++) //a fanatic could make this code more efficient by improving on the i++
		{
			if (countPrimeFactors(i) == 7)
			{
				int b = s - i; //b is the largest possible sum of b and c
				for (int j = 8; j <= b - 2; j++) //8 being the smallest 3-prime number
				{
					if (countPrimeFactors(j) == 3)
					{
						int a = b - j; //a being the only possible value for the 1-prime number (with i and j as they are)
						if (countPrimeFactors(a) == 1)
							sums++; //the code has reached here (through the checks for 7, 3 and 1 prime numbers) thus i, j and a are the three numbers and there is another solution
					}
				}
			}
		}
		return sums;
	} //laugh at all the closing braces if you want

private:
	static int countPrimeFactors(long long n) {
		if (n == 0)
			return 0;
		int factors = 0;
		long long fac = 2;
		while (n != 1)
		{
			while ((n % fac) != 0)
			{
				if (fac > sqrt(n))
					fac = n; //the square root is the largest possible factor (prime or not) - thus n is 1 prime if this hits
							 //thanks to stack exchange for the square root check hint
							 //this check is mainly to eliminate those annoying 1-prime numbers which would make this code too slow
				else if (fac == 2)
					fac = 3;  //the only time you don't add 2
				else
					fac += 2; //since there are no prime numbers that are even the prime factors jump in increments of 2 (with gaps)
			}
			factors++;
			n = n / fac;
		}
		return factors;
	}
};

void test_k_primes() {
	//{
	//	PerfMeasure perfMeas("my test");

	//	//KPrimes_my::countKprimes(10, 0, 1000000);
	//	KPrimes_my::puzzle(10000);
	//}

	//{
	//	PerfMeasure perfMeas("codewars test");

	//	//KPrimes::countKprimes(10, 0, 1000000);
	//	KPrimes::puzzle(1000000);
	//}

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
