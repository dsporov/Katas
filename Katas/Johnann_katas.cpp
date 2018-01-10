#include "stdafx.h"

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>

#include <numeric>

#include <assert.h>

/*

John and his wife Ann have decided to go to Codewars.

On day 0 Ann will do one kata and John - he wants to know how it is working - 0.

Let us call a(n) the number of katas done by Ann at day n we have a(0) = 1 and in the same manner j(0) = 0.

They have chosen the following rules:

On day n the number of katas done by Ann should be n minus the number of katas done by John at day t, t being equal to the number of katas done by Ann herself at day n - 1.
On day n the number of katas done by John should be n minus the number of katas done by Ann at day t, t being equal to the number of katas done by John himself at day n - 1.
Whoops! I think they need to lay out a little clearer exactly what there're getting themselves into!

Could you write:

1) two functions ann and john (parameter n) giving the list of the numbers of katas Ann and John should take on each day from day 0 to day n - 1 (n days - see first example below)?
2) The total number of katas taken by ann (function sum_ann(n)) and john (function sum_john(n)) from day 0 (inclusive) to day n (exclusive)?
Examples:

john(11) -->  [0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]
ann(6) -->  [1, 1, 2, 2, 3, 3]

sum_john(75) -->  1720
sum_ann(150) -->  6930
Shell Note:

sumJohnAndAnn has two parameters:

first one : n (number of days, $1)

second one : which($2) ->

1 for getting John's sum
2 for getting Ann's sum.
See "Sample Tests".

Note:

Keep an eye on performance.
*/

class Johnann
{
	static std::vector<long long> johnKatas;
	static std::vector<long long> annKatas;

	static long long johnKatasAtDay(long long n) {
		if (johnKatas.size() > n)
			return johnKatas[n];

		johnKatas.resize(n + 1);
		johnKatas[0] = 0;
		if (0 == n)
			return johnKatas[0];

		long long t = johnKatas[n - 1];
		johnKatas[n] = n - annKatasAtDay(t);
		return johnKatas[n];
	}

	static long long annKatasAtDay(long long n) {
		if (annKatas.size() > n)
			return annKatas[n];

		annKatas.resize(n + 1);
		annKatas[0] = 1;
		if (0 == n)
			return annKatas[0];

		long long t = annKatas[n - 1];
		annKatas[n] = n - johnKatasAtDay(t);
		return annKatas[n];
	}

	//static long long annKatasAtDay(long long n) {
	//	if (0 == n)
	//		return 1;

	//	long long t = annKatasAtDay(n-1);
	//	return n - johnKatasAtDay(t);
	//}

public:
	static std::vector<long long> john(long long n) {
		std::vector<long long> katas(n);

		for (long long i = 0; i < n; ++i) {
			katas[i] = johnKatasAtDay(i);
		}

		return katas;
	}

	static std::vector<long long> ann(long long n) {
		std::vector<long long> katas(n);

		for (long long i = 0; i < n; ++i) {
			katas[i] = annKatasAtDay(i);
		}

		return katas;
	}

	static long long sumJohn(long long n) {
		auto katas = john(n);
		return std::accumulate(katas.begin(), katas.end(), 0);
	}

	static long long sumAnn(long long n) {
		auto katas = ann(n);
		return std::accumulate(katas.begin(), katas.end(), 0);
	}
};

std::vector<long long> Johnann::johnKatas;
std::vector<long long> Johnann::annKatas;

void testSumAnn(long long ans, long long sol)
{
	assert(ans == sol);
}

void testSumJohn(long long ans, long long sol)
{
	assert(ans == sol);
}

void testann(std::vector<long long> ans, std::vector<long long> sol)
{
	assert(ans == sol);
}

void testjohn(std::vector<long long> ans, std::vector<long long> sol)
{
	assert(ans == sol);
}

/*
int main() {
	testSumAnn(Johnann::sumAnn(115), 4070);
	testSumJohn(Johnann::sumJohn(75), 1720);
	testann(Johnann::ann(6), { 1, 1, 2, 2, 3, 3 });
	testann(Johnann::john(11), { 0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6 });
}
*/
