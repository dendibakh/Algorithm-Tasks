#include "stdafx.h"
#include "CppUnitTest.h"
#include "3WayRadixQuickSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace ThreeWayRadixQuickSortTest
{
	TEST_CLASS(ThreeWayRadixQuickSortTest)
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

			StrSet actual = ThreeWayRadixQuickSort(InitSet);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(TestMethod_SpacesInFront)
		{
			StrSet InitSet;

			InitSet.push_back(" she");
			InitSet.push_back(" sells");
			InitSet.push_back(" seashells");
			InitSet.push_back(" by");
			InitSet.push_back(" the");
			InitSet.push_back(" sea");
			InitSet.push_back(" shore");
			InitSet.push_back(" the");
			InitSet.push_back(" shells");
			InitSet.push_back(" she");
			InitSet.push_back(" sells");
			InitSet.push_back(" are");
			InitSet.push_back(" surely");
			InitSet.push_back(" seashells");

			StrSet etalon;

			etalon.push_back(" are");
			etalon.push_back(" by");
			etalon.push_back(" sea");
			etalon.push_back(" seashells");
			etalon.push_back(" seashells");
			etalon.push_back(" sells");
			etalon.push_back(" sells");
			etalon.push_back(" she");
			etalon.push_back(" she");
			etalon.push_back(" shells");
			etalon.push_back(" shore");
			etalon.push_back(" surely");
			etalon.push_back(" the");
			etalon.push_back(" the");

			StrSet actual = ThreeWayRadixQuickSort(InitSet);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(TestMethodIndexString)
		{
			IndexStrSet InitSet;
			
			string str_she("she");
			string str_sells("sells");
			string str_seashells("seashells");
			string str_by("by");
			string str_the("the");
			string str_sea("sea");
			string str_shore("shore");
			string str_shells("shells");
			string str_are("are");
			string str_surely("surely");			

			InitSet.push_back(str_she);
			InitSet.push_back(str_sells);
			InitSet.push_back(str_seashells);
			InitSet.push_back(str_by);
			InitSet.push_back(str_the);
			InitSet.push_back(str_sea);
			InitSet.push_back(str_shore);
			InitSet.push_back(str_the);
			InitSet.push_back(str_shells);
			InitSet.push_back(str_she);
			InitSet.push_back(str_sells);
			InitSet.push_back(str_are);
			InitSet.push_back(str_surely);
			InitSet.push_back(str_seashells);

			IndexStrSet etalon;

			etalon.push_back(str_are);
			etalon.push_back(str_by);
			etalon.push_back(str_sea);
			etalon.push_back(str_seashells);
			etalon.push_back(str_seashells);
			etalon.push_back(str_sells);
			etalon.push_back(str_sells);
			etalon.push_back(str_she);
			etalon.push_back(str_she);
			etalon.push_back(str_shells);
			etalon.push_back(str_shore);
			etalon.push_back(str_surely);
			etalon.push_back(str_the);
			etalon.push_back(str_the);

			IndexStrSet actual = ThreeWayRadixQuickSort(InitSet);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(TestMethodIndexString_SpacesInFront)
		{
			IndexStrSet InitSet;

			string str_she(" she");
			string str_sells(" sells");
			string str_seashells(" seashells");
			string str_by(" by");
			string str_the(" the");
			string str_sea(" sea");
			string str_shore(" shore");
			string str_shells(" shells");
			string str_are(" are");
			string str_surely(" surely");

			InitSet.push_back(str_she);
			InitSet.push_back(str_sells);
			InitSet.push_back(str_seashells);
			InitSet.push_back(str_by);
			InitSet.push_back(str_the);
			InitSet.push_back(str_sea);
			InitSet.push_back(str_shore);
			InitSet.push_back(str_the);
			InitSet.push_back(str_shells);
			InitSet.push_back(str_she);
			InitSet.push_back(str_sells);
			InitSet.push_back(str_are);
			InitSet.push_back(str_surely);
			InitSet.push_back(str_seashells);

			IndexStrSet etalon;

			etalon.push_back(str_are);
			etalon.push_back(str_by);
			etalon.push_back(str_sea);
			etalon.push_back(str_seashells);
			etalon.push_back(str_seashells);
			etalon.push_back(str_sells);
			etalon.push_back(str_sells);
			etalon.push_back(str_she);
			etalon.push_back(str_she);
			etalon.push_back(str_shells);
			etalon.push_back(str_shore);
			etalon.push_back(str_surely);
			etalon.push_back(str_the);
			etalon.push_back(str_the);

			IndexStrSet actual = ThreeWayRadixQuickSort(InitSet);
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}
	};
}