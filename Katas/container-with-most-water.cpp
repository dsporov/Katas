#include "stdafx.h"

#include <assert.h>

namespace {
    int calcArea(std::vector<int> const& height, size_t i, size_t j) {
        int x_len = static_cast<int>(j > i ? (j - i) : i - j);
        return x_len * std::min(height[i], height[j]);
    }

    int maxArea_n2(std::vector<int> const& height) {
        int maxArea = 0;

        for (size_t i = 0; i < height.size(); ++i) {
            for (size_t j = i + 1; j < height.size(); ++j)
            {
                maxArea = std::max(maxArea, calcArea(height, i, j));
            }
        }

        return maxArea;
    }

    int maxArea(std::vector<int> const& height) {
        if (height.size() < 2)
            return 0;

        int maxArea = 0;

        int i = 0; int j = height.size() - 1;

        while (i < j) {
            int area = calcArea(height, i, j);

            if (maxArea < area) {
                maxArea = area;
            }

            if (height[i] < height[j]) {
                ++i;
            }
            else {
                --j;
            }
        }

        return maxArea;
    }


    int maxArea_sorted(std::vector<int> const& height) {
        if (height.size() < 2)
            return 0;

        std::multimap<int, int> sortedHeight;
        for (size_t i = 0; i < height.size(); ++i) {
            sortedHeight.insert(std::pair<int, int>(height[i], i));
        }

        auto max1 = sortedHeight.rbegin();
        auto max2 = max1; ++max2;
        int maxArea = calcArea(height, max1->second, max2->second);

        auto it = max2; ++it;
        for (; it != sortedHeight.rend(); ++it) {
            int area1 = calcArea(height, max1->second, it->second);
            int area2 = calcArea(height, max2->second, it->second);

            if (area1 <= maxArea && area2 <= maxArea)
                continue;

            if (area1 > area2) {
                maxArea = area1;
                max1 = it; 
            }

            if (area1 <= area2) {
                maxArea = area2;
                max2 = it;
            }
        }

        return maxArea;
    }
}

void test_container_with_most_water() {
    assert(maxArea({ 1,2,3,4,5,6,7,8,9,10 }) == 25);

    assert(maxArea({ 1, 2, 4, 3 }) == 4);

    assert(maxArea({}) == 0);
    assert(maxArea({1}) == 0);
    
    assert(maxArea({ 1, 1 }) == 1);
    assert(maxArea({ 1, 2 }) == 1);

    assert(maxArea({ 1, 2, 1 }) == 2);

    assert(maxArea({ 1,8,6,2,5,4,8,3,7 }) == 49);
    assert(maxArea({ 4,3,2,1,4 }) == 16);
}
