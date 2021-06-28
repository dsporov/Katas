#include "stdafx.h"

std::vector<std::vector<int>> threeSum(std::vector<int> &nums) {
	std::vector<std::vector<int>> res;

	if (nums.size() < 3)
		return res;

	std::sort(nums.begin(), nums.end());

	for (size_t i = 0; i < nums.size() - 2; ++i) {
		int v1 = nums[i];
		if (i > 0 && v1 == nums[i - 1])
			continue;
		if (v1 > 0)
			break;

		size_t j = nums.size();
		while (--j > i) {
			int v3 = nums[j];
			if (j < nums.size()-1 && v3 == nums[j + 1])
				continue;
			if (v3 < 0)
				break;

			int v2 = -(v1 + v3);

			bool exists = std::binary_search(std::begin(nums) + i + 1, std::begin(nums) + j, v2);
			if (exists)
				res.push_back({v1, v2, v3});
		}
	}

	return res;
}


void test_3_sum() {
	std::vector<int> test3 = { 0, 0, 0, 0 };
	auto v3 = threeSum(test3);

	std::vector<int> test1 = { -1,0,1,2,-1,-4 };
	auto v1 = threeSum(test1);

	std::vector<int> test2 = { 0, 0, 0 };
	auto v2 = threeSum(test2);

}
