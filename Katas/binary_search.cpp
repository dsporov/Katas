#include "stdafx.h"

#include <assert.h>

namespace {
    std::vector<int> searchRange(std::vector<int> const& nums, int target) {
        std::vector<int> result = {-1, -1};

        if (nums.empty())
            return result;

        int first = 0;
        int end = nums.size() - 1;

        while (first <= end) {
            int middle = first + (end - first) / 2;

            if (nums[middle] == target) {
                int range_start = middle;
                while ((range_start > 0) && (nums[range_start-1] == target))
                    --range_start;
                
                int range_end = middle;
                while (((range_end+1) < nums.size()) && (nums[range_end + 1] == target))
                    ++range_end;

                return { range_start,  range_end };
            }

            if (target > nums[middle]) {
                first = middle + 1;
            }
            else {
                end = middle - 1;
            }
        };

        return result;
    }
}

void test_binary_search() {
    auto res11 = searchRange({ 5, 7, 7, 8, 8, 10 }, 8);
    auto res12 = searchRange({ 5, 7, 7, 8, 8, 10 }, 5);
    auto res13 = searchRange({ 5, 7, 7, 8, 8, 10 }, 10);

    auto res21 = searchRange({ 5, 7, 7, 8, 8, 10 }, 6);
    auto res22 = searchRange({ 5, 7, 7, 8, 8, 10 }, 3);
    auto res23 = searchRange({ 5, 7, 7, 8, 8, 10 }, 11);
}
