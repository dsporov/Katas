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
Count ones in a segment

Given two numbers: 'left' and 'right' (1 <= 'left' <= 'right' <= 200 000 000 000 000)
return sum of all '1' occurencies in binary representations of numbers between 'left' and 'right' (including both)

Example:
countOnes 4 7 should return 8, because:
0(dec) = 000(bin)
1(dec) = 001(bin)

2(dec) = 010(bin)
3(dec) = 011(bin)

4(dec) = 100(bin), which adds 1 to the result.
5(dec) = 101(bin), which adds 2 to the result.
6(dec) = 110(bin), which adds 2 to the result.
7(dec) = 111(bin), which adds 3 to the result.

8(dec) = 1000(bin)
9(dec) = 1001(bin)
10(dec) = 1010(bin)
11(dec) = 1011(bin)
12(dec) = 1100(bin)
13(dec) = 1101(bin)
14(dec) = 1110(bin)
15(dec) = 1111(bin)

So finally result equals 8.
WARNING: Segment may contain billion elements, to pass this kata, your solution cannot iterate through all numbers in the segment!

RightLessThanMilionTests
Expected: equal to 916107
Actual: 193303
Actual: 289384

SmallSegmentsTests
Expected: equal to 6676768
Actual: 476744280
Actual: 477171088

SmallRandomSegments
Expected: equal to 1377702
Actual: 14092
Actual: 747567


RightLessThanBilionTests
Expected: equal to 3131546184
Actual: 4250829
Actual: 231192380


OneBilionElementsSegment
Expected: equal to 14846928141
Actual: 1
Actual: 1000000000


RandomSegments
Expected: equal to 1722425418
Actual: 310658700
Actual: 414747567
*/

long long getBitsCount(int n) {
	long long bitsCount = 0;

	while (n) {
		bitsCount += n % 2;
		n >>= 1;
	}

	return bitsCount;
}

long long countOnesStraight(int left, int right) {
	long long count = 0;

	for (int i = left; i <= right; ++i) {
		count += getBitsCount(i);
	}

	return count;
}

template<long long i>
long long setBitsSumCount() {
	return (1 << (i - 1)) + 2 * setBitsSumCount<i - 1>();
	//return (i * pow(2, i-1));
}

template<> long long setBitsSumCount<1>() { return 1; }

static long long powCounts[] = { 0, 1, 4,
setBitsSumCount<3>() + 1, setBitsSumCount<4>() + 1, setBitsSumCount<5>() + 1, setBitsSumCount<6>() + 1, setBitsSumCount<7>() + 1,
setBitsSumCount<8>() + 1, setBitsSumCount<9>() + 1, setBitsSumCount<10>() + 1, setBitsSumCount<11>() + 1, setBitsSumCount<12>() + 1,
setBitsSumCount<13>() + 1, setBitsSumCount<14>() + 1, setBitsSumCount<15>() + 1, setBitsSumCount<16>() + 1, setBitsSumCount<17>() + 1,
setBitsSumCount<18>() + 1, setBitsSumCount<19>() + 1, setBitsSumCount<20>() + 1, setBitsSumCount<21>() + 1, setBitsSumCount<22>() + 1,
setBitsSumCount<23>() + 1, setBitsSumCount<24>() + 1, setBitsSumCount<25>() + 1, setBitsSumCount<26>() + 1, setBitsSumCount<27>() + 1,
setBitsSumCount<28>() + 1, setBitsSumCount<29>() + 1, setBitsSumCount<30>() + 1, setBitsSumCount<31>() + 1, setBitsSumCount<32>() + 1,
};

int leftmostBit(int n) {
	int left = 0;
	while (n > 1) {
		n = n >> 1;
		++left;
	}

	return left;
}

int nextLeftmostBit(int n, int left) {
	int val = 1 << left;
	while (n < val) {
		val = val >> 1;
		--left;
	}

	return left;
}

long long countSetBits(int n, int left);

long long countSetBits(int n) {
	int left = leftmostBit(n);

	// Use the position
	return countSetBits(n, left);
}

