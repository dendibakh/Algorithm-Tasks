#include "stdafx.h"
#include "BruteForceSubstringSearch.h"
#include "KnuthMorrisPrattSubstringSearch.h"
#include "BoyerMooreSubStringSearch.h"
#include "RabinKarpSubStringSearch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace SubstringSearch
{
	TEST_CLASS(BruteForceSubstringSearchTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			string InitSet("ABACADABRAC");
			BruteForceSubstringSearch subStr(InitSet);

			Assert::AreEqual(6, subStr.findSubString("ABRA"));
		}		

		TEST_METHOD(TestMethod2)
		{
			string InitSet("We think in generalities, but we live in details.");
			BruteForceSubstringSearch subStr(InitSet);

			Assert::AreEqual(12, subStr.findSubString("gen"));
			Assert::AreEqual(-1, subStr.findSubString("gena"));
		}
	};

	TEST_CLASS(KnuthMorrisPrattSubstringSearchTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			string InitSet("ABACADABRAC");
			KnuthMorrisPrattSubstringSearch subStr(InitSet);

			Assert::AreEqual(6, subStr.findSubString("ABRA"));
		}

		TEST_METHOD(TestMethod2)
		{
			string InitSet("We think in generalities, but we live in details.");
			KnuthMorrisPrattSubstringSearch subStr(InitSet);

			Assert::AreEqual(12, subStr.findSubString("gen"));
			Assert::AreEqual(-1, subStr.findSubString("gena"));
		}

		TEST_METHOD(TestMethod3)
		{
			string InitSet("Creating testset for KnuthMorrisPratt is very cool!");
			KnuthMorrisPrattSubstringSearch subStr(InitSet);

			Assert::AreEqual(9, subStr.findSubString("testset"));
			Assert::AreEqual(9, subStr.findSubString("test"));
			Assert::AreEqual(-1, subStr.findSubString("settest"));
			Assert::AreEqual(3, subStr.findSubString("at"));
		}
	};

	TEST_CLASS(BoyerMooreSubStringSearchTest)
	{
	public:
		TEST_METHOD(BoyerMoore1)
		{
			string InitSet("ABACADABRAC");
			BoyerMooreSubstringSearch subStr(InitSet);

			Assert::AreEqual(6, subStr.findSubString("ABRA"));
		}

		TEST_METHOD(BoyerMoore2)
		{
			string InitSet("We think in generalities, but we live in details.");
			BoyerMooreSubstringSearch subStr(InitSet);

			Assert::AreEqual(12, subStr.findSubString("gen"));
			Assert::AreEqual(-1, subStr.findSubString("gena"));
		}

		TEST_METHOD(BoyerMoore3)
		{
			string InitSet("Creating testset for KnuthMorrisPratt is very cool!");
			BoyerMooreSubstringSearch subStr(InitSet);

			Assert::AreEqual(9, subStr.findSubString("testset"));
			Assert::AreEqual(9, subStr.findSubString("test"));
			Assert::AreEqual(-1, subStr.findSubString("settest"));
			Assert::AreEqual(3, subStr.findSubString("at"));
		}

		TEST_METHOD(BoyerMoore4)
		{
			string InitSet("AABBRARB");
			BoyerMooreSubstringSearch subStr(InitSet);

			Assert::AreEqual(1, subStr.findSubString("ABBR"));
		}

		TEST_METHOD(BoyerMoore5)
		{
			string InitSet("AABRBBAABBBBAABBRB");
			BoyerMooreSubstringSearch subStr(InitSet);

			Assert::AreEqual(13, subStr.findSubString("ABBRB"));
		}
	};

	TEST_CLASS(RabinKarpSubStringSearchTest)
	{
	public:
		TEST_METHOD(RabinKarp1)
		{
			string InitSet("ABACADABRAC");
			RabinKarpSubStringSearch subStr(InitSet);

			Assert::AreEqual(6, subStr.findSubString("ABRA"));
		}

		TEST_METHOD(RabinKarp2)
		{
			string InitSet("We think in generalities, but we live in details.");
			RabinKarpSubStringSearch subStr(InitSet);

			Assert::AreEqual(12, subStr.findSubString("gen"));
			Assert::AreEqual(-1, subStr.findSubString("gena"));
		}

		TEST_METHOD(RabinKarp3)
		{
			string InitSet("Creating testset for KnuthMorrisPratt is very cool!");
			RabinKarpSubStringSearch subStr(InitSet);

			Assert::AreEqual(9, subStr.findSubString("testset"));
			Assert::AreEqual(9, subStr.findSubString("test"));
			Assert::AreEqual(-1, subStr.findSubString("settest"));
			Assert::AreEqual(3, subStr.findSubString("at"));
		}

		TEST_METHOD(RabinKarp4)
		{
			string InitSet("AABBRARB");
			RabinKarpSubStringSearch subStr(InitSet);

			Assert::AreEqual(1, subStr.findSubString("ABBR"));
		}

		TEST_METHOD(RabinKarp5)
		{
			string InitSet("AABRBBAABBBBAABBRB");
			RabinKarpSubStringSearch subStr(InitSet);

			Assert::AreEqual(13, subStr.findSubString("ABBRB"));
		}
	};
}