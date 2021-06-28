#include "stdafx.h"

#include <assert.h>

namespace {
    using Matrix = std::vector<std::vector<int>>;

    void rotate(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();

        int idx_start = 0;
        int idx_end = n - 1;

        while (idx_start < idx_end) {
            for (int col = 0; col < idx_end - idx_start; ++col) {
                int& val1 = matrix[idx_start][idx_start+col];
                int& val2 = matrix[idx_start + col][idx_end];
                int& val3 = matrix[idx_end][idx_end - col];
                int& val4 = matrix[idx_end - col][idx_start];

                int val0 = val4;

                val4 = val3;
                val3 = val2;
                val2 = val1;
                val1 = val0;
            }

            ++idx_start;
            --idx_end;
        }
    }

    bool isEqual(Matrix const& m1, Matrix const& m2) {
        if (m1.size() != m2.size())
            return false;

        for (int i = 0; i < m1.size(); ++i) {
            if (m1[i].size() != m2[i].size())
                return false;

            for (int j = 0; j < m1[i].size(); ++j) {
                if (m1[i][j] != m2[i][j])
                    return false;
            }
        }

        return true;
    }

}

void test_rotate_matrix() {
    std::vector<std::vector<int>> matrix3 = { {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16} };
    std::vector<std::vector<int>> result3 = { {15, 13, 2, 5}, {14, 3, 4, 1}, {12, 6, 8, 9}, {16, 7, 10, 11} };
    rotate(matrix3);
    assert(isEqual(matrix3, result3));

    std::vector<std::vector<int>> matrix1 = { {1, 2}, {3, 4} };
    std::vector<std::vector<int>> result1 = { {3, 1}, {4, 2} };
    rotate(matrix1);
    assert(isEqual(matrix1, result1));

    std::vector<std::vector<int>> matrix2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<int>> result2 = {{7, 4, 1}, {8, 5, 2}, {9, 6, 3}};
    rotate(matrix2);
    assert(isEqual(matrix2, result2));
}
