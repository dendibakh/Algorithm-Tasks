#include "stdafx.h"
#include "CppUnitTest.h"
#include "TernarySearchTrie.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace TernarySearchTrieTest
{
	TEST_CLASS(TernarySearchTrieTest)
	{
	public:
		TEST_METHOD(TernarySearchTrieTest1)
		{
			TernarySearchTrieInt trie;
		}

		TEST_METHOD(TernarySearchTrieTest2)
		{
			TernarySearchTrieInt trie;
			trie.clear();
		}

		TEST_METHOD(TernarySearchTrieTest3)
		{
			TernarySearchTrieInt trie;
			Assert::AreEqual(0u, trie.height());
		}

		TEST_METHOD(TernarySearchTrieTest4)
		{
			TernarySearchTrieInt trie;
			std::string str = "by";
			trie.insert(str, 1);
			Assert::AreEqual(str.size(), trie.height());
		}

		TEST_METHOD(TernarySearchTrieTest5)
		{
			TernarySearchTrieInt trie;
			std::string str = "she";
			trie.insert(str, 1);
			Assert::AreEqual(str.size(), trie.height());
		}

		TEST_METHOD(TernarySearchTrieTest6)
		{
			TernarySearchTrieInt trie;
			std::string str = "seashells";
			trie.insert(str, 1);
			Assert::AreEqual(str.size(), trie.height());
		}

		TEST_METHOD(TernarySearchTrieTest7)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "by";
			std::string str2 = "she";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			Assert::AreEqual(str2.size(), trie.height());
		}

		TEST_METHOD(TernarySearchTrieTest8)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "by";
			std::string str2 = "seashells";
			std::string str3 = "she";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			Assert::AreEqual(str2.size(), trie.height());
		}

		TEST_METHOD(TernarySearchTrieTest9)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "by";
			std::string str2 = "seashells";
			std::string str3 = "she";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			Assert::AreEqual(str2.size(), trie.height());
			trie.clear();
			Assert::AreEqual(0u, trie.height());
		}

		TEST_METHOD(TernarySearchTrieTest10)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			trie.insert(str1, 1);
			Assert::IsTrue(trie.exist(str1));
			Assert::IsFalse(trie.exist("sh"));
			Assert::IsFalse(trie.exist("sha"));
			Assert::IsFalse(trie.exist("sht"));
			Assert::IsFalse(trie.exist("shee"));
			Assert::IsFalse(trie.exist("she "));
			Assert::IsFalse(trie.exist("s"));
			Assert::IsFalse(trie.exist(""));
		}

		TEST_METHOD(TernarySearchTrieTest11)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "by";
			std::string str2 = "seashells";
			std::string str3 = "she";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			Assert::IsTrue(trie.exist(str1));
			Assert::IsTrue(trie.exist(str2));
			Assert::IsTrue(trie.exist(str3));

			Assert::IsFalse(trie.exist("sea"));
			Assert::IsFalse(trie.exist("seashell"));
			Assert::IsFalse(trie.exist("b"));
			Assert::IsFalse(trie.exist("sh"));
			Assert::IsFalse(trie.exist("shea"));
			Assert::IsFalse(trie.exist("she "));
			Assert::IsFalse(trie.exist("s"));
		}

		TEST_METHOD(TernarySearchTrieTest12)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "by";
			std::string str2 = "seashells";
			std::string str3 = "she";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);

			Assert::AreEqual(1, trie.getValue(str1));
			Assert::AreEqual(2, trie.getValue(str2));
			Assert::AreEqual(3, trie.getValue(str3));

			try
			{
				Assert::AreEqual(0, trie.getValue("sea"));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				Assert::AreEqual(0, trie.getValue("seashell"));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				Assert::AreEqual(0, trie.getValue("b"));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				Assert::AreEqual(0, trie.getValue("sh"));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				Assert::AreEqual(0, trie.getValue("shea"));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				Assert::AreEqual(0, trie.getValue("she "));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				Assert::AreEqual(0, trie.getValue("s"));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}
		}

		TEST_METHOD(TernarySearchTrieTest13)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "by";
			trie.insert(str1, 1);

			Assert::IsTrue(trie.exist(str1));
			Assert::AreEqual(1, trie.getValue(str1));

			trie.remove(str1);

			Assert::IsFalse(trie.exist(str1));
		}

		TEST_METHOD(TernarySearchTrieTest14)
		{
			TernarySearchTrieInt trie;
			Assert::IsFalse(trie.exist("by"));
			Assert::IsFalse(trie.exist(" "));
			Assert::IsFalse(trie.exist(""));

			try
			{
				Assert::AreEqual(0, trie.getValue(""));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				Assert::AreEqual(0, trie.getValue(" se"));
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				trie.remove("");
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}

			try
			{
				trie.remove(" se");
				Assert::Fail(L"We shouldn't reach this code");
			}
			catch (std::exception&) {}
		}

		TEST_METHOD(TernarySearchTrieTest15)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);

			trie.remove(str2);

			Assert::IsTrue(trie.exist(str1));
			Assert::IsFalse(trie.exist(str2));
			Assert::IsTrue(trie.exist(str3));
			Assert::IsTrue(trie.exist(str4));

			trie.remove(str1);

			Assert::IsFalse(trie.exist(str1));
			Assert::IsFalse(trie.exist(str2));
			Assert::IsTrue(trie.exist(str3));
			Assert::IsTrue(trie.exist(str4));

			trie.remove(str3);

			Assert::IsFalse(trie.exist(str1));
			Assert::IsFalse(trie.exist(str2));
			Assert::IsFalse(trie.exist(str3));
			Assert::IsTrue(trie.exist(str4));

			trie.remove(str4);

			Assert::IsFalse(trie.exist(str1));
			Assert::IsFalse(trie.exist(str2));
			Assert::IsFalse(trie.exist(str3));
			Assert::IsFalse(trie.exist(str4));
		}

		TEST_METHOD(TernarySearchTrieTest16)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str2, str3, str4 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectAllKeys();
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest17)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str2, str3, str4, str5, str6 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectAllKeys();
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest18)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str2, str3};
			TernarySearchTrieInt::ListOfKeys actual = trie.getKeysWithPrefix("sh");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest19)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str2, str3, str4 };
			TernarySearchTrieInt::ListOfKeys actual = trie.getKeysWithPrefix("s");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest20)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "bypass";
			std::string str7 = "byd";
			std::string str8 = "byfly";
			std::string str9 = "bydlo";
			std::string str10 = "yb";
			std::string str11 = "bydka";
			std::string str12 = "byrka";
			std::string str13 = "byzka";
			std::string str14 = "bydk";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);
			trie.insert(str7, 7);
			trie.insert(str8, 8);
			trie.insert(str9, 9);
			trie.insert(str10, 10);
			trie.insert(str11, 11);
			trie.insert(str12, 12);
			trie.insert(str13, 13);
			trie.insert(str14, 14);

			TernarySearchTrieInt::ListOfKeys expected = { str7, str9, str11, str14 };
			TernarySearchTrieInt::ListOfKeys actual = trie.getKeysWithPrefix("byd");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest21)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str2, str3 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("sh");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest22)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str2, str3, str4 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("s.");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest23)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str2, str3, str4, str5, str6 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest24)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str2, str3, str4, str5, str6 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("..");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest25)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str3, str4};
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("...");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest26)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str3, str4 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".....");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest27)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str4 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".........");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest28)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("..........");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest29)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str5 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("b.");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest30)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str6 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".b");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest31)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = {  };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".by");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest32)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = {};
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".e.r");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest33)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str4 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".e.s");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest34)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = {  };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".h..h");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest35)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			TernarySearchTrieInt::ListOfKeys expected = { str4 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".e..h");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest36)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "bypass";
			std::string str7 = "byd";
			std::string str8 = "byfly";
			std::string str9 = "bydlo";
			std::string str10 = "yb";
			std::string str11 = "bydka";
			std::string str12 = "byrka";
			std::string str13 = "byzka";
			std::string str14 = "bydk";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);
			trie.insert(str7, 7);
			trie.insert(str8, 8);
			trie.insert(str9, 9);
			trie.insert(str10, 10);
			trie.insert(str11, 11);
			trie.insert(str12, 12);
			trie.insert(str13, 13);
			trie.insert(str14, 14);

			TernarySearchTrieInt::ListOfKeys expected = { str9, str11 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("byd..");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest37)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "bypass";
			std::string str7 = "byd";
			std::string str8 = "byfly";
			std::string str9 = "bydlo";
			std::string str10 = "yb";
			std::string str11 = "bydka";
			std::string str12 = "byrka";
			std::string str13 = "byzka";
			std::string str14 = "bydk";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);
			trie.insert(str7, 7);
			trie.insert(str8, 8);
			trie.insert(str9, 9);
			trie.insert(str10, 10);
			trie.insert(str11, 11);
			trie.insert(str12, 12);
			trie.insert(str13, 13);
			trie.insert(str14, 14);

			TernarySearchTrieInt::ListOfKeys expected = { str11, str12, str13 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("by.ka");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest38)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "bypass";
			std::string str7 = "byd";
			std::string str8 = "byfly";
			std::string str9 = "bydlo";
			std::string str10 = "yb";
			std::string str11 = "bydka";
			std::string str12 = "byrka";
			std::string str13 = "byzka";
			std::string str14 = "bydk";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);
			trie.insert(str7, 7);
			trie.insert(str8, 8);
			trie.insert(str9, 9);
			trie.insert(str10, 10);
			trie.insert(str11, 11);
			trie.insert(str12, 12);
			trie.insert(str13, 13);
			trie.insert(str14, 14);

			TernarySearchTrieInt::ListOfKeys expected = { str4, str6 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch("......");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest39)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "bypass";
			std::string str7 = "byd";
			std::string str8 = "byfly";
			std::string str9 = "bydlo";
			std::string str10 = "yb";
			std::string str11 = "bydka";
			std::string str12 = "byrka";
			std::string str13 = "byzka";
			std::string str14 = "bydk";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);
			trie.insert(str7, 7);
			trie.insert(str8, 8);
			trie.insert(str9, 9);
			trie.insert(str10, 10);
			trie.insert(str11, 11);
			trie.insert(str12, 12);
			trie.insert(str13, 13);
			trie.insert(str14, 14);

			TernarySearchTrieInt::ListOfKeys expected = { str11, str12, str13, str14 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".y.k");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest40)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "marcin";
			std::string str2 = "igor";
			std::string str3 = "rafal";
			std::string str4 = "alex";
			std::string str5 = "denis";
			std::string str6 = "ivan";
			std::string str7 = "mike";
			std::string str8 = "jan";
			std::string str9 = "piotr";
			std::string str10 = "tomas";
			std::string str11 = "szymon";
			std::string str12 = "marek";
			std::string str13 = "damian";
			std::string str14 = "egor";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);
			trie.insert(str7, 7);
			trie.insert(str8, 8);
			trie.insert(str9, 9);
			trie.insert(str10, 10);
			trie.insert(str11, 11);
			trie.insert(str12, 12);
			trie.insert(str13, 13);
			trie.insert(str14, 14);

			TernarySearchTrieInt::ListOfKeys expected = { str1, str3, str8, str12, str13 };
			TernarySearchTrieInt::ListOfKeys actual = trie.collectKeysThatMatch(".a.");
			std::sort(expected.begin(), expected.end());
			std::sort(actual.begin(), actual.end());
			Assert::AreEqual(expected.size(), actual.size());
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TernarySearchTrieTest41)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			Assert::IsTrue(str2 == trie.getLongestKeyWithPrefix("shop"));
		}

		TEST_METHOD(TernarySearchTrieTest42)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			Assert::IsTrue(str2 == trie.getLongestKeyWithPrefix("shor"));
		}

		TEST_METHOD(TernarySearchTrieTest43)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			Assert::IsTrue(str3 == trie.getLongestKeyWithPrefix("shore"));
		}

		TEST_METHOD(TernarySearchTrieTest44)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			Assert::IsTrue(str1 == trie.getLongestKeyWithPrefix("sheet"));
		}

		TEST_METHOD(TernarySearchTrieTest45)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			Assert::IsTrue(str4 == trie.getLongestKeyWithPrefix("seashellsort"));
		}

		TEST_METHOD(TernarySearchTrieTest46)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			Assert::IsTrue(std::string("") == trie.getLongestKeyWithPrefix("s"));
		}

		TEST_METHOD(TernarySearchTrieTest47)
		{
			TernarySearchTrieInt trie;
			std::string str1 = "she";
			std::string str2 = "sh";
			std::string str3 = "shore";
			std::string str4 = "seashells";
			std::string str5 = "by";
			std::string str6 = "yb";
			trie.insert(str1, 1);
			trie.insert(str2, 2);
			trie.insert(str3, 3);
			trie.insert(str4, 4);
			trie.insert(str5, 5);
			trie.insert(str6, 6);

			Assert::IsTrue(str5 == trie.getLongestKeyWithPrefix("bycicle"));
		}

		TEST_METHOD(TernarySearchTrieTest48)
		{
			LZW_TST trie;
			std::string str1 = "by";
			std::string str2 = "seashells";
			std::string str3 = "she";
			trie.insert(str1);
			trie.insert(str2);
			trie.insert(str3);

			Assert::AreEqual(static_cast<short>(0), trie.getValue(str1));
			Assert::AreEqual(static_cast<short>(1), trie.getValue(str2));
			Assert::AreEqual(static_cast<short>(2), trie.getValue(str3));
		}
	};
}