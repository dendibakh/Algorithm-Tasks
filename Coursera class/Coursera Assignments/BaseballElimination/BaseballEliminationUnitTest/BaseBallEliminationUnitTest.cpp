#include "stdafx.h"
#include "CppUnitTest.h"
#include "BaseBallElimination.h"
#include "utils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BaseballEliminationUnitTest
{		
	TEST_CLASS(BaseballEliminationUnitTest)
	{
	public:
		
		TEST_METHOD(TestGetTeamsMap)
		{
			teamsList teams = getTeamsMap("C:\\BaseBallElimination.txt");
			Assert::AreEqual(size_t(5), teams.size());
			Assert::AreEqual(std::string("NewYork"), teams[0].name);
			Assert::AreEqual(75, teams[0].wins);
			Assert::AreEqual(59, teams[0].loss);
			Assert::AreEqual(28, teams[0].left);
			Assert::AreEqual(size_t(5), teams[0].games.size());

			Assert::AreEqual(std::string("Toronto"), teams[3].name);
			Assert::AreEqual(63, teams[3].wins);
			Assert::AreEqual(72, teams[3].loss);
			Assert::AreEqual(27, teams[3].left);
			Assert::AreEqual(size_t(5), teams[3].games.size());
		}

		TEST_METHOD(TestElimination)
		{
			BaseballElimination baseBallElimination("C:\\BaseBallElimination.txt");
			Assert::IsFalse(baseBallElimination.isEliminated("NewYork"));
			Assert::IsFalse(baseBallElimination.isEliminated("Baltimore"));
			Assert::IsFalse(baseBallElimination.isEliminated("Boston"));
			Assert::IsFalse(baseBallElimination.isEliminated("Toronto"));
			Assert::IsTrue(baseBallElimination.isEliminated("Detroit"));
		}
	};
}