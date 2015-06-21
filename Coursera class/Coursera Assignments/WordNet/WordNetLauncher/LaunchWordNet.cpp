#include "WordNet.h"
#include "OutCast.h"

int main()
{
	WordNet wNet(WordNetSynsets, WordNetHypernyms);
	OutCast outCast(wNet);
	/*
	std::vector<std::string> nouns1;
	nouns1.push_back("horse");
	nouns1.push_back("zebra");
	nouns1.push_back("cat");
	nouns1.push_back("bear");
	nouns1.push_back("table");
	std::string actualOutCast1 = outCast.findOutCast(nouns1);
	
	std::vector<std::string> nouns2;
	nouns2.push_back("water");
	nouns2.push_back("soda");
	nouns2.push_back("bed");
	nouns2.push_back("orange_juice");
	nouns2.push_back("milk");
	nouns2.push_back("apple_juice");
	nouns2.push_back("tea");
	nouns2.push_back("coffee");
	std::string actualOutCast2 = outCast.findOutCast(nouns2);
    */     
	std::vector<std::string> nouns3;
	nouns3.push_back("apple");
	nouns3.push_back("pear");
	nouns3.push_back("peach");
	nouns3.push_back("banana");
	nouns3.push_back("potato");
	nouns3.push_back("lime");
	nouns3.push_back("lemon");
	nouns3.push_back("blueberry");
	nouns3.push_back("strawberry");
	nouns3.push_back("mango");
	nouns3.push_back("watermelon");
	std::string actualOutCast3 = outCast.findOutCast(nouns3);
}
