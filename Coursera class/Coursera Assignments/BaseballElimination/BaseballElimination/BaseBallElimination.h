#pragma once
#include <string>
#include <vector>
#include "utils.h"

class BaseballElimination
{
	int getID(const std::string& team);
public:
	typedef std::vector<std::string> TeamList;
	BaseballElimination(const std::string& filename);                    // create a baseball division from given filename in format specified below
	int getNumberOfTeams();                        // number of teams
	TeamList getTeams();                                // all teams
	int getWins(const std::string& team);                      // number of wins for given team
	int losses(const std::string& team);                    // number of losses for given team
	int remaining(const std::string& team);                 // number of remaining games for given team
	int against(const std::string& team1, const std::string& team2);    // number of remaining games between team1 and team2
	bool isEliminated(const std::string& team);              // is given team eliminated?
	TeamList certificateOfElimination(const std::string& team);  // subset R of teams that eliminates given team; null if not eliminated
private:
	teamsList teams;
};
