#pragma once
#include "util.h"
#include "SAP.h"
#include <map>

// ToDo:
//    1. Перетащить из дома тип DiGraph. Done.
//    2. Реализовать SAP. Done.
//    3. Написать тесты на SAP, используя примеры digraph1.txt и digraph2.txt. Done.
//    4. Реализовать WordNet через SAP. Done.
//    5. Написать тесты на WordNet. Done.
//    6. Возвращать из getSap set<string>. Done.
//    7. noun может входить в несколько synset'ов. Done.
//    8. Оптимизировать findOutCast. Запоминать вычисленные пары. Будет в два раза быстрее. Done.
//    9. Проанализировать временную сложность. Done.
//    10. Оптимизировать: - Вызовы sap::length() и sap::ancestor() объединить. Done
//    11. Провести профилирование. Найти узкие места. Done

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