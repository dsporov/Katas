#include "stdafx.h"

#include <string>
#include <vector>
#include <algorithm>

#include <assert.h>

/*
Your granny, who lives in town X0, has friends. These friends are given in an array, for example: array of friends is

[ "A1", "A2", "A3", "A4", "A5" ].
The order of friends is this array must not be changed since this order gives the order in which they will be visited.

These friends inhabit towns and you have an array with friends and towns, for example:

[ ["A1", "X1"], ["A2", "X2"], ["A3", "X3"], ["A4", "X4"] ]
or
(C)
{"A1", "X1", "A2", "X2", "A3", "X3", "A4", "X4"}
which means A1 is in town X1, A2 in town X2... It can happen that we don't know the town of one of the friends.

Your granny wants to visit her friends and to know how many miles she will have to travel.

You will make the circuit that permits her to visit her friends. For example here the circuit will contain:

X0, X1, X2, X3, X4, X0
and you must compute the total distance

X0X1 + X1X2 + .. + X4X0.
For the distance, fortunately, you have a map (and a hashmap) that gives each distance X0X1, X0X2 and so on. For example:

[ ["X1", 100.0], ["X2", 200.0], ["X3", 250.0], ["X4", 300.0] ]
or (Coffeescript, Javascript)
['X1',100.0, 'X2',200.0, 'X3',250.0, 'X4',300.0 ]
or
(C)
{"X1", "100.0", "X2", "200.0", "X3", "250.0", "X4", "300.0"}
which means that X1 is at 100.0 miles from X0, X2 at 200.0 miles from X0, etc...

More fortunately (it's not real life, it's a story...), the towns X0, X1, ..Xn are placed in the following manner:

X0X1X2 is a right triangle with the right angle in X1, X0X2X3 is a right triangle with the right angle in X2, etc...

If a town Xi is not visited you will suppose that the triangle

X0Xi-1Xi+1 is still a right triangle.

(Ref: https://en.wikipedia.org/wiki/Pythagoras#Pythagorean_theorem)

Task

Can you help your granny and give her the distance to travel?

Notes

If you have some difficulty to see the tour I made a non terrific but maybe useful drawing:


X1--------\
/       ---X2---\
/ - ----/         \
| /                 \
X0-------------------X3
\                     |
--------------------X4



alternative text

Python Note

You must implement a function only, not a whole class.

All languages

The data type of the parameters can be seen in the examples test cases.

"tour" returns an int which is the floor of the total distance.*/

#include <unordered_map>
#include <vector>
#include <map>

typedef std::unordered_map<std::string, double> stringdblmap;
class Tour {
	static double getDist(std::string const& town, stringdblmap const& h) {
		auto it = h.find(town);
		if (it == h.end())
			return 0.0;
		return it->second;
	}

	static double calcDist(std::string const& town1, std::string const& town2, stringdblmap const& h) {
		double a = getDist(town1, h);
		double c = getDist(town2, h);

		double b = sqrt(c*c - a*a);
		return b;
	}

	typedef std::map<std::string, std::string> FriendsTowns;

	static std::string getTown(std::string const& frnd, FriendsTowns const& friendsTowns) {
		auto it1 = friendsTowns.find(frnd);
		if (it1 == friendsTowns.end())
			return std::string();

		return it1->second;
	}

public:
	static int tour(std::vector<std::string> &arrFriends, std::vector<std::vector<std::string>> &ftwns, stringdblmap &h) {
		FriendsTowns friendsTowns;
		for (auto const& friendTown : ftwns)
			friendsTowns[friendTown.front()] = friendTown.back();

		std::string town1 = getTown(arrFriends.front(), friendsTowns);
		double dist = getDist(town1, h);
		for (size_t i = 1; i < arrFriends.size(); ++i) {
			auto const& town2 = getTown(arrFriends[i], friendsTowns);
			if (town2.empty())
				continue;

			dist += calcDist(town1, town2, h);
			town1 = town2;
		}
		dist += getDist(town1, h);

		return static_cast<int>(dist);
	}
};

/*
typedef std::unordered_map<string, double> stringdblmap;
class Tour
{
public:
static int tour(std::vector<string> &arrFriends, std::vector<std::vector<string>> &ftwns, stringdblmap &h) {
std::unordered_map<string, string> M;
for (const auto& x : ftwns)
M[x[0]] = x[1];
double t = 0, ans = 0;
for (const auto& x : arrFriends) {
if (M.find(x) == M.end()) continue;
double d = h[M[x]];
ans += sqrt(d*d - t*t);
t = d;
}
return int(ans + t);
}
};
*/

void testequal(int ans, int sol) {
	assert(ans == sol);
}

void dotest(std::vector<std::string> &arrFriends, std::vector<std::vector<std::string>> &ftwns, stringdblmap &h, int expected)
{
	testequal(Tour::tour(arrFriends, ftwns, h), expected);
}


//int main() {
//	std::vector<std::string> friends1 = { "A1", "A2", "A3", "A4", "A5" };
//	std::vector<std::vector<std::string>> fTowns1 = { { "A1", "X1" },{ "A2", "X2" },{ "A3", "X3" },{ "A4", "X4" } };
//	stringdblmap distTable1 = { { "X1", 100.0 },{ "X2", 200.0 },{ "X3", 250.0 },{ "X4", 300.0 } };
//	dotest(friends1, fTowns1, distTable1, 889);
//
//	friends1 = { "A1", "A2", "A3", "A4", "A5" };
//	fTowns1 = { { "A1", "X1" },{ "A2", "X2" },{ "A3", "X3" },{ "A4", "X4" },{ "A5", "X5" } };
//	distTable1 = { { "X1", 100.0 },{ "X2", 200.0 },{ "X3", 250.0 },{ "X4", 300.0 },{ "X5", 320.0 } };
//	dotest(friends1, fTowns1, distTable1, 1020);
//}
