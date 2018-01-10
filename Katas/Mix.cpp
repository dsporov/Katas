#include "stdafx.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <deque>
#include <map>
#include <set>
#include <cctype>

#include <numeric>

#include <assert.h>


/*
Given two strings s1 and s2, we want to visualize how different the two strings are. We will only take into account the lowercase letters (a to z).
First let us count the frequency of each lowercase letters in s1 and s2.

s1 = "A aaaa bb c"

s2 = "& aaa bbb c d"

s1 has 4 'a', 2 'b', 1 'c'

s2 has 3 'a', 3 'b', 1 'c', 1 'd'

So the maximum for 'a' in s1 and s2 is 4 from s1; the maximum for 'b' is 3 from s2. In the following we will not consider letters when the maximum of their occurrences is less than or equal to 1.

We can resume the differences between s1 and s2 in the following string: "1:aaaa/2:bbb" where 1 in 1:aaaa stands for string s1 and aaaa because the maximum for a is 4.
In the same manner 2:bbb stands for string s2 and bbb because the maximum for b is 3.

The task is to produce a string in which each lowercase letters of s1 or s2 appears as many times as its maximum if this maximum is strictly greater than 1; these letters will be prefixed
by the number of the string where they appear with their maximum value and :. If the maximum is in s1 as well as in s2 the prefix is =:.

In the result, substrings (a substring is for example 2:nnnnn or 1:hhh; it contains the prefix) will be in decreasing order of their length and when they have the same length sorted in
ascending lexicographic order (letters and digits - more precisely sorted by codepoint); the different groups will be separated by '/'. See examples and "Example Tests".

Hopefully other examples can make this clearer.

s1 = "my&friend&Paul has heavy hats! &"
s2 = "my friend John has many many friends &"
mix(s1, s2) --> "2:nnnnn/1:aaaa/1:hhh/2:mmm/2:yyy/2:dd/2:ff/2:ii/2:rr/=:ee/=:ss"

s1 = "mmmmm m nnnnn y&friend&Paul has heavy hats! &"
s2 = "my frie n d Joh n has ma n y ma n y frie n ds n&"
mix(s1, s2) --> "1:mmmmmm/=:nnnnnn/1:aaaa/1:hhh/2:yyy/2:dd/2:ff/2:ii/2:rr/=:ee/=:ss"

s1="Are the kids at home? aaaaa fffff"
s2="Yes they are here! aaaaa fffff"
mix(s1, s2) --> "=:aaaaaa/2:eeeee/=:fffff/1:tt/2:rr/=:hh"
*/

class Mix {
public:
	static std::string mix(const std::string &s1, const std::string &s2) {
		CharsFreqs charsFreqs1;
		calcCharsFreqs(s1, charsFreqs1);

		CharsFreqs charsFreqs2;
		calcCharsFreqs(s2, charsFreqs2);

		FreqsChars freqsChars;
		for (auto p : charsFreqs1) {
			if (p.second <= 1)
				continue;

			char ch = p.first;
			if (charsFreqs2[ch] > p.second)
				continue;

			freqsChars[p.second].ch1.insert(p.first);
		}

		for (auto p : charsFreqs2) {
			if (p.second <= 1)
				continue;

			char ch = p.first;
			if (charsFreqs1[ch] > p.second)
				continue;

			freqsChars[p.second].ch2.insert(p.first);
		}

		std::string res;

		for (auto it = std::rbegin(freqsChars); it != std::rend(freqsChars); ++it) {
			Chars &c1 = it->second.ch1;
			Chars &c2 = it->second.ch2;

			std::vector<std::string> s2;
			std::vector<std::string> sEq;

			while (!c1.empty() || !c2.empty()) {
				int numStr = 0;
				char ch;
				if (c1.empty()) {
					ch = *c2.begin();
					c2.erase(c2.begin());
					numStr = 2;
				}
				else if (c2.empty()) {
					ch = *c1.begin();
					c1.erase(c1.begin());
					numStr = 1;
				}
				else {
					if (*c2.begin() > *c1.begin()) {
						ch = *c1.begin();
						c1.erase(c1.begin());
						numStr = 1;
					}
					else if (*c2.begin() < *c1.begin()) {
						ch = *c2.begin();
						c2.erase(c2.begin());
						numStr = 2;
					}
					else {
						ch = *c1.begin();
						c1.erase(c1.begin());
						c2.erase(c2.begin());
					}
				}

				std::string s = numStr > 0 ? std::to_string(numStr) : "=";
				s += ":";
				s += std::string(it->first, ch);

				if (0 == numStr)
					sEq.push_back(s);
				if (2 == numStr)
					s2.push_back(s);
				if (1 == numStr) {
					if (!res.empty())
						res += "/";
					res += s;
				}
			}

			for (auto const& s : s2) {
				if (!res.empty())
					res += "/";
				res += s;
			}

			for (auto const& s : sEq) {
				if (!res.empty())
					res += "/";
				res += s;
			}
		}

		return res;
	}

private:
	typedef std::map<char, size_t> CharsFreqs;
	typedef std::set<char> Chars;

