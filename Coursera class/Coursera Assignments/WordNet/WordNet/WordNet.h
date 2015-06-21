#pragma once
#include "util.h"
#include "SAP.h"
#include <map>

// ToDo:
//    1. ���������� �� ���� ��� DiGraph. Done.
//    2. ����������� SAP. Done.
//    3. �������� ����� �� SAP, ��������� ������� digraph1.txt � digraph2.txt. Done.
//    4. ����������� WordNet ����� SAP. Done.
//    5. �������� ����� �� WordNet. Done.
//    6. ���������� �� getSap set<string>. Done.
//    7. noun ����� ������� � ��������� synset'��. Done.
//    8. �������������� findOutCast. ���������� ����������� ����. ����� � ��� ���� �������. Done.
//    9. ���������������� ��������� ���������. Done.
//    10. ��������������: - ������ sap::length() � sap::ancestor() ����������. Done
//    11. �������� ��������������. ����� ����� �����. Done

class WordNet
{
   CommonAncestor findClosestAncestor(const std::string& nounA, const std::string& nounB) const;
   std::list<int> getID(const std::string& word) const;
public:
   // constructor takes the name of the two input files
   WordNet(const std::string& synsetsFile, const std::string& hypernymsFile);

   // the set of nouns (no duplicates), returned as an Iterable
   std::set<std::string> getNouns() const;

   // is the word a WordNet noun?
   bool isNoun(const std::string& word) const;

   // distance between nounA and nounB
   int getDistance(const std::string& nounA, const std::string& nounB) const;

   // a synset that is the common ancestor of nounA and nounB in a shortest ancestral path
   std::set<std::string> getSap(const std::string& nounA, const std::string& nounB) const;
private:
   std::vector<synset> synsets;
   std::auto_ptr<DiGraph> graph;
   std::set<std::string> nouns;
   std::multimap<std::string, int> nounMap;
   std::auto_ptr<SAP> sap;
};