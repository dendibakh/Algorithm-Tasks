#include "stdafx.h"
#include "CppUnitTest.h"
#include "KeyIndexCounting.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace StringAlgoritmsTest
{		
	TEST_CLASS(KeyIndexCountingTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			string etalon = "aabbbcddefff";
			string actual = KeyIndexCounting("dacffbdbfbea");
			Assert::IsTrue(etalon == actual);
		}

	};
}