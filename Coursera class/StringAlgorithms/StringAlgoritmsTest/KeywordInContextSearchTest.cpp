#include "stdafx.h"
#include "KeywordInContextSearch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace KeywordInContextSearchTest
{
	TEST_CLASS(KeywordInContextSearchTest)
	{
	public:
		TEST_METHOD(TestMethod1_SmallText)
		{
			string str("Before our approach");
			KeywordInContextSearch kics(str);
			Assert::IsTrue(kics.findString("approach"));
			Assert::IsFalse(kics.findString("approasdach"));
		}

		TEST_METHOD(TestMethod_BigText_FindText)
		{
			string str("This book is intended to survey the most important computer algorithms in use today,");
			str += "and to teach fundamental techniques to the growing number of people in need of";
			str += "knowing them.It is intended for use as a textbook for a second course in computer";
			str += "science, after students have acquired basic programming skills and familiarity with computer";
			str += "systems.The book also may be useful for self - study or as a reference for people engaged in";
			str += "the development of computer systems or applications programs, since it contains implemen";
			str += "tations  of  useful  algorithms  and  detailed  information  on  performance  characteristics  and";
			str += "clients.The broad perspective taken makes the book an appropriate introduction to the field.";
			str += "the study of algorithms and data structuresis fundamental to any computer";
			str += "science curriculum, but it is not just for programmers and computer - science students.Every";
			str += "one who uses a computer wants it to run faster or to solve larger problems.The algorithms";
			str += "in this book represent a body of knowledge developed over the last 50 years that has become";
			str += "indispensable.From N - body simulation problems in physics to genetic - sequencing problems";
			str += "in molecular biology, the basic methods described here have become essential in scientific";
			str += "research; from architectural modeling systems to aircraft simulation, they have become es";
			str += "sential tools in engineering; and from database systems to internet search engines, they have";
			str += "become essential parts of modern software systems.And these are but a few examples—as the";
			str += "scope of computer applications continues to grow, so grows the impact of the basic methods";
			str += "covered here.";
			str += "Before developing our fundamental approach to studying algorithms, we develop data";
			str += "types for stacks, queues, and other low - level abstractions that we use throughout the book.";
			str += "Then we survey fundamental algorithms for sorting, searching, graphs, and strings.The last";
			str += "chapter is an overview placing the rest of the material in the book in a larger context.";

			KeywordInContextSearch kics(str);
			Assert::IsTrue(kics.findString("approach"));
			Assert::IsFalse(kics.findString("approasdach"));
		}

		TEST_METHOD(TestMethod_BigText_AmountOccurences)
		{
			string str("This book is intended to survey the most important computer algorithms in use today,");
			str += "and to teach fundamental techniques to the growing number of people in need of";
			str += "knowing them.It is intended for use as a textbook for a second course in computer";
			str += "science, after students have acquired basic programming skills and familiarity with computer";
			str += "systems.The book also may be useful for self - study or as a reference for people engaged in";
			str += "the development of computer systems or applications programs, since it contains implemen";
			str += "tations  of  useful  algorithms  and  detailed  information  on  performance  characteristics  and";
			str += "clients.The broad perspective taken makes the book an appropriate introduction to the field.";
			str += "the study of algorithms and data structuresis fundamental to any computer";
			str += "science curriculum, but it is not just for programmers and computer - science students.Every";
			str += "one who uses a computer wants it to run faster or to solve larger problems.The algorithms";
			str += "in this book represent a body of knowledge developed over the last 50 years that has become";
			str += "indispensable.From N - body simulation problems in physics to genetic - sequencing problems";
			str += "in molecular biology, the basic methods described here have become essential in scientific";
			str += "research; from architectural modeling systems to aircraft simulation, they have become es";
			str += "sential tools in engineering; and from database systems to internet search engines, they have";
			str += "become essential parts of modern software systems.And these are but a few examples—as the";
			str += "scope of computer applications continues to grow, so grows the impact of the basic methods";
			str += "covered here.";
			str += "Before developing our fundamental approach to studying algorithms, we develop data";
			str += "types for stacks, queues, and other low - level abstractions that we use throughout the book.";
			str += "Then we survey fundamental algorithms for sorting, searching, graphs, and strings.The last";
			str += "chapter is an overview placing the rest of the material in the book in a larger context.";

			KeywordInContextSearch kics(str);

			Assert::AreEqual(1u, kics.getAmountOfStringOccurences("approach"));
			Assert::AreEqual(6u, kics.getAmountOfStringOccurences("algorithms"));
			Assert::AreEqual(2u, kics.getAmountOfStringOccurences("methods"));
		}
	};
}