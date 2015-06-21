#pragma once

#include <vector>
#include <string>
#include <set>

static const char DIGraph1[] = "E:\\digraph1.txt";
static const char DIGraph2[] = "E:\\digraph2.txt";
static const char WordNetSynsets[] = "E:\\synsets.txt";
static const char WordNetHypernyms[] = "E:\\hypernyms.txt";
static const int linesCount = 82192;

struct synset
{
	std::set<std::string> synonym;
	std::string gloss;
};

typedef std::set<int> hypernyms;

std::vector<synset> parseSynsets(const std::string& FileName);
std::vector<hypernyms> parseHypernyms(const std::string& FileName);