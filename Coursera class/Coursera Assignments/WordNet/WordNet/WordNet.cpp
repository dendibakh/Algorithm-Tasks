#include "WordNet.h"

WordNet::WordNet(const std::string& synsetsFile, const std::string& hypernymsFile)
{
   synsets = parseSynsets(synsetsFile);
   for (auto i = synsets.begin(); i != synsets.end(); ++i)
   {
      int id = i - synsets.begin();
      for (auto j = i->synonym.begin(); j != i->synonym.end(); ++j)
      {
         nouns.insert(*j);
         nounMap.insert(std::make_pair(*j, id));
      }     
   }

   std::vector<hypernyms> graphRepresentation = parseHypernyms(hypernymsFile);
   graph.reset(new DiGraph(graphRepresentation.size()));
   for (auto i = graphRepresentation.begin(); i != graphRepresentation.end(); ++i)
   {
      int v = i - graphRepresentation.begin();
      for (auto j = i->begin(); j != i->end(); ++j)
      {
         int w = *j;
         graph->addEdge(v, w);
      }
   }

   sap.reset(new SAP(*graph));
}

std::set<std::string> WordNet::getNouns() const
{
   return nouns;
}

bool WordNet::isNoun(const std::string& word) const
{
   return nouns.find(word) != nouns.end();
}

int WordNet::getDistance(const std::string& nounA, const std::string& nounB) const
{
   CommonAncestor retVal = findClosestAncestor(nounA, nounB);
   return retVal.lenght;
}

std::set<std::string> WordNet::getSap(const std::string& nounA, const std::string& nounB) const
{
   CommonAncestor retVal = findClosestAncestor(nounA, nounB);
   return synsets[retVal.ancestorID].synonym;
}

CommonAncestor WordNet::findClosestAncestor(const std::string& nounA, const std::string& nounB) const
{
   // running time = O( (N * ( M + 1 ) / 2 ) * (5*E + 3*V) ), N = v.size(); M = w.size().
   CommonAncestor retVal = {-1, -1};
   std::list<int> v = getID(nounA);
   std::list<int> w = getID(nounB);
   for (auto i = v.begin(); i != v.end(); ++i)
   {
      for (auto j = w.begin(); j != w.end(); ++j)
      {
		 CommonAncestor curAncestor = sap->findClosestAncestor(*i, *j);
         int curLength = curAncestor.lenght;
         if ((curLength < retVal.lenght) || (-1 == retVal.lenght))
         {
            retVal.ancestorID = curAncestor.ancestorID;
            retVal.lenght = curLength;
         }
      }
   }
   return retVal;
}

std::list<int> WordNet::getID(const std::string& word) const
{
   std::list<int> retList;
   auto iters = nounMap.equal_range(word);
   if (iters.first == iters.second)
      throw std::runtime_error("No such word");
   for (auto i = iters.first; i != iters.second; ++i)
    {
      retList.push_back(i->second);
    }
   return retList;
}