	struct FreqChars {
		Chars ch1;
		Chars ch2;
	};
	typedef std::map<size_t, FreqChars> FreqsChars;

	static void calcCharsFreqs(std::string const& s, CharsFreqs &charsFreqs) {
		for (char ch : s) {
			if (std::islower(ch))
				++charsFreqs[ch];
		}
	}
};

class Mix1
{
private:
	static bool compare(const std::string &s1, const std::string &s2);
	static std::vector<std::string> split(const std::string &s);
	static std::string join(const std::vector<std::string>& vec);
public:
	static std::string mix(const std::string &s1, const std::string &s2);
};

bool Mix1::compare(const std::string &s1, const std::string &s2)
{
	int w1 = s1.length(); int w2 = s2.length();
	if (w1 == w2) return s1 < s2;
	return w1 > w2;
}

std::vector<std::string> Mix1::split(const std::string &s)
{
	std::vector<std::string> out;
	std::istringstream ss(s);
	std::string next;
	while (std::getline(ss, next, '/'))
		out.push_back(next);
	return out;
}
std::string Mix1::join(const std::vector<std::string>& vec)
{
	std::string s = "";
	for (unsigned int i = 0; i < vec.size(); i++)
		if (i < vec.size() - 1) s += vec[i] + "/";
		else s += vec[i];
		return s;
}

std::string Mix1::mix(const std::string &s1, const std::string &s2)
{
	std::vector<int> alpha1(26);
	for (unsigned int i = 0; i < alpha1.size(); i++) alpha1[i] = 0;
	std::vector<int> alpha2(26);
	for (unsigned int i = 0; i < alpha1.size(); i++) alpha2[i] = 0;
	for (unsigned int i = 0; i < s1.length(); i++)
	{
		int c = static_cast<int>(s1[i]);
		if (c >= 97 && c <= 122)
			alpha1[c - 97]++;
	}
	for (unsigned int i = 0; i < s2.length(); i++)
	{
		int c = static_cast<int>(s2[i]);
		if (c >= 97 && c <= 122)
			alpha2[c - 97]++;
	}
	std::string res = "";
	for (int i = 0; i < 26; i++)
	{
		int sm = std::max(alpha1[i], alpha2[i]);
		if (sm > 1)
		{
			if (sm > alpha1[i])
			{
				std::string r1 = std::string(sm, static_cast<char>(i + 97));
				res += "2:" + r1 + "/";
			}
			else
			{
				std::string r2 = std::string(sm, static_cast<char>(i + 97));
				if (sm > alpha2[i])
					res += "1:" + r2 + "/";
				else
					res += "=:" + r2 + "/";
			}
		}
	}
	if (res.length() == 0)
		return "";
	std::vector<std::string> lstr = split(res.substr(0, res.length() - 1));
	std::sort(lstr.begin(), lstr.end(), compare);
	res = join(lstr);
	return res;
}


void test_mix() {
	auto res0 = Mix::mix("my&friend&Paul has heavy hats! &", "my friend John has many many friends &");
	std::string exp0 = "2:nnnnn/1:aaaa/1:hhh/2:mmm/2:yyy/2:dd/2:ff/2:ii/2:rr/=:ee/=:ss";
	assert(res0 == exp0);

	auto res1 = Mix::mix("mmmmm m nnnnn y&friend&Paul has heavy hats! &", "my frie n d Joh n has ma n y ma n y frie n ds n&");
	std::string exp1 = "1:mmmmmm/=:nnnnnn/1:aaaa/1:hhh/2:yyy/2:dd/2:ff/2:ii/2:rr/=:ee/=:ss";
	assert(res1 == exp1);

	auto res2 = Mix::mix("Are the kids at home? aaaaa fffff", "Yes they are here! aaaaa fffff");
	std::string exp2 = "=:aaaaaa/2:eeeee/=:fffff/1:tt/2:rr/=:hh";
	assert(res2 == exp2);
}

