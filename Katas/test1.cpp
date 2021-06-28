#include "stdafx.h"
#include <assert.h>

#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef std::vector<std::string> ReplacedWords;

void insertString(ReplacedWords& wordsWithQmReplaced, std::string part, std::string next) {
    if (next.empty()) {
        wordsWithQmReplaced.push_back(part);
        return;
    }

    for (int i = 0; i < next.length(); ++i) {
        if (next[i] == '?') {
            insertString(wordsWithQmReplaced, part + '0', next.substr(i + 1));
            insertString(wordsWithQmReplaced, part + '1', next.substr(i + 1));

            return;
        }

        part += next[i];
    }

    wordsWithQmReplaced.push_back(part);
}


ReplacedWords replaceQuestionMarks(std::string word) {
    ReplacedWords wordsWithQmReplaced;

    insertString(wordsWithQmReplaced, "", word);


    //std::string part;
    //for (int i = 0; i < word.length(); ++i) {
    //    if (word[i] == '?') {
    //        insertString(wordsWithQmReplaced, part + '0', word.substr(i + 1));
    //        insertString(wordsWithQmReplaced, part + '1', word.substr(i + 1));
    //        part.clear();
    //        break;
    //    }

    //    part += word[i];
    //}

    //if (!part.empty()) {
    //    wordsWithQmReplaced.push_back(part);
    //}

    return wordsWithQmReplaced;
}

bool equalVectors(ReplacedWords const& words1, ReplacedWords const& words2) {
    if (words1.size() != words2.size())
        return false;

    for (size_t i = 0; i < words1.size(); ++i) {
        if (words1[i] != words2[i])
            return false;
    }

    return true;
}

// To execute C++, please define "int main()"
void test_replaceQuestionMarks() {
    auto res1 = replaceQuestionMarks("00");
    assert(equalVectors(res1, {"00"}));

    auto res2 = replaceQuestionMarks("?00");
    assert(equalVectors(res2, { "000", "100" }));

    auto res3 = replaceQuestionMarks("00?");
    assert(equalVectors(res3, { "000", "001" }));

    auto res4 = replaceQuestionMarks("?0?1");
    assert(equalVectors(res4, { "0001", "0011", "1001", "1011" }));

    auto res5 = replaceQuestionMarks("?0?1?");
    assert(equalVectors(res5, { "00010", "00011", "00110", "00111", "10010", "10011", "10110", "10111" }));


    auto res6 = replaceQuestionMarks("?0?1?00");
    assert(equalVectors(res6, { "0001000", "0001100", "0011000", "0011100", "1001000", "1001100", "1011000", "1011100" }));
}


// I have a string like "?0?1" -> ? = 0 or 1.
// "?0?1" = ["0001", "0011", .. ]

// "?0?1" -> {0, 2} list of ? positions
// "?0?1" -> ["0001", "1001", "0011", "1011"]

// replaceQmarks: "?0?1" -> ["0"+replaceQmarks("0?1"), "1"+ replaceQmarks("0?1")]

