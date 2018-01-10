#include "stdafx.h"

#include <string>
#include <vector>
#include <algorithm>

#include <assert.h>

/*
Find the missing term in an Arithmetic Progression.

An Arithmetic Progression is defined as one in which there is a constant difference between the consecutive terms of a given series of numbers.
You are provided with consecutive elements of an Arithmetic Progression. There is however one hitch:
Exactly one term from the original series is missing from the set of numbers which have been given to you.
The rest of the given series is the same as the original AP. Find the missing term.

You have to write the function findMissing (list) , list will always be atleast 3 numbers. The missing term will never be the first or last one.

Example :

findMissing([1,3,5,9,11]) == 7
PS: This is a sample question of the facebook engeneer challange on interviewstreet. I found it quite fun to solve on paper using math , derive the algo that way. Have fun!
*/

static long findMissing(std::vector<long> list) {
	long step = (list.back() - list.front()) / static_cast<long>(list.size());

	int idx = list.size() / 2;
	int bound = list.size() / 2 / 2;
	for (;;) {
		long val = list.front() + idx * step;
		if (list[idx] == val) {
			idx += std::max(1, bound);
			bound /= 2;
			continue;
		}

		if ((list[idx] - list[idx - 1]) != step)
			return list[idx] - step;

		idx -= std::max(1, bound);
		bound /= 2;
	}
}

/*
int main() {
	auto res0 = findMissing({ -1, -5, -7 });

	auto res1 = findMissing({ 1, 3, 5, 9, 11 }); // 7
	auto res2 = findMissing({ 1, 3, 5, 7, 11 }); // 9
	auto res3 = findMissing({ 1, 5, 7, 9, 11 }); // 3
	auto res4 = findMissing({ 1, 3, 7, 9, 11 }); // 5
}
*/
