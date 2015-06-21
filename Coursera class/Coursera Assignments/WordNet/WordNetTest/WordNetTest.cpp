#include "stdafx.h"
#include "util.h"
#include "WordNet.h"
#include "OutCast.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace   Microsoft::VisualStudio::TestTools::UnitTesting;

namespace WordNetTest
{
   [TestClass]
   public ref class WordNetTest
   {
   public: 
      [TestMethod]
      void TestParseSynsets()
      {
         /*std::vector<synset> result = parseSynsets(WordNetSynsets);
         Assert::IsTrue(result.size() == linesCount);
         std::set<std::string> expected;
         expected.insert("9/11");
         expected.insert("9-11");
         expected.insert("September_11");
         expected.insert("Sept._11");
         expected.insert("Sep_11");
         Assert::IsTrue(std::equal(expected.begin(), expected.end(), result[20].synonym.begin()));
         std::string expectedGloss("the day in 2001 when Arab suicide bombers hijacked United States airliners and used them as bombs  ");
         Assert::IsTrue(expectedGloss == result[20].gloss);*/
      }

      [TestMethod]
      void TestParseHypernyms()
      {
         /*std::vector<hypernyms> result = parseHypernyms(WordNetHypernyms);
         Assert::IsTrue(result.size() == linesCount);
         std::set<int> expected;
         expected.insert(51642);
         expected.insert(41004);
         expected.insert(57259);
         Assert::IsTrue(std::equal(expected.begin(), expected.end(), result[80256].begin()));*/
      }

      [TestMethod]
      void TestWordNet()
      {
         // For optimization all check are in one test.
         WordNet wNet(WordNetSynsets, WordNetHypernyms);
         Assert::IsTrue(wNet.isNoun("Asian_coral_snake"));
         Assert::IsTrue(wNet.isNoun("Edmund_Kean"));
         Assert::IsTrue(wNet.isNoun("Kean"));
         Assert::IsTrue(wNet.isNoun("basset"));
         Assert::IsTrue(wNet.isNoun("crammer"));
         Assert::IsTrue(wNet.isNoun("exteroceptor"));
         Assert::IsTrue(wNet.isNoun("yeoman_of_the_guard"));

         Assert::IsFalse(wNet.isNoun("Ancestor"));
         Assert::IsFalse(wNet.isNoun("Refactoring"));
         Assert::IsFalse(wNet.isNoun("MergeSort"));   

         Assert::AreEqual(1, wNet.getDistance("mountain_peak", "Aconcagua"));
         std::set<std::string> expected1;
         expected1.insert("mountain_peak");
         Assert::IsTrue(std::equal(expected1.begin(), expected1.end(), wNet.getSap("mountain_peak", "Aconcagua").begin()));

         // add more tests.
         // Assert::AreEqual(2, wNet.getDistance("demotion", "variation"));

         OutCast outCast(wNet);
         
         std::vector<std::string> nouns1;
         nouns1.push_back("horse");
         nouns1.push_back("zebra");
         nouns1.push_back("cat");
         nouns1.push_back("bear");
         nouns1.push_back("table");
         std::string actualOutCast1 = outCast.findOutCast(nouns1);
         std::string expectedOutCast1("table");
         Assert::IsTrue(expectedOutCast1 == actualOutCast1);
		 
         /*
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
         std::string expectedOutCast2("bed");
         Assert::IsTrue(expectedOutCast2 == actualOutCast2);
         
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
         std::string expectedOutCast3("potato");
         Assert::IsTrue(expectedOutCast3 == actualOutCast3);
         */
      }
   };
}
