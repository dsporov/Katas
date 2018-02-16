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
#include <memory>
#include <regex>

#include <numeric>
#include <utility>

#include <assert.h>

/*
On 08/26/2016 (26.08.2016) the German Fussball-Bundesliga (national soccer league) started another new season!

In this kata you get an array with 9 strings, which contain the matches from the first match day.
Every string has this format, where x and y are the number of goals for the teams, if the match has already been played:

x:y [Team 1] - [Team 2]

Example:
6:0 FC Bayern Munchen - Werder Bremen
-:- Eintracht Frankfurt - Schalke 04
The team, which has shot more goals than the other team, wins the match.

Your method should create and return the league table as one string.

Every line in the table follows these rules:

1. Tableplace with two chars and a dot (" 1.", "12.")
2. Space
3. Name of the team/club padded right up to 30 chars (filled up with spaces).
4. Number of played matches (in this kata always only one digit)
5. Two spaces
6. Number of won matches (in this kata always only one digit)
7. Two spaces
8. Number of tie matches (in this kata always only one digit)
9. Two spaces
10. Number of lost matches (in this kata always only one digit)
11. Two spaces
12. Differences of goals (shot vs. gotten)
13. Two spaces
14. Count of points
It is 3 points for a won match and 1 point for a tie.
The table has to be sorted by these criteria:

1. Points
2. If the points are the same: The difference of goals. (2:0 is better than 1:0)
3. If the difference of goals is the same: More goals are better! (2:1 is better than 1:0)
4. Otherwise: The teams share the same place, but ordered by the name of the team (case-insensitive!)!
Example with the two matches above, if the league WOULD only have 4 teams:

1. FC Bayern Munchen             1  1  0  0  6:0  3
2. Eintrach Frankfurt            0  0  0  0  0:0  0
2. Schalke 04                    0  0  0  0  0:0  0
4. Werder Bremen                 1  0  0  1  0:6  0
You do not have to do a check for the input values. It will always be an array of 9 strings and all strings will be complete!

Have fun coding it and please don't forget to vote and rank this kata! :-)

I have created other katas. Have a look if you like coding and challenges.
*/

class Bundesliga {
	struct Team {
		Team()
			: wins(0)
			, draws(0)
			, looses(0)
			, scored(0)
			, conc(0)
			, place(0)
		{}

		std::string name;

		size_t wins;
		size_t draws;
		size_t looses;

		size_t scored;
		size_t conc;

		size_t place;

		size_t Points() const {
			return wins * 3 + draws;
		};

		int GoalsDiff() const {
			return scored - conc;
		};

		size_t Matches() const {
			return wins + draws + looses;
		};

		bool IsSamePlace(Team const& t) const {
			if (Points() != t.Points())
				return false;

			return scored == t.scored && conc == t.conc;
		}

		bool IsNameLess(Team const& t) const {
			std::string n1 = name;
			std::transform(n1.begin(), n1.end(), n1.begin(), ::tolower);

			std::string n2 = t.name;
			std::transform(n2.begin(), n2.end(), n2.begin(), ::tolower);

			return n1 < n2;
		}

		bool operator<(Team const& t) const {
			if (Points() != t.Points())
				return Points() > t.Points();

			if (GoalsDiff() != t.GoalsDiff())
				return GoalsDiff() > t.GoalsDiff();

			if (scored != t.scored)
				return scored > t.scored;

			return IsNameLess(t);
		}

		void Merge(Team const& t) {
			wins += t.wins;
			draws += t.draws;
			looses += t.looses;

			scored += t.scored;
			conc += t.conc;
		}
	};

	typedef std::set<Team> Standings;
	typedef std::tuple<Team, Team> Match;

public:
	std::string table(std::vector<std::string> results) {
		for (auto const& res : results) {
			auto match = ParseResult(res);
			UpdateStandings(match);
		}

		size_t pos = 1;
		size_t idx = 0;

		Team const* prevTeam = nullptr;
		for (auto &team : m_standings) {
			++idx;

			const_cast<Team&>(team).place = idx;
			if (prevTeam != nullptr) {
				if (team.IsSamePlace(*prevTeam))
					const_cast<Team&>(team).place = prevTeam->place;
			}

			prevTeam = &team;
		}

		std::string res;

		idx = 0;
		for (auto const& team : m_standings) {
			if (idx > 0)
				res += "\n";
			res += BuildTableLine(team);
			++idx;
		}

		return res;
	}

private:
	Standings m_standings;