long long countSetBits(int n, int left) {
	if (0 == n)
		return 0;

	left = nextLeftmostBit(n, left);

	// if n is power of 2 minus 1 (i.g. all bits are set in a row from 0 to leftmost) then 1-bits count is equal to pow2 * 2^(pow2-1)
	bool isPower2minus1 = (n == (1 << (left + 1)) - 1);
	if (isPower2minus1)
		return (left + 1) * ((long long)1 << left);

	// else devide bitwise repesentation of all numbers before n into 4 parts:
	// find leftmost bit that is set and ignore all zeroes before it; 

	// part1|part2
	// ___________
	// part3| part4

	// part1 = all 0
	// res = part3 + part4 + part2
	// part3 = all ones = n - (1 << leftmostBit) + 1
	// part2 = case when n is power of 2 minus 1 = pow2 * 2^(pow2-1)
	// part4 = unset leftmostBit and recursive call

	// e.g. n = 6
	// 0|0 0
	// 0|0 1
	// 0|1 0
	// 0|1 1
	// -|––
	// 1|0 0
	// 1|0 1
	// 1|1 0

	// set off bit 'left'
	n = n - (1 << left);

	return (n + 1) + countSetBits(n) + left * ((long long)1 << (left - 1));
}

long long countOnes(int left, int right) {
	return countSetBits(right) - countSetBits(left - 1);
}

long long countOnesFromZeroTo(int n) {
	long long res = 0;
	for (int i = std::numeric_limits<int>::digits - 1; i >= 0; i--) {
		int b = 1 << i;
		if (n & b)
			res += static_cast<long long>(i) * (b >> 1) + (n & (b - 1)) + 1;
	}
	return res;
}

long long countOnes_usingZeroToN(int left, int right) {
	return countOnesFromZeroTo(right) - countOnesFromZeroTo(left - 1);
}



long long countOnes(int n) {
	if (0 == n)
		return 0;

	int n2pow = static_cast<int>(log(n) / log(2));
	int nDecr = 1 << n2pow;

	long long count = powCounts[n2pow];
	count += countOnesStraight(nDecr + 1, n);
	return count;
}

long long countOnes2(int left, int right) {
	if ((right - left) / (double)right < 0.25)
		return countOnesStraight(left, right);

	return countOnes(right) - countOnes(left - 1);
}

long long countOnes1(int left, int right) {
	int left2pow = static_cast<int>(log(left) / log(2));
	int right2pow = static_cast<int>(log(right) / log(2));

	int leftDecr = 1 << left2pow;
	int rightDecr = 1 << right2pow;

	//if ((right - left) < (left - leftDecr + right - rightDecr)) {
	//	return countOnesStraight(left, right);
	//}

	long long count = (powCounts[right2pow] + countOnesStraight(rightDecr + 1, right))
		- (powCounts[left2pow] + countOnesStraight(leftDecr + 1, left - 1))
		//+ getBitsCount(left)
		;

	return count;
}

void test_Count_ones_in_a_segment() {
	PerfMeasure perfMeasure("Test");

	countSetBits(6);

	long long tests[][3] = {
		{ 193303, 289384, 916107 },
	{ 476744280, 477171088, 6676768 },
	{ 14092, 747567, 7058000 },
	{ 4250829, 231192380, 3131546184 },
	{ 1, 1000000000, 14846928141 },
	{ 310658700, 414747567, 1540903068 }
	};

	for (size_t i = 0; i < _countof(tests); ++i) {
		long long res = countOnes(tests[i][0], tests[i][1]);
		if (res != tests[i][2])
			std::cout << res << " != " << tests[i][2] << " => failed!\n";
		else
			std::cout << res << " passed\n";
	}

	assert(countOnes(4, 7) == 8);

	/*
	for (size_t i = 1; i < 8; ++i) {
	int r = 1 << (i - 1);
	std::cout << i << " (" << r << ")";
	std::cout << " = " << countOnes(0, r) << "\n";
	}
	*/
}
