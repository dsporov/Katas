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
Phone Directory

John keeps a backup of his old personal phone book as a text file. On each line of the file he can find the phone number (formated as +X-abc-def-ghij where X stands for one or two digits),
the corresponding name between < and > and the address.

Unfortunately everything is mixed, things are not always in the same order, lines are cluttered with non-alpha-numeric characters.

Examples of John's phone book lines:

"/+1-541-754-3010 156 Alphand_St. <J Steeve>\n"

" 133, Green, Rd. <E Kustur> NY-56423 ;+1-541-914-3010!\n"

"<Anastasia> +48-421-674-8974 Via Quirinal Roma\n"

Could you help John with a program that, given the lines of his phone book and a phone number returns a string for this number : "Phone => num, Name => name, Address => adress"

Examples:

s = "/+1-541-754-3010 156 Alphand_St. <J Steeve>\n 133, Green, Rd. <E Kustur> NY-56423 ;+1-541-914-3010!\n"

phone(s, "1-541-754-3010") should return "Phone => 1-541-754-3010, Name => J Steeve, Address => 156 Alphand St."
It can happen that, for a few phone numbers, there are many people for a phone number -say nb- , then

return : "Error => Too many people: nb"

or it can happen that the number nb is not in the phone book, in that case

return: "Error => Not found: nb"

You can see other examples in the test cases.

JavaScript random tests completed by @matt c

Note
Codewars stdout doesn't print part of a string when between < and >
*/


class PhoneDir {
public:
	static std::string phone(const std::string& orgdr, std::string num) {
		PhoneBook phoneBook;
		DuplicatePhones duplicates;
		Parse(orgdr, phoneBook, duplicates);

		if (duplicates.find(num) != duplicates.end()) {
			return "Error => Too many people: " + num;
		}

		auto it = phoneBook.find(num);
		if (it == phoneBook.end()) {
			return "Error => Not found: " + num;
		}

		std::string res =
			"Phone => " + num + ", " +
			"Name => " + it->second.name + ", "
			"Address => " + it->second.addr;
		return res;
	}

private:
	struct Entry {
		Entry(std::string n = std::string(), std::string a = std::string()) : name(n), addr(a) {};
		std::string name, addr;
	};
	typedef std::map<std::string, Entry> PhoneBook;

	typedef std::set<std::string> DuplicatePhones;

	static constexpr char PHONE_DELIM = '+';
	static constexpr char NAME_START_DELIM = '<';
	static constexpr char NAME_END_DELIM = '>';

	static void Parse(std::string const& orgdr, PhoneBook &phoneBook, DuplicatePhones &duplicates) {
		std::istringstream ss(orgdr);
		std::string next;
		while (std::getline(ss, next)) {
			std::string phone, name, addr;
			ParseLine(next, phone, name, addr);

			if (phoneBook.find(phone) != phoneBook.end()) {
				duplicates.insert(phone);
				continue;
			}

			phoneBook[phone] = Entry(name, addr);
		}
	}

	static bool isAddrDelim(char ch) {
		return ch == ' ' || ch == '.' || ch == '-';
	}

	static void ParseLine(std::string const& line, std::string &phone, std::string &name, std::string &addr) {
		for (size_t i = 0; i < line.size(); ++i) {
			char ch = line[i];
			if (ch == PHONE_DELIM) {
				i = ParsePhone(line, i, phone);
				continue;
			}

			if (ch == NAME_START_DELIM) {
				i = ParseName(line, i, name);
				continue;
			}

			if (ch == '_')
				ch = ' ';

			if (!std::isalnum(ch) && !isAddrDelim(ch))
				continue;

			if (isAddrDelim(ch) && (addr.empty() || addr.back() == ch))
				continue;
			addr += ch;
		}

		while (addr.back() == ' ')
			addr.pop_back();
	}

