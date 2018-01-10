#include "stdafx.h"

#include <string>
#include <vector>
#include <algorithm>

#include <assert.h>

/*
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Finish the solution so that it returns the sum of all the multiples of 3 or 5 below the number passed in.

Note: If the number is a multiple of both 3 and 5, only count it once.
Courtesy of ProjectEuler.net

*/

int solution(int number) {

	int sum = 0;

	--number;

	int numOf3 = number / 3;
	int sumOf3 = 3 * numOf3 * (numOf3 + 1) / 2;

	int numOf5 = number / 5;
	int sumOf5 = 5 * numOf5 * (numOf5 + 1) / 2;

	int numOf15 = number / 15;
	int sumOf15 = 15 * numOf15 * (numOf15 + 1) / 2;

	sum = sumOf3 + sumOf5 - sumOf15;
	/*
	for (int i = 3; i < number; ++i) {
	if (i % 3 == 0)
	sum += i;
	else if (i % 5 == 0)
	sum += i;
	}*/

	return sum;
}

/*
int main() {
	int res1 = solution(10);
}
*/
