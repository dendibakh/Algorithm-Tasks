#include "stdafx.h"
#include "IndexString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IndexStringTest
{
	TEST_CLASS(IndexStringTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			string InitSet("We think in generalities, but we live in details.");
			IndexString indexStr(InitSet, 12, 24);
			
			string etalon("generalities");

			string actual(indexStr.getString());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(TestMethod2)
		{
			string InitSet("We think in generalities, but we live in details.");
			IndexString indexStr(InitSet, 4, 9);

			string etalon("hink ");

			string actual(indexStr.getString());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(TestMethod3)
		{
			string InitSet("We think in generalities, but we live in details.");
			IndexString indexStr(InitSet, 4, 9);
			IndexString copyIndexStr(indexStr);

			string etalon("hink ");

			string actual(copyIndexStr.getString());
			Assert::IsTrue(std::equal(etalon.begin(), etalon.end(), actual.begin()));
		}

		TEST_METHOD(TestMethod4)
		{
			string InitSet("We think in generalities, but we live in details.");
			IndexString indexStr(InitSet, 4, 9);
			IndexString copyIndexStr(InitSet, 3, 8);

			string etalon1("think");
			string actual1(copyIndexStr.getString());
			Assert::IsTrue(std::equal(etalon1.begin(), etalon1.end(), actual1.begin()));

			string etalon2("hink ");
			copyIndexStr = indexStr;
			string actual2(copyIndexStr.getString());
			Assert::IsTrue(std::equal(etalon2.begin(), etalon2.end(), actual2.begin()));
		}

		TEST_METHOD(TestMethodExchangeStrings)
		{
			string InitString("think");
			IndexString indexStr(InitString);
			string copyString("generalities");
			IndexString copyIndexStr(copyString);

			IndexString temp(copyIndexStr);
			copyIndexStr = indexStr;
			indexStr = temp;

			string actualStr(indexStr.getString());
			string actualIndexStr(copyIndexStr.getString());
			Assert::IsTrue(std::equal(copyString.begin(), copyString.end(), actualStr.begin()));
			Assert::IsTrue(std::equal(InitString.begin(), InitString.end(), actualIndexStr.begin()));
		}

		TEST_METHOD(TestMethod6)
		{
			string InitSet("We think in generalities, but we live in details.");
			IndexString copyIndexStr(InitSet, 3, 8);
						
			Assert::IsTrue(copyIndexStr[0] == 't');
			Assert::IsTrue(copyIndexStr[1] == 'h');
			Assert::IsTrue(copyIndexStr[2] == 'i');
			Assert::IsTrue(copyIndexStr[3] == 'n');
			Assert::IsTrue(copyIndexStr[4] == 'k');
		}
	};
}