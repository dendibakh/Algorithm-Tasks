#include "BaseBallElimination.h"
#include "FordFulkerson.h"
#include <limits>

BaseballElimination::BaseballElimination(const std::string& filename) : teams(getTeamsMap(filename))
{

}

int BaseballElimination::getNumberOfTeams()
{
	return static_cast<int>(teams.size());
}

BaseballElimination::TeamList BaseballElimination::getTeams()
{
	TeamList list;
	for (auto i = teams.begin(); i != teams.end(); ++i)
		list.push_back(i->name);
	return list;
}

int BaseballElimination::getWins(const std::string& team)
{
	for (auto i = teams.begin(); i != teams.end(); ++i)
		if (i->name == team)
			return i->wins;
	return 0;
}

int BaseballElimination::losses(const std::string& team)
{
	for (auto i = teams.begin(); i != teams.end(); ++i)
		if (i->name == team)
			return i->loss;
	return 0;
}

int BaseballElimination::remaining(const std::string& team)
{
	for (auto i = teams.begin(); i != teams.end(); ++i)
		if (i->name == team)
			return i->left;
	return 0;
}

int BaseballElimination::against(const std::string& team1, const std::string& team2)
{
	int i = getID(team1);
	int j = getID(team2);
	return teams[i].games[j];
}

int BaseballElimination::getID(const std::string& team)
{
	for (auto i = teams.begin(); i != teams.end(); ++i)
		if (i->name == team)
			return static_cast<int>(i - teams.begin());
	return 0;
}

bool BaseballElimination::isEliminated(const std::string& team)
{
	int i = getID(team);
	if (teams[i].wins + teams[i].left < teams[0].wins)
		return true;
	int n = getNumberOfTeams();
	FlowNetwork flowNet(n + 1 + (n-1)*(n-2) / 2);
	int vertexID = n + 1;
	for (auto j = teams.begin(); j != teams.end(); ++j)
	{
		int curTeam = j - teams.begin();
		if (curTeam == i)
			continue;
		for (auto k = j->games.begin(); k != j->games.end(); ++k)
		{
			int againstTeam = k - j->games.begin();
			if (againstTeam < curTeam)
				continue;
			if ((againstTeam != curTeam) && (againstTeam != i))
			{
				flowNet.addEdge(FlowEdge(i, vertexID, *k));
				flowNet.addEdge(FlowEdge(vertexID, curTeam, std::numeric_limits<int>::max()));
				flowNet.addEdge(FlowEdge(vertexID, againstTeam, std::numeric_limits<int>::max()));
				vertexID++;
			}
		}
		flowNet.addEdge(FlowEdge(curTeam, n, teams[i].wins + teams[i].left - j->wins));
	}
	FordFulkerson ff(flowNet, i, n);
	FordFulkerson::MinCutVertecies mincut = ff.getMinCutVertecies();
	if ((mincut.size() == 1) && (mincut.back() == i))
		return false;
	return true;
}