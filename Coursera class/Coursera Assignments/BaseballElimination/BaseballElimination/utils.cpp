#include "utils.h"
#include <fstream>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

teamsList getTeamsMap(const std::string& fileName)
{
	teamsList returnMap;
	ifstream file;
	file.open(fileName);
	if (file)
	{
		while (!file.eof())
		{
			string line;
			TeamData teamData;
			getline(file, line);
			typedef tokenizer<boost::char_separator<char> > tokenizer;
			tokenizer tokens(line);
			tokenizer::iterator tok_iter = tokens.begin();
			if (tok_iter != tokens.end())
				++tok_iter;
			if (tok_iter != tokens.end())
			{
				teamData.name = *tok_iter;
				++tok_iter;
			}
			if (tok_iter != tokens.end())
			{
				teamData.wins = lexical_cast<int>(*tok_iter);
				++tok_iter;
			}
			if (tok_iter != tokens.end())
			{
				teamData.loss = lexical_cast<int>(*tok_iter);
				++tok_iter;
			}
			if (tok_iter != tokens.end())
			{
				teamData.left = lexical_cast<int>(*tok_iter);
				++tok_iter;
			}
				
			for (; tok_iter != tokens.end(); ++tok_iter)
				teamData.games.push_back(lexical_cast<int>(*tok_iter));
			
			returnMap.push_back(teamData);
		}
	}
	file.close();
	return returnMap;
}