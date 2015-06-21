#pragma once
#include <string>
#include "digraph.h"
#include "dfs.h"

class RegExp
{
	bool symbolIsStar(size_t index) const;
	bool symbolIsOrExpr(size_t index) const;
	bool symbolIsLeftParanthesis(size_t index) const;
	bool symbolIsRightParanthesis(size_t index) const;
	bool symbolIsLetter(size_t index) const;
	bool nextSymbolExists(size_t index) const;
	bool completeStateIsReachable(const dfs::Paths<DiGraph>::AllReachableVertexSet& reachableEpsilon) const;

public:
	typedef size_t First;
	typedef size_t Lenght;
	typedef std::pair<First, Lenght> OneMatch;
	typedef std::vector<OneMatch> MatchOccurences;

	RegExp(const std::string& regExp);
	bool recognizes(const std::string& text) const;
	MatchOccurences findOccurences(const std::string& text) const;

protected: // for test purposes
	DiGraph nfa;
	std::string regExp;
};