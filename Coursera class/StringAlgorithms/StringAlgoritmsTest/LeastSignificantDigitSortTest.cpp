#include "stdafx.h"
#include "CppUnitTest.h"
#include "LeastSignificantDigitSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace LeastSignificantDigitSortTest
{
	TEST_CLASS(LeastSignificantDigitSortTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			StrSet         InitSet = { "dab",
				                       "add", 
									   "cab",
									   "fad",
									   "fee",
									   "bad",
									   "dad",
									   "bee",
									   "fed",
									   "bed",
									   "ebb",
									   "ace"
			                         };
			StrSet etalon =           { "ace",
										"add",
										"bad",
										"bed",
										"bee",
										"cab",
										"dab",
										"dad",
										"ebb",
										"fad",
										"fed",
										"fee"
									 };
			StrSet actual = LeastSignificantDigitSort(InitSet);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

	};
}