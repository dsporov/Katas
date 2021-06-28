#include "stdafx.h"

#include <string>
#include <assert.h>
#include <vector>

#include <algorithm>

/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);


Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:
Input: s = "A", numRows = 1
Output: "A"


Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000
*/

class Solution {
public:
    std::string convert(std::string s, int numRows) {
        if (numRows <= 1)
            return s;

        std::string result;

        int numCols = s.length();
            //+ ((s.length() % numRows) == 0 ? 0 : 1);

        std::vector<std::string> zigZag(numRows);
        for (int i = 0; i < numRows; ++i) {
            zigZag[i] = std::string(numCols, ' ');
        }

        const int lastRowIdx = numRows - 1;
        int zigZagIdx = lastRowIdx - 1;

        int colIdx = 0;
        int rowIdx = 0;
        bool isZigZagCol = false;
        for (int i = 0; i < s.length(); ++i) {
            
            if (isZigZagCol) {
                zigZag[zigZagIdx][colIdx] = s[i];
                --zigZagIdx;
                if (0 == zigZagIdx) {
                    zigZagIdx = lastRowIdx - 1;
                    isZigZagCol = false;
                }
                ++colIdx;
                rowIdx = 0;
                continue;
            }

            zigZag[rowIdx][colIdx] = s[i];
            ++rowIdx;
            if (rowIdx >= numRows) {
                rowIdx = 0;
                ++colIdx;
                isZigZagCol = (numRows > 2);
            }
        }

        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                if (zigZag[i][j] != ' ')
                    result += zigZag[i][j];
                std::cout << zigZag[i][j];
            }
            std::cout << '\n';
        }
        std::cout << "\n\n";


        //size_t startIdx = 0;
        //while (startIdx < numRows) {
        //    for (size_t i = startIdx; i < s.length(); i += numRows) {
        //        result += s[i];
        //    }
        //    ++startIdx;
        //}

        return result;
    }

    // leetcode 1
    std::string convert_1(std::string s, int numRows) {

        if (numRows == 1) return s;

        std::vector<std::string> rows(std::min(numRows, int(s.size())));
        int curRow = 0;
        bool goingDown = false;

        for (char c : s) {
            rows[curRow] += c;
            if (curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        std::string ret;
        for (std::string row : rows) ret += row;
        return ret;
    }

    // leetcode 2
    std::string convert_2(std::string s, int numRows) {

        if (numRows == 1) return s;

        std::string ret;
        int n = s.size();
        int cycleLen = 2 * numRows - 2;

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j + i < n; j += cycleLen) {
                ret += s[j + i];
                if (i != 0 && i != numRows - 1 && j + cycleLen - i < n)
                    ret += s[j + cycleLen - i];
            }
        }
        return ret;
    }
};

void test_zigZag_conversion() {
    Solution solution;

    assert(solution.convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
    assert(solution.convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
    assert(solution.convert("A", 1) == "A");

    assert(solution.convert("AB", 1) == "AB");
    assert(solution.convert("ABCD", 2) == "ACBD");
}