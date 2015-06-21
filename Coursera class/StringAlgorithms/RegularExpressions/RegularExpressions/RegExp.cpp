#include "RegExp.h"
#include <stack>
#include <memory>

RegExp::RegExp(const std::string& regExp) : nfa(regExp.size() + 1) , regExp(regExp)
{
	std::stack<size_t> helperStack;
	size_t regExplength = regExp.size();
	if (regExplength == 0)
		throw std::domain_error("Regular Expression cannot be empty!");
	for (size_t i = 0; i < regExplength; ++i)
	{
		if (symbolIsOrExpr(i))
		{
			if (i == 0 || i == regExplength - 1)
				throw std::domain_error("Regular Expression is not valid! | cannot be the first or the last symbol.");
			if (nextSymbolExists(i) && symbolIsStar(i + 1))
				throw std::domain_error("Regular Expression is not valid! | cannot be followed by *.");
			if (helperStack.empty())
				throw std::domain_error("Regular Expression is not valid! There Should be left parenthesis before |.");
			helperStack.push(i);
		}
		else if (symbolIsStar(i))
		{
			if (i == 0)
				throw std::domain_error("Regular Expression is not valid! * cannot be the first symbol.");
			if (symbolIsLetter(i - 1))
			{
				nfa.addEdge(i - 1, i);
				nfa.addEdge(i, i - 1);
			}
			nfa.addEdge(i, i + 1);
		}
		else if (symbolIsLeftParanthesis(i))
		{
			helperStack.push(i);
			nfa.addEdge(i, i + 1);
		}
		else if (symbolIsRightParanthesis(i))
		{
			if (helperStack.empty())
				throw std::domain_error("Regular Expression is not valid!");
			nfa.addEdge(i, i + 1);
			size_t leftElementIndex = helperStack.top();
			if (symbolIsLeftParanthesis(leftElementIndex))
			{
				if (i - leftElementIndex < 2)
					throw std::domain_error("Regular Expression is not valid! There should be symbols between ( and )");
			}
			if (symbolIsOrExpr(leftElementIndex))
			{
				helperStack.pop();
				size_t leftParenthesisIndex = helperStack.top();
				if (symbolIsOrExpr(leftParenthesisIndex))
					throw std::domain_error("Regular Expression is not valid! Sequential | symbols are not supported.");
				if (!symbolIsLeftParanthesis(leftParenthesisIndex))
					throw std::domain_error("Regular Expression is not valid!");
				if (leftElementIndex - leftParenthesisIndex < 2)
					throw std::domain_error("Regular Expression is not valid! There should be symbols between ( and |");
				if (i - leftElementIndex < 2)
					throw std::domain_error("Regular Expression is not valid! There should be symbols between | and )");
				nfa.addEdge(leftParenthesisIndex, leftElementIndex + 1);
				nfa.addEdge(leftElementIndex, i);
			}
			if (nextSymbolExists(i) && symbolIsStar(i + 1))
			{
				size_t leftParenthesisIndex = helperStack.top();
				if (symbolIsLeftParanthesis(leftParenthesisIndex))
				{
					nfa.addEdge(leftParenthesisIndex, i + 1);
					nfa.addEdge(i + 1, leftParenthesisIndex);
				}
			}
			helperStack.pop();
		}
	}
	if (!helperStack.empty())
		throw std::domain_error("Regular Expression is not valid!");
}

bool RegExp::symbolIsStar(size_t index) const
{
	return regExp[index] == '*';
}

bool RegExp::symbolIsOrExpr(size_t index) const
{
	return regExp[index] == '|';
}

bool RegExp::symbolIsLeftParanthesis(size_t index) const
{
	return regExp[index] == '(';
}

bool RegExp::symbolIsRightParanthesis(size_t index) const
{
	return regExp[index] == ')';
}

bool RegExp::symbolIsLetter(size_t index) const
{
	return regExp[index] >= 'A' && regExp[index] <= 'z';
}

bool RegExp::nextSymbolExists(size_t index) const
{
	return index < regExp.size() - 1;
}

RegExp::MatchOccurences RegExp::findOccurences(const std::string& text) const
{
	RegExp::MatchOccurences retOccur;
	std::unique_ptr<dfs::Paths<DiGraph>> paths(new dfs::Paths<DiGraph>(nfa, 0));
	dfs::Paths<DiGraph>::AllReachableVertexSet reachableEpsilon = paths->getAllReachable();

	size_t matchStartIndex = 0;
	bool matchFound = false;

	size_t textSize = text.size();
	for (size_t i = 0; i < textSize; ++i)
	{
		std::vector<int> matches;
		for (dfs::Paths<DiGraph>::AllReachableVertexSet::const_iterator iter = reachableEpsilon.begin(); iter != reachableEpsilon.end(); ++iter)
		{
			if ((text[i] == regExp[*iter]) || (regExp[*iter] == '.'))
			{
				matches.push_back(*iter + 1);
				if (!matchFound)
				{
					matchFound = true;
					matchStartIndex = i;
				}
			}
		}

		if (matches.empty())
		{
			if (completeStateIsReachable(reachableEpsilon))
				retOccur.push_back(std::make_pair(matchStartIndex, i - matchStartIndex));
			if (matchFound)
			{
				// in the next iteration we will go to the same symbol but nfa will be reloaded!
				i = i - 1; 
				matchFound = false;
			}
			// reload the nfa
			paths.reset(new dfs::Paths<DiGraph>(nfa, 0));
		}	
		else
		{
			paths.reset(new dfs::Paths<DiGraph>(nfa, matches));
		}

		reachableEpsilon = paths->getAllReachable();
	}
	if (completeStateIsReachable(reachableEpsilon))
		retOccur.push_back(std::make_pair(matchStartIndex, textSize - matchStartIndex));
	return retOccur;
}

bool RegExp::recognizes(const std::string& text) const
{
	return !findOccurences(text).empty();
}

bool RegExp::completeStateIsReachable(const dfs::Paths<DiGraph>::AllReachableVertexSet& reachableEpsilon) const
{
	size_t completeState = regExp.size();
	for (dfs::Paths<DiGraph>::AllReachableVertexSet::const_iterator iter = reachableEpsilon.begin(); iter != reachableEpsilon.end(); ++iter)
	{
		if (*iter == completeState)
			return true;
	}
	return false;
}