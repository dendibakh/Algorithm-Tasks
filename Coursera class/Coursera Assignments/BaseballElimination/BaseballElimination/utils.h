#pragma once
#include <string>
#include <vector>

struct TeamData
{
	std::string name;
	int wins;
	int loss;
	int left;
	std::vector<int> games;
};

typedef std::vector<TeamData> teamsList;

teamsList getTeamsMap(const std::string& fileName);