	std::string BuildTableLine(Team const& team) {
		std::stringstream line;

		if (team.place < 10)
			line << " ";
		line << team.place << ". " << team.name;

		static const int TeamPlacaholderLen = 30;
		line << std::string(std::max(TeamPlacaholderLen - (int)team.name.length(), 0), ' ');

		line << team.Matches() << "  " << team.wins << "  " << team.draws << "  " << team.looses;

		line << "  " << team.scored << ":" << team.conc;

		line << "  " << team.Points();

		return line.str();
	}

	void UpdateStandings(Team const& team) {
		auto it1 = m_standings.find(team);
		if (it1 == m_standings.end()) {
			m_standings.insert(team);
			return;
		}

		Team existedTeam = *it1;
		existedTeam.Merge(team);
		m_standings.erase(it1);
		m_standings.insert(existedTeam);
	}

	void UpdateStandings(Match const& match) {
		UpdateStandings(std::get<0>(match));
		UpdateStandings(std::get<1>(match));
	}

	Match ParseResult(std::string const& res) {
		Team team1, team2;

		std::regex re(R"#(([\d, -]):([\d, -]) (.+) - (.+))#");

		std::smatch matchedResults;
		std::regex_match(res, matchedResults, re);

		std::string m1 = matchedResults[1].str();
		std::string m2 = matchedResults[2].str();
		std::string m3 = matchedResults[3].str();
		std::string m4 = matchedResults[4].str();

		team1.name = m3;
		team2.name = m4;

		if (m1 == "-") {
			return std::make_tuple(team1, team2);
		}

		size_t goals1 = std::stoi(m1);
		size_t goals2 = std::stoi(m2);

		team1.scored = goals1;
		team1.conc = goals2;

		team2.scored = goals2;
		team2.conc = goals1;

		if (goals1 == goals2) {
			team1.draws = team2.draws = 1;
		}
		if (goals1 > goals2) {
			++team1.wins;
			++team2.looses;
		}
		if (goals1 < goals2) {
			++team1.looses;
			++team2.wins;
		}

		return std::make_tuple(team1, team2);
	}
};

