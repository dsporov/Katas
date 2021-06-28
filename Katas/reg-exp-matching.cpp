#include "stdafx.h"

#include <assert.h>

/*
'.' Matches any single character
'*' Matches zero or more of the preceding element
*/
namespace {
/*
	bool isMatch(char c, char c2, char prev, bool matchPrev) {
		if (!matchPrev) {
			bool isAnySymbol = c2 == '.';
			if (!isAnySymbol)
				return c == c2;
			return true;
		}

		bool matchAny = prev == '.';
		if (matchAny)
			return true;

		return c == prev;
	}

	bool getNext(char const*& pattern, char& cur, char &prev, bool &matchPrev) {
		if (*pattern == '\0')
			return false;

		matchPrev = false;
		cur = *pattern;

		if (*(pattern + 1) == '*') {
			++pattern;
			matchPrev = true;
			prev = cur;
			cur = *pattern;
		}

		++pattern;
		return true;
	}

	bool checkLastPatternChars(char const* pattern, char prev, std::string const& s) {
		while (*pattern != '\0' && *(pattern + 1) == '*') {
			pattern += 2;
		}

		if (*pattern == '\0')
			return true;

		if (prev == '.') {
			while (*(++pattern) != '\0');
		}

		while (*pattern == prev)
			++pattern;
		if (*pattern != '\0')
			return false;

		int i = s.length();
		while (*(--pattern) == s[--i] && i > 0);
		if (*pattern == '*')
			return true;
		if (*pattern == prev && i == 0)
			return (*(--pattern) == '*');
		return false;
	}

	bool checkLastPatternChars(char const* pattern) {
		return false;
	}

	bool isMatch(std::string s, std::string p) {
		char const* pattern = p.c_str();
		bool matchPrev = false;
		char prev, cur;

		for (size_t i = 0; i < s.length(); ++i) {

			if (!getNext(pattern, cur, prev, matchPrev))
				return false;

			if (matchPrev) {
				while (i < s.length() && isMatch(s[i], cur, prev, matchPrev))
					++i;

				if (i >= s.length()) {
					return checkLastPatternChars(pattern, prev, s);
				}
				--i;
				continue;
			}

			if (!isMatch(s[i], cur, prev, matchPrev)) {
				return false;
			}
		}

		while (*pattern != '\0' && *(pattern + 1) == '*') {
			pattern += 2;
		}
		return *pattern == '\0';
	}
*/

	/*
class Solution {
	public boolean isMatch(String text, String pattern) {
		if (pattern.isEmpty()) return text.isEmpty();
		boolean first_match = (!text.isEmpty() &&
							   (pattern.charAt(0) == text.charAt(0) || pattern.charAt(0) == '.'));

		if (pattern.length() >= 2 && pattern.charAt(1) == '*'){
			return (isMatch(text, pattern.substring(2)) ||
					(first_match && isMatch(text.substring(1), pattern)));
		} else {
			return first_match && isMatch(text.substring(1), pattern.substring(1));
		}
	}
}	*/

/*
enum Result {
	TRUE, FALSE
}

class Solution {
	Result[][] memo;

	public boolean isMatch(String text, String pattern) {
		memo = new Result[text.length() + 1][pattern.length() + 1];
		return dp(0, 0, text, pattern);
	}

	public boolean dp(int i, int j, String text, String pattern) {
		if (memo[i][j] != null) {
			return memo[i][j] == Result.TRUE;
		}
		boolean ans;
		if (j == pattern.length()){
			ans = i == text.length();
		} else{
			boolean first_match = (i < text.length() &&
								   (pattern.charAt(j) == text.charAt(i) ||
									pattern.charAt(j) == '.'));

			if (j + 1 < pattern.length() && pattern.charAt(j+1) == '*'){
				ans = (dp(i, j+2, text, pattern) ||
					   first_match && dp(i+1, j, text, pattern));
			} else {
				ans = first_match && dp(i+1, j+1, text, pattern);
			}
		}
		memo[i][j] = ans ? Result.TRUE : Result.FALSE;
		return ans;
	}
}*/


/*
class Solution {
	public boolean isMatch(String text, String pattern) {
		boolean[][] dp = new boolean[text.length() + 1][pattern.length() + 1];
		dp[text.length()][pattern.length()] = true;

		for (int i = text.length(); i >= 0; i--){
			for (int j = pattern.length() - 1; j >= 0; j--){
				boolean first_match = (i < text.length() &&
									   (pattern.charAt(j) == text.charAt(i) ||
										pattern.charAt(j) == '.'));
				if (j + 1 < pattern.length() && pattern.charAt(j+1) == '*'){
					dp[i][j] = dp[i][j+2] || first_match && dp[i+1][j];
				} else {
					dp[i][j] = first_match && dp[i+1][j+1];
				}
			}
		}
		return dp[0][0];
	}
}
*/

	bool isMatch(char *text, char *pattern) {
		if (*pattern == '\0')
			return *text == '\0';

		bool first_match = (*text != '\0') &&
			(*pattern == *text || *pattern == '.');

		if (*(pattern+1) == '*') {
			return (isMatch(text, pattern+2) ||
				(first_match && isMatch(text+1, pattern)));
		}
		else {
			return first_match && isMatch(text+1, pattern+1);
		}

		return false;
	}

	bool isMatch(std::string s, std::string p) {
		return isMatch(s.c_str(), p.c_str());
	}
}

void test_reg_exp_matching() {
	assert(!isMatch("a", ".*..a*"));

	assert(isMatch("bbbba", ".*a*a"));

	assert(isMatch("a", "ab*"));

	assert(isMatch("aaa", "ab*a*c*a"));
	assert(isMatch("aaa", "a*aaa"));

	assert(!isMatch("aaa", "a*aaaa"));
	assert(isMatch("aaa", "a*a"));
	assert(isMatch("aaa", "a*aa"));

	assert(!isMatch("ab", "abc"));
	assert(!isMatch("ab", ".*c"));

	assert(!isMatch("aa", "a"));
	assert(isMatch("aa", "a*"));
	assert(isMatch("ab", ".*"));
	assert(isMatch("aab", "c*a*b"));

	assert(!isMatch("ssippi", "s*p*."));
	assert(!isMatch("mississippi", "mis*is*p*."));
}
