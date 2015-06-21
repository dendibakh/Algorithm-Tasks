#include "stdafx.h"
#include "CppUnitTest.h"
#include "RegExp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define unused_var(v) (void)(v)

namespace
{
	class RegExpFake : public RegExp
	{
	public:
		RegExpFake(const std::string& regExp) : RegExp(regExp) {}
		using RegExp::nfa;
	};
}

namespace RegExpTest
{		
	TEST_CLASS(RegExpTest)
	{
	public:
		
		TEST_METHOD(IsExist)
		{
			RegExpFake regExp("A");
			unused_var(regExp);
		}

		TEST_METHOD(ConstructorTakesRegExp)
		{
			RegExpFake regExp("ABC");
			unused_var(regExp);
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown1)
		{
			try
			{
				RegExpFake regExp("");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckVertexCount1)
		{
			RegExpFake regExp("ABC");
			Assert::AreEqual(4, regExp.nfa.getVertexCount());
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckEdgesCount1)
		{
			RegExpFake regExp("ABC");
			Assert::AreEqual(0, regExp.nfa.getEdgesCount());
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckWholeGraph1)
		{
			RegExpFake regExp("ABC");
			DiGraph etalon(4);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckVertexCount2)
		{
			RegExpFake regExp("ABCDregt");
			Assert::AreEqual(9, regExp.nfa.getVertexCount());
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckEdgesCount2)
		{
			RegExpFake regExp("ABCDregt");
			Assert::AreEqual(0, regExp.nfa.getEdgesCount());
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckWholeGraph2)
		{
			RegExpFake regExp("ABCDregt");
			DiGraph etalon(9);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown2)
		{
			try
			{
				RegExpFake regExp("A(B");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown3)
		{
			try
			{
				RegExpFake regExp("A)B");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}
		
		TEST_METHOD(ConstructorBuildsNFA_CheckSingleParenthesis)
		{
			RegExpFake regExp("A(BC)Dregt");
			Assert::AreEqual(11, regExp.nfa.getVertexCount());
			Assert::AreEqual(2, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(1, 2);
			etalon.addEdge(4, 5);
			Assert::IsTrue(etalon == regExp.nfa);
		}
		
		TEST_METHOD(ConstructorBuildsNFA_CheckNestedParenthesis)
		{
			RegExpFake regExp("A(B(CD)r)egt");
			Assert::AreEqual(13, regExp.nfa.getVertexCount());
			Assert::AreEqual(4, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(1, 2);
			etalon.addEdge(3, 4);
			etalon.addEdge(6, 7);
			etalon.addEdge(8, 9);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckClosure)
		{
			RegExpFake regExp("A*BC");
			Assert::AreEqual(5, regExp.nfa.getVertexCount());
			Assert::AreEqual(3, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(0, 1);
			etalon.addEdge(1, 0);
			etalon.addEdge(1, 2);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckTwoClosures)
		{
			RegExpFake regExp("A*BCD*");
			Assert::AreEqual(7, regExp.nfa.getVertexCount());
			Assert::AreEqual(6, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(0, 1);
			etalon.addEdge(1, 0);
			etalon.addEdge(1, 2);
			etalon.addEdge(4, 5);
			etalon.addEdge(5, 4);
			etalon.addEdge(5, 6);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckParenthesisAndClosure)
		{
			RegExpFake regExp("A(BC)*D");
			Assert::AreEqual(8, regExp.nfa.getVertexCount());
			Assert::AreEqual(5, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(1, 2);
			etalon.addEdge(1, 5);
			etalon.addEdge(4, 5);
			etalon.addEdge(5, 1);
			etalon.addEdge(5, 6);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown4)
		{
			try
			{
				RegExpFake regExp("*ABC");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown5)
		{
			try
			{
				RegExpFake regExp("|ABC");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown6)
		{
			try
			{
				RegExpFake regExp("ABC|");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown7)
		{
			try
			{
				RegExpFake regExp("A|*BC");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckNestedParenthesisAndClosure)
		{
			RegExpFake regExp("A(B(CD)*E)*F");
			Assert::AreEqual(13, regExp.nfa.getVertexCount());
			Assert::AreEqual(10, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(1, 2);
			etalon.addEdge(1, 10);
			etalon.addEdge(3, 4);
			etalon.addEdge(3, 7);
			etalon.addEdge(6, 7);
			etalon.addEdge(7, 3);
			etalon.addEdge(7, 8);
			etalon.addEdge(9, 10);
			etalon.addEdge(10, 1);
			etalon.addEdge(10, 11);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown8)
		{
			try
			{
				RegExpFake regExp("AB|C");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckOrExpression)
		{
			RegExpFake regExp("A(B|C)");
			Assert::AreEqual(7, regExp.nfa.getVertexCount());
			Assert::AreEqual(4, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(1, 2);
			etalon.addEdge(1, 4);
			etalon.addEdge(3, 5);
			etalon.addEdge(5, 6);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown9)
		{
			try
			{
				RegExpFake regExp("(A|B|C)");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckNestedOrExpression)
		{
			RegExpFake regExp("A((B|C)|(D|E))");
			Assert::AreEqual(15, regExp.nfa.getVertexCount());
			Assert::AreEqual(12, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(1, 2);
			etalon.addEdge(1, 8);
			etalon.addEdge(2, 3);
			etalon.addEdge(2, 5);
			etalon.addEdge(4, 6);
			etalon.addEdge(6, 7);
			etalon.addEdge(7, 13);
			etalon.addEdge(8, 9);
			etalon.addEdge(8, 11);
			etalon.addEdge(10, 12);
			etalon.addEdge(12, 13);
			etalon.addEdge(13, 14);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown10)
		{
			try
			{
				RegExpFake regExp("A((B|C)|(|E))");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown11)
		{
			try
			{
				RegExpFake regExp("A((B|)|(D|E))");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown12)
		{
			try
			{
				RegExpFake regExp("A()");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(IfRegExpIsNotValidExceptionShouldBeThrown13)
		{
			try
			{
				RegExpFake regExp("A(())");
				Assert::Fail(L"Constructor should generate exception");
				unused_var(regExp);
			}
			catch (const std::exception&)
			{
			}
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckClosuredOrExpression)
		{
			RegExpFake regExp("A(B|C)*D");
			Assert::AreEqual(9, regExp.nfa.getVertexCount());
			Assert::AreEqual(7, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(1, 2);
			etalon.addEdge(1, 6);
			etalon.addEdge(1, 4);
			etalon.addEdge(3, 5);
			etalon.addEdge(5, 6);
			etalon.addEdge(6, 7);
			etalon.addEdge(6, 1);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckNestedClosuredOrExpression)
		{
			RegExpFake regExp("A((B|C)*|(D|E)*)*F");
			Assert::AreEqual(19, regExp.nfa.getVertexCount());
			Assert::AreEqual(21, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(1, 2);
			etalon.addEdge(1, 9);
			etalon.addEdge(1, 16);
			etalon.addEdge(2, 3);
			etalon.addEdge(2, 5);
			etalon.addEdge(2, 7);
			etalon.addEdge(4, 6);
			etalon.addEdge(6, 7);
			etalon.addEdge(7, 2);
			etalon.addEdge(7, 8);
			etalon.addEdge(8, 15);
			etalon.addEdge(9, 10);
			etalon.addEdge(9, 12);
			etalon.addEdge(9, 14);
			etalon.addEdge(11, 13);
			etalon.addEdge(13, 14);
			etalon.addEdge(14, 9);
			etalon.addEdge(14, 15);
			etalon.addEdge(15, 16);
			etalon.addEdge(16, 1);
			etalon.addEdge(16, 17);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(ConstructorBuildsNFA_CheckExampleFromCoursera)
		{
			RegExpFake regExp("((A*B|AC)D)");
			Assert::AreEqual(12, regExp.nfa.getVertexCount());
			Assert::AreEqual(9, regExp.nfa.getEdgesCount());
			DiGraph etalon(regExp.nfa.getVertexCount());
			etalon.addEdge(0, 1);
			etalon.addEdge(1, 2);
			etalon.addEdge(1, 6);
			etalon.addEdge(2, 3);
			etalon.addEdge(3, 2);
			etalon.addEdge(3, 4);
			etalon.addEdge(5, 8);
			etalon.addEdge(8, 9);
			etalon.addEdge(10, 11);
			Assert::IsTrue(etalon == regExp.nfa);
		}

		TEST_METHOD(CheckRecognizes_CheckExampleFromCoursera)
		{
			RegExpFake regExp("((A*B|AC)D)");

			Assert::IsTrue(regExp.recognizes("AABD"));
			Assert::IsTrue(regExp.recognizes("ABD"));
			Assert::IsTrue(regExp.recognizes("BD"));
			Assert::IsTrue(regExp.recognizes("ACD"));
			Assert::IsTrue(regExp.recognizes("ABDD"));

			Assert::IsFalse(regExp.recognizes("D"));

			Assert::IsTrue(regExp.recognizes("CCCCCAABD"));
			Assert::IsTrue(regExp.recognizes("CCCCCAABDCCCCCC"));
			Assert::IsTrue(regExp.recognizes("CCCCCAABDCCCCBDCC"));
		}

		TEST_METHOD(CheckFindOccurences_CheckExampleFromCoursera1)
		{
			RegExpFake regExp("((A*B|AC)D)");

			RegExpFake::MatchOccurences etalon = { RegExpFake::OneMatch(0, 4) };
			RegExpFake::MatchOccurences actual = regExp.findOccurences("AABD");
			Assert::AreEqual(etalon.size(), actual.size());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));			
		}

		TEST_METHOD(CheckFindOccurences_CheckExampleFromCoursera2)
		{
			RegExpFake regExp("((A*B|AC)D)");

			RegExpFake::MatchOccurences etalon = { RegExpFake::OneMatch(5, 4) };
			RegExpFake::MatchOccurences actual = regExp.findOccurences("CCCCCAABD");
			Assert::AreEqual(etalon.size(), actual.size());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(CheckFindOccurences_CheckExampleFromCoursera3)
		{
			RegExpFake regExp("((A*B|AC)D)");

			RegExpFake::MatchOccurences etalon = { RegExpFake::OneMatch(5, 4) };
			RegExpFake::MatchOccurences actual = regExp.findOccurences("CCCCCAABDCCCCCC");
			Assert::AreEqual(etalon.size(), actual.size());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(CheckFindOccurences_CheckExampleFromCoursera4)
		{
			RegExpFake regExp("((A*B|AC)D)");

			RegExpFake::MatchOccurences etalon = { RegExpFake::OneMatch(0, 4) };
			RegExpFake::MatchOccurences actual = regExp.findOccurences("AABDCCCCCC");
			Assert::AreEqual(etalon.size(), actual.size());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}
		
		TEST_METHOD(CheckFindOccurences_CheckExampleFromCoursera5)
		{
			RegExpFake regExp("((A*B|AC)D)");

			RegExpFake::MatchOccurences etalon = { RegExpFake::OneMatch(5, 4), RegExpFake::OneMatch(13, 2) };
			RegExpFake::MatchOccurences actual = regExp.findOccurences("CCCCCAABDCCCCBDCC");
			Assert::AreEqual(etalon.size(), actual.size());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(CheckFindOccurences_CheckExampleFromCoursera6)
		{
			RegExpFake regExp("((A*B|AC)D)");

			RegExpFake::MatchOccurences etalon = { RegExpFake::OneMatch(7, 4), RegExpFake::OneMatch(15, 2) };
			RegExpFake::MatchOccurences actual = regExp.findOccurences("CCACCBCAABDCCCCBDCAC");
			Assert::AreEqual(etalon.size(), actual.size());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(CheckFindOccurences_CheckExampleFromCoursera7)
		{
			RegExpFake regExp("((A*B|AC)D)");

			RegExpFake::MatchOccurences etalon = { RegExpFake::OneMatch(7, 4), RegExpFake::OneMatch(11, 3), RegExpFake::OneMatch(18, 2) };
			RegExpFake::MatchOccurences actual = regExp.findOccurences("CCACCBCAABDABDCCCCBDCAC");
			Assert::AreEqual(etalon.size(), actual.size());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}
	};
}