#include "stdafx.h"
#include "CppUnitTest.h"
#include "MyVector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace MyVector;

namespace MyVectorUnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestConstruct)
		{
			vector<int> vec;
		};

		TEST_METHOD(TestEmpty)
		{
			vector<int> vec;
			Assert::IsTrue(vec.isEmpty());
		};

		TEST_METHOD(TestEmpty2)
		{
			vector<int> vec;
			Assert::IsTrue(vec.isEmpty());
			vec.push_back(1);
			Assert::IsFalse(vec.isEmpty());
			Assert::AreEqual(1, vec.pop_back());
			Assert::IsTrue(vec.isEmpty());
		};

		TEST_METHOD(TestCount)
		{
			vector<int> vec;
			Assert::AreEqual(0, vec.getCount());
			vec.push_back(1);
			Assert::AreEqual(1, vec.getCount());
			Assert::AreEqual(1, vec.pop_back());
			Assert::AreEqual(0, vec.getCount());
		};

		TEST_METHOD(TestPushPop)
		{
			vector<int> vec;
			vec.push_back(1);
			vec.push_back(2);
			vec.push_back(3);
			vec.push_back(4);

			Assert::AreEqual(4, vec.pop_back());
			Assert::AreEqual(3, vec.pop_back());
			Assert::AreEqual(2, vec.pop_back());
			Assert::AreEqual(1, vec.pop_back());

			try
			{
				Assert::AreEqual(0, vec.pop_back());
				Assert::Fail(L"Should be an exception");
			}
			catch (std::exception&)
			{
			}
		};

		TEST_METHOD(TestPushPop2)
		{
			vector<int> vec;
			vec.push_back(1);
			vec.push_front(2);
			vec.push_back(3);
			vec.push_front(4);

			Assert::AreEqual(4, vec.pop_front());
			Assert::AreEqual(3, vec.pop_back());
			Assert::AreEqual(1, vec.pop_back());
			Assert::AreEqual(2, vec.pop_front());
		};

		TEST_METHOD(TestAccesByIndex)
		{
			vector<int> vec;
			vec.push_back(1);
			vec.push_front(2);
			vec.push_back(3);
			vec.push_front(4);

			Assert::AreEqual(4, vec[0]);
			Assert::AreEqual(2, vec[1]);
			Assert::AreEqual(1, vec[2]);
			Assert::AreEqual(3, vec[3]);

			try
			{
				Assert::AreEqual(0, vec[4]);
				Assert::Fail(L"Should be an exception");
			}
			catch (std::exception&)
			{
			}
		};

		TEST_METHOD(TestIteratorConstruct)
		{
			vector<int> vec;
			vector<int>::iterator i1;
			vector<int>::iterator i2(vec.begin());
			vector<int>::iterator i3(vec.end());

			vector<int>::iterator i4 = vec.begin();
			vector<int>::iterator i5 = vec.begin();
		};

		TEST_METHOD(TestIteratorEqual)
		{
			vector<int> vec;
			vector<int>::iterator i1;
			vector<int>::iterator i2(vec.begin());
			vector<int>::iterator i3(vec.end());

			Assert::IsTrue(i1 == i2); // Todo:: make it false
			Assert::IsTrue(i1 == i3); // Todo:: make it false
			Assert::IsTrue(i2 == i3); 

			vec.push_back(1);

			vector<int>::iterator i4 = vec.begin();
			vector<int>::iterator i5 = vec.end();

			Assert::IsTrue(i4 != i5);
		};

		TEST_METHOD(TestIteratorMove)
		{
			vector<int> vec;
			vec.push_back(1);
			vec.push_front(2);
			vec.push_back(3);
			vec.push_front(4);
			for (vector<int>::iterator i = vec.begin(); i != vec.begin(); ++i)
			{

			}
			vector<int>::iterator j = vec.begin();
			Assert::AreEqual(4, *j);
			++j;
			Assert::AreEqual(2, *j);
			j++;
			Assert::AreEqual(1, *j);
			++j;
			Assert::AreEqual(3, *j);
			++j;
			Assert::IsTrue(j == vec.end());
		};

		TEST_METHOD(TestInsertInBegin)
		{
			vector<int> vec;
			vector<int>::iterator i = vec.begin();
			i = vec.insert(i, 1);
			i = vec.insert(i, 2);
			i = vec.insert(i, 3);
			i = vec.insert(i, 4);

			vector<int>::iterator j = vec.begin();
			Assert::AreEqual(4, *j);
			++j;
			Assert::AreEqual(3, *j);
			j++;
			Assert::AreEqual(2, *j);
			++j;
			Assert::AreEqual(1, *j);
			++j;
			Assert::IsTrue(j == vec.end());
		};

		TEST_METHOD(TestInsertInEnd)
		{
			vector<int> vec;
			vector<int>::iterator i = vec.end();
			i = vec.insert(i, 1);
			i = vec.end();
			i = vec.insert(i, 2);
			i = vec.end();
			i = vec.insert(i, 3);
			i = vec.end();
			i = vec.insert(i, 4);

			vector<int>::iterator j = vec.begin();
			Assert::AreEqual(1, *j);
			++j;
			Assert::AreEqual(2, *j);
			j++;
			Assert::AreEqual(3, *j);
			++j;
			Assert::AreEqual(4, *j);
			++j;
			Assert::IsTrue(j == vec.end());
		};

		TEST_METHOD(TestMixedInsert)
		{
			vector<int> vec;
			vec.push_back(1);
			vec.push_back(5);
			vec.push_back(7);
			vector<int>::iterator i = vec.begin();
			i++;
			i = vec.insert(i, 3);
			i = vec.insert(i, 2);
			i++;
			i++;
			i = vec.insert(i, 4);
			i++;
			i++;
			i = vec.insert(i, 6);
			i = vec.begin();
			i = vec.insert(i, 0);
			i = vec.end();
			i = vec.insert(i, 8);
			Assert::AreEqual(8, *i);
			Assert::IsTrue(i != vec.end());

			vector<int>::iterator j = vec.begin();
			Assert::AreEqual(0, *j);
			++j;
			Assert::AreEqual(1, *j);
			++j;
			Assert::AreEqual(2, *j);
			j++;
			Assert::AreEqual(3, *j);
			++j;
			Assert::AreEqual(4, *j);
			++j;
			Assert::AreEqual(5, *j);
			++j;
			Assert::AreEqual(6, *j);
			j++;
			Assert::AreEqual(7, *j);
			++j;
			Assert::AreEqual(8, *j);
			++j;
			Assert::IsTrue(j == vec.end());
		};

		TEST_METHOD(TestEraseFromBegin)
		{
			vector<int> vec;
			vec.push_back(1);
			vec.push_back(2);
			vec.push_back(3);
			vec.push_back(4);
			vec.push_back(5);
			vec.push_back(6);
			vector<int>::iterator i = vec.begin();
			i = vec.erase(i);
			i = vec.erase(i);
			i = vec.erase(i);
			i = vec.erase(i);
			i = vec.erase(i);

			Assert::AreEqual(6, *i);
			++i;
			Assert::IsTrue(i == vec.end());
			vec.erase(vec.begin());
			Assert::IsTrue(vec.isEmpty());
		};

		TEST_METHOD(TestEraseFromEnd)
		{
			vector<int> vec;
			vec.push_back(1);
			vec.push_back(2);
			vec.push_back(3);
			vec.push_back(4);
			vec.push_back(5);
			vec.push_back(6);
			vector<int>::iterator i = vec.begin(); i++; i++; i++; i++; i++;
			Assert::AreEqual(6, *i);
			i = vec.erase(i);
			Assert::IsTrue(i == vec.end());
			i = vec.begin(); i++; i++; i++; i++;
			Assert::AreEqual(5, *i);
			i = vec.erase(i);
			Assert::IsTrue(i == vec.end());
			i = vec.begin(); i++; i++; i++;
			Assert::AreEqual(4, *i);
			i = vec.erase(i);
			Assert::IsTrue(i == vec.end());
			i = vec.begin(); i++; i++;
			Assert::AreEqual(3, *i);
			i = vec.erase(i);
			Assert::IsTrue(i == vec.end());
			i = vec.begin(); i++;
			Assert::AreEqual(2, *i);
			i = vec.erase(i);
			Assert::IsTrue(i == vec.end());
			i = vec.begin(); 
			Assert::AreEqual(1, *i);
			i = vec.erase(i);
			Assert::IsTrue(i == vec.end());

			Assert::IsTrue(vec.isEmpty());
		};

		TEST_METHOD(TestMixedErase)
		{
			vector<int> vec;
			vec.push_back(1);
			vec.push_back(2);
			vec.push_back(3);
			vec.push_back(4);
			vec.push_back(5);
			vec.push_back(6);
			vec.push_back(7);
			vec.push_back(8);
			
			vector<int>::iterator i = vec.begin(); 
			i++; 
			i++;
			Assert::AreEqual(3, *i);
			i = vec.erase(i);
			Assert::AreEqual(4, *i);
			i++;
			i++;
			Assert::AreEqual(6, *i);
			i = vec.erase(i);
			Assert::AreEqual(7, *i);
			
			i = vec.begin();
			i++;
			Assert::AreEqual(2, *i);
			i = vec.erase(i);
			Assert::AreEqual(4, *i);
			i++;
			Assert::AreEqual(5, *i);
			i = vec.erase(i);
			Assert::AreEqual(7, *i);
			i++;
			Assert::AreEqual(8, *i);
			i = vec.erase(i);
			Assert::IsTrue(i == vec.end());

			i = vec.begin(); 
			i++;
			Assert::AreEqual(4, *i);
			i = vec.erase(i);
			Assert::AreEqual(7, *i);
			i = vec.erase(i);
			Assert::IsTrue(i == vec.end());

			i = vec.erase(vec.begin());
			
			Assert::IsTrue(vec.isEmpty());
		};
	};
}
