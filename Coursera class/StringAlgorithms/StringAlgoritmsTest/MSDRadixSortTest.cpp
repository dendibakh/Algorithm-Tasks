#include "stdafx.h"
#include "CppUnitTest.h"
#include "MSDRadixSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace MSDRadixSortTest
{
	TEST_CLASS(MSDRadixSortTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			StrSet InitSet;

			InitSet.push_back("she");
			InitSet.push_back("sells");
			InitSet.push_back("seashells");
			InitSet.push_back("by");
			InitSet.push_back("the");
			InitSet.push_back("sea");
			InitSet.push_back("shore");
			InitSet.push_back("the");
			InitSet.push_back("shells");
			InitSet.push_back("she");
			InitSet.push_back("sells");
			InitSet.push_back("are");
			InitSet.push_back("surely");
			InitSet.push_back("seashells");

			StrSet etalon;

			etalon.push_back("are");
			etalon.push_back("by");
			etalon.push_back("sea");
			etalon.push_back("seashells");
			etalon.push_back("seashells");
			etalon.push_back("sells");
			etalon.push_back("sells");
			etalon.push_back("she");
			etalon.push_back("she");
			etalon.push_back("shells");
			etalon.push_back("shore");
			etalon.push_back("surely");
			etalon.push_back("the");
			etalon.push_back("the");

			StrSet actual = MostSignificantDigitSort(InitSet);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

	};
}