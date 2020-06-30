//Description
//Given an array X of positive integers, its elements are to be transformed by running the following operation on them as many times as required:
//
//if X[i] > X[j] then X[i] = X[i] - X[j]
//
//When no more transformations are possible, return its sum ("smallest possible sum").
//
//For instance, the successive transformation of the elements of input X = [6, 9, 21] is detailed below:
//
//X_1 = [6, 9, 12] # -> X_1[2] = X[2] - X[1] = 21 - 9
//X_2 = [6, 9, 6]  # -> X_2[2] = X_1[2] - X_1[0] = 12 - 6
//X_3 = [6, 3, 6]  # -> X_3[1] = X_2[1] - X_2[0] = 9 - 6
//X_4 = [6, 3, 3]  # -> X_4[2] = X_3[2] - X_3[1] = 6 - 3
//X_5 = [3, 3, 3]  # -> X_5[1] = X_4[0] - X_4[1] = 6 - 3
//The returning output is the sum of the final transformation (here 9).
//
//Example
//solution([6, 9, 21]) #-> 9
//Solution steps:
//[6, 9, 12] #-> X[2] = 21 - 9
//[6, 9, 6] #-> X[2] = 12 - 6
//[6, 3, 6] #-> X[1] = 9 - 6
//[6, 3, 3] #-> X[2] = 6 - 3
//[3, 3, 3] #-> X[1] = 6 - 3
//Additional notes:
//There are performance tests consisted of very big numbers and arrays of size at least 30000. Please write an efficient algorithm to prevent timeout.

#include <cassert>

#include <vector>
#include <algorithm>
#include <numeric>

unsigned long long solution_correct_but_slow(const std::vector<unsigned long long>& arr){
    std::vector<unsigned long long> x(arr);

    bool wereSubstr;
    do {
        wereSubstr = false;
        for (size_t i = 0; i < x.size(); ++i) {
            for (size_t j = 0; j < x.size(); ++j) {
                if (x[i] > x[j]) {
                    x[i] = x[i] - x[j];
                    wereSubstr = true;
                }
            }
        }
    } while(wereSubstr);

    return std::accumulate(x.begin(), x.end(), 0);
}

// todo: use GCD
unsigned long long solution(const std::vector<unsigned long long>& arr){
    if (arr.empty())
        return 0;

    std::vector<unsigned long long> x(arr);

    bool wereSubstr;
    do {
        wereSubstr = false;

        unsigned long long minEl = *std::min_element(x.begin(), x.end());

        for (unsigned long long &el : x) {
            if (el == minEl)
                continue;

            el = (el % minEl);
            if (el == 0)
                el = minEl;
            wereSubstr = true;
        }
    } while(wereSubstr);

    return std::accumulate(x.begin(), x.end(), 0ULL);
}

void test_smallest_possible_sum() {
    assert(solution_correct_but_slow({3,13,23,7,83}) == 5);
    assert(solution({3,13,23,7,83}) == 5);


    assert(solution({1,21,55}) == 3);
    assert(solution({3,13,23,7,83}) == 5);
    assert(solution({4,16,24}) == 12);
    assert(solution({30,12}) == 12);
    assert(solution({60,12,96,48,60,24,72,36,72,72,48}) == 132);
    assert(solution({71,71,71,71,71,71,71,71,71,71,71,71,71}) == 923);
    assert(solution({11,22}) == 22);
    assert(solution({9}) == 9);
    assert(solution({1}) == 1);
    assert(solution({9, 9}) == 18);
}