void test_German_Fussball_Bundesliga() {

	{
		std::vector<std::string> results =
		{
			"6:0 FC Bayern Muenchen - Werder Bremen",
			"-:- Eintracht Frankfurt - Schalke 04",
			"-:- FC Augsburg - VfL Wolfsburg",
			"-:- Hamburger SV - FC Ingolstadt",
			"-:- 1. FC Koeln - SV Darmstadt",
			"-:- Borussia Dortmund - FSV Mainz 05",
			"-:- Borussia Moenchengladbach - Bayer Leverkusen",
			"-:- Hertha BSC Berlin - SC Freiburg",
			"-:- TSG 1899 Hoffenheim - RasenBall Leipzig"
		};

		std::string expected =
			" 1. FC Bayern Muenchen            1  1  0  0  6:0  3\n"
			" 2. 1. FC Koeln                   0  0  0  0  0:0  0\n"
			" 2. Bayer Leverkusen              0  0  0  0  0:0  0\n"
			" 2. Borussia Dortmund             0  0  0  0  0:0  0\n"
			" 2. Borussia Moenchengladbach     0  0  0  0  0:0  0\n"
			" 2. Eintracht Frankfurt           0  0  0  0  0:0  0\n"
			" 2. FC Augsburg                   0  0  0  0  0:0  0\n"
			" 2. FC Ingolstadt                 0  0  0  0  0:0  0\n"
			" 2. FSV Mainz 05                  0  0  0  0  0:0  0\n"
			" 2. Hamburger SV                  0  0  0  0  0:0  0\n"
			" 2. Hertha BSC Berlin             0  0  0  0  0:0  0\n"
			" 2. RasenBall Leipzig             0  0  0  0  0:0  0\n"
			" 2. SC Freiburg                   0  0  0  0  0:0  0\n"
			" 2. Schalke 04                    0  0  0  0  0:0  0\n"
			" 2. SV Darmstadt                  0  0  0  0  0:0  0\n"
			" 2. TSG 1899 Hoffenheim           0  0  0  0  0:0  0\n"
			" 2. VfL Wolfsburg                 0  0  0  0  0:0  0\n"
			"18. Werder Bremen                 1  0  0  1  0:6  0";

		Bundesliga bundesLiga;

		std::string actual = bundesLiga.table(results);

		assert(("\n" + actual) == ("\n" + expected));
	}

	{
		std::vector<std::string> results =
		{
			"6:0 FC Bayern Muenchen - Werder Bremen",
			"1:0 Eintracht Frankfurt - Schalke 04",
			"0:2 FC Augsburg - VfL Wolfsburg",
			"1:1 Hamburger SV - FC Ingolstadt",
			"2:0 1. FC Koeln - SV Darmstadt",
			"2:1 Borussia Dortmund - FSV Mainz 05",
			"2:1 Borussia Moenchengladbach - Bayer Leverkusen",
			"-:- Hertha BSC Berlin - SC Freiburg",
			"-:- TSG 1899 Hoffenheim - RasenBall Leipzig"
		};

		std::string expected =
			" 1. FC Bayern Muenchen            1  1  0  0  6:0  3\n"
			" 2. 1. FC Koeln                   1  1  0  0  2:0  3\n"
			" 2. VfL Wolfsburg                 1  1  0  0  2:0  3\n"
			" 4. Borussia Dortmund             1  1  0  0  2:1  3\n"
			" 4. Borussia Moenchengladbach     1  1  0  0  2:1  3\n"
			" 6. Eintracht Frankfurt           1  1  0  0  1:0  3\n"
			" 7. FC Ingolstadt                 1  0  1  0  1:1  1\n"
			" 7. Hamburger SV                  1  0  1  0  1:1  1\n"
			" 9. Hertha BSC Berlin             0  0  0  0  0:0  0\n"
			" 9. RasenBall Leipzig             0  0  0  0  0:0  0\n"
			" 9. SC Freiburg                   0  0  0  0  0:0  0\n"
			" 9. TSG 1899 Hoffenheim           0  0  0  0  0:0  0\n"
			"13. Bayer Leverkusen              1  0  0  1  1:2  0\n"
			"13. FSV Mainz 05                  1  0  0  1  1:2  0\n"
			"15. Schalke 04                    1  0  0  1  0:1  0\n"
			"16. FC Augsburg                   1  0  0  1  0:2  0\n"
			"16. SV Darmstadt                  1  0  0  1  0:2  0\n"
			"18. Werder Bremen                 1  0  0  1  0:6  0";

		Bundesliga bundesLiga;

		std::string actual = bundesLiga.table(results);

		assert(("\n" + actual) == ("\n" + expected));
	}

	{
		std::vector<std::string> results =
		{
			"6:0 FC Bayern Muenchen - Werder Bremen",
			"1:0 Eintracht Frankfurt - Schalke 04",
			"0:2 FC Augsburg - VfL Wolfsburg",
			"1:1 Hamburger SV - FC Ingolstadt",
			"2:0 1. FC Koeln - SV Darmstadt",
			"2:1 Borussia Dortmund - FSV Mainz 05",
			"2:1 Borussia Moenchengladbach - Bayer Leverkusen",
			"2:1 Hertha BSC Berlin - SC Freiburg",
			"2:2 TSG 1899 Hoffenheim - RasenBall Leipzig"
		};

		std::string expected =
			" 1. FC Bayern Muenchen            1  1  0  0  6:0  3\n"
			" 2. 1. FC Koeln                   1  1  0  0  2:0  3\n"
			" 2. VfL Wolfsburg                 1  1  0  0  2:0  3\n"
			" 4. Borussia Dortmund             1  1  0  0  2:1  3\n"
			" 4. Borussia Moenchengladbach     1  1  0  0  2:1  3\n"
			" 4. Hertha BSC Berlin             1  1  0  0  2:1  3\n"
			" 7. Eintracht Frankfurt           1  1  0  0  1:0  3\n"
			" 8. RasenBall Leipzig             1  0  1  0  2:2  1\n"
			" 8. TSG 1899 Hoffenheim           1  0  1  0  2:2  1\n"
			"10. FC Ingolstadt                 1  0  1  0  1:1  1\n"
			"10. Hamburger SV                  1  0  1  0  1:1  1\n"
			"12. Bayer Leverkusen              1  0  0  1  1:2  0\n"
			"12. FSV Mainz 05                  1  0  0  1  1:2  0\n"
			"12. SC Freiburg                   1  0  0  1  1:2  0\n"
			"15. Schalke 04                    1  0  0  1  0:1  0\n"
			"16. FC Augsburg                   1  0  0  1  0:2  0\n"
			"16. SV Darmstadt                  1  0  0  1  0:2  0\n"
			"18. Werder Bremen                 1  0  0  1  0:6  0";

		Bundesliga bundesLiga;

		std::string actual = bundesLiga.table(results);

		assert(("\n" + actual) == ("\n" + expected));
	}
}
