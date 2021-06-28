#include "stdafx.h"

#include <assert.h>

namespace{
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        std::set<char> subBoxes[3][3];
        std::set<char> rows[9];
        std::set<char> cols[9];

        int r = 0, c = 0;
        for (auto const& row : board) {
            c = 0;
            for (auto const& col : row) {
                char val = col;
                if (val < '0' || val > '9') {
                    ++c;
                    continue;
                }

                if (rows[r].find(val) != rows[r].end())
                    return false;
                if (cols[c].find(val) != cols[c].end())
                    return false;
                if (subBoxes[r/3][c/3].find(val) != subBoxes[r/3][c/3].end())
                    return false;

                rows[r].insert(val);
                cols[c].insert(val);
                subBoxes[r/3][c/3].insert(val);

                ++c;
            }
            ++r;
        }

        return true;
    }
}

void test_isValidSudoku() {
    std::vector<std::vector<char>> board1 = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'},
    };
    assert(isValidSudoku(board1));


    std::vector<std::vector<char>> board2 = {
         {'8','3','.','.','7','.','.','.','.'}
        ,{'6','.','.','1','9','5','.','.','.'}
        ,{'.','9','8','.','.','.','.','6','.'}
        ,{'8','.','.','.','6','.','.','.','3'}
        ,{'4','.','.','8','.','3','.','.','1'}
        ,{'7','.','.','.','2','.','.','.','6'}
        ,{'.','6','.','.','.','.','2','8','.'}
        ,{'.','.','.','4','1','9','.','.','5'}
        ,{'.','.','.','.','8','.','.','7','9'}
    };
    assert(!isValidSudoku(board2));
}