	static size_t ParsePhone(std::string const& line, size_t idx, std::string &phone) {
		size_t idxStart = ++idx;
		for (; idx < line.size(); ++idx) {
			char ch = line[idx];

			bool isPhonePart = ch == '-' || std::isdigit(ch);
			if (!isPhonePart)
				break;
		}

		phone = line.substr(idxStart, idx - idxStart);
		return idx - 1;
	}

	static size_t ParseName(std::string const& line, size_t idx, std::string &name) {
		size_t nameEnd = line.find(NAME_END_DELIM);
		if (nameEnd == std::string::npos)
			return idx;

		name = line.substr(idx + 1, nameEnd - idx - 1);
		return nameEnd;
	}
};


#include <regex>

class PhoneDir1
{
private:
	static void trim(std::string &s);
public:
	static std::string phone(const std::string& orgdr, std::string num);
};

void PhoneDir1::trim(std::string &s) {
	s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), [](char c) { return std::isspace(c); }));
	s.erase(std::find_if_not(s.rbegin(), s.rend(), [](char c) { return std::isspace(c); }).base(), s.end());
}

std::string PhoneDir1::phone(const std::string& orgdr, std::string num)
{
	// work on copy
	std::string dr = orgdr;
	// clean data
	std::regex e("[^-0-9a-z\\s+A-Z\\n<>.']");
	dr = std::regex_replace(dr, e, " ");
	// search num
	std::string regex_string = std::string(".*") + "\\+" + num + ".*";
	std::regex f(regex_string); std::smatch sm;
	int cnt = 0; std::string fnd = "";
	while (std::regex_search(dr, sm, f)) {
		for (auto x : sm)
		{
			// keep the result and count
			fnd = x; cnt++;
		}
		dr = sm.suffix().str();
	}
	// bad cases
	if (cnt == 0) return "Error => Not found: " + num;
	if (cnt > 1) return "Error => Too many people: " + num;
	// remove num
	std::string regex_string1 = std::string("\\s*") + "\\+" + num;
	std::regex f1(regex_string1);
	fnd = std::regex_replace(fnd, f1, "");
	// search name
	std::string regex_string2 = std::string("\\<") + ".*" + "\\>";
	std::regex f2(regex_string2); std::smatch sm2;
	std::string name = "", tmp = fnd;
	while (std::regex_search(fnd, sm2, f2)) {
		for (auto x : sm2) name = x;
		fnd = sm2.suffix().str();
	}
	// remove name
	std::string regex_string3 = std::string("\\<") + ".*" + "\\>";
	std::regex f3(regex_string3);
	// address
	std::string address = std::regex_replace(tmp, f3, "");
	// clean address
	std::regex h("[ ]{2,}");
	address = std::regex_replace(address, h, " ");
	PhoneDir1::trim(address);
	return "Phone => " + num + ", Name => " + name.substr(1, name.length() - 2) + ", Address => " + address;
}

void test_phoneDirectory() {
	std::string dr = "/+1-541-754-3010 156 Alphand_St. <J Steeve>\n 133, Green, Rd. <E Kustur> NY-56423 ;+1-541-914-3010\n"
		"+1-541-984-3012 <P Reed> /PO Box 530; Pollocksville, NC-28573\n :+1-321-512-2222 <Paul Dive> Sequoia Alley PQ-67209\n"
		"+1-741-984-3090 <Peter Reedgrave> _Chicago\n :+1-921-333-2222 <Anna Stevens> Haramburu_Street AA-67209\n"
		"+1-111-544-8973 <Peter Pan> LA\n +1-921-512-2222 <Wilfrid Stevens> Wild Street AA-67209\n"
		"<Peter Gone> LA ?+1-121-544-8974 \n <R Steell> Quora Street AB-47209 +1-481-512-2222\n"
		"<Arthur Clarke> San Antonio $+1-121-504-8974 TT-45120\n <Ray Chandler> Teliman Pk. !+1-681-512-2222! AB-47209,\n"
		"<Sophia Loren> +1-421-674-8974 Bern TP-46017\n <Peter O'Brien> High Street +1-908-512-2222; CC-47209\n"
		"<Anastasia> +48-421-674-8974 Via Quirinal Roma\n <P Salinger> Main Street, +1-098-512-2222, Denver\n"
		"<C Powel> *+19-421-674-8974 Chateau des Fosses Strasbourg F-68000\n <Bernard Deltheil> +1-498-512-2222; Mount Av.  Eldorado\n"
		"+1-099-500-8000 <Peter Crush> Labrador Bd.\n +1-931-512-4855 <William Saurin> Bison Street CQ-23071\n"
		"<P Salinge> Main Street, +1-098-512-2222, Denve\n"
		"<P Salinge> Main Street, +1-098-512-2222, Denve\n"
		"/+5-541-754-3010 156 Alphandria_Street. <Jr Part>\n 1333, Green, Road <F Fulgur> NW-46423 ;+6-541-914-3010!\n"
		"+5-541-984-3012 <Peter Reeves> /PO Box 5300; Albertville, SC-28573\n :+5-321-512-2222 <Paulo Divino> Boulder Alley ZQ-87209\n"
		"+3-741-984-3090 <F Flanaghan> _Chicago Av.\n :+3-921-333-2222 <Roland Scorsini> Bellevue_Street DA-67209\n"
		"+8-111-544-8973 <Laurence Pantow> SA\n +8-921-512-2222 <Raymond Stevenson> Joly Street EE-67209\n"
		"<John Freeland> Mantow ?+2-121-544-8974 \n <Robert Mitch> Eleonore Street QB-87209 +2-481-512-2222?\n"
		"<Arthur Paternos> San Antonio $+7-121-504-8974 TT-45121\n <Ray Charles> Stevenson Pk. !+7-681-512-2222! CB-47209,\n"
		"<JP Gorce> +9-421-674-8974 New-Bern TP-16017\n <P McDon> Revolution Street +2-908-512-2222; PP-47209\n"
		"<Elizabeth Corber> +8-421-674-8974 Via Papa Roma\n <C Saborn> Main Street, +15-098-512-2222, Boulder\n"
		"<Colin Marshall> *+9-421-674-8974 Edinburgh UK\n <Bernard Povit> +3-498-512-2222; Hill Av.  Cameron\n"
		"+12-099-500-8000 <Pete Highman> Ontario Bd.\n +8-931-512-4855 <W Mount> Oxford Street CQ-23071\n"
		"<Donald Drinkaw> Moon Street, +3-098-512-2222, Peterville\n";

	std::string res = PhoneDir::phone(dr, "1-481-512-2222");
	std::string exp = "Phone => 1-481-512-2222, Name => R Steell, Address => Quora Street AB-47209";

	/*	if (res != exp) {
	size_t l1 = res.length();
	size_t l2 = exp.length();
	for (size_t i = 0; i < l1; ++i) {

	}
	}*/

	assert(PhoneDir::phone(dr, "48-421-674-8974") == "Phone => 48-421-674-8974, Name => Anastasia, Address => Via Quirinal Roma");
	assert(PhoneDir::phone(dr, "19-421-674-8974") == "Phone => 19-421-674-8974, Name => C Powel, Address => Chateau des Fosses Strasbourg F-68000");
	assert(PhoneDir::phone(dr, "1-921-512-2222") == "Phone => 1-921-512-2222, Name => Wilfrid Stevens, Address => Wild Street AA-67209");
	assert(PhoneDir::phone(dr, "1-481-512-2222") == "Phone => 1-481-512-2222, Name => R Steell, Address => Quora Street AB-47209");
	assert(PhoneDir::phone(dr, "1-098-512-2222") == "Error => Too many people: 1-098-512-2222");
	assert(PhoneDir::phone(dr, "5-555-555-5555") == "Error => Not found: 5-555-555-5555");
}
