#include "stdafx.h"
#include "CppUnitTest.h"
#include "RwayTries.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace RwayTriesTest
{
        TEST_CLASS(RwayTriesTest)
        {
        public:
				TEST_METHOD(RwayTriesTest1)
                {
                    RwayTrie trie;
                }                               

				TEST_METHOD(RwayTriesTest2)
				{
					RwayTrie trie;
					trie.clear();
				}

				TEST_METHOD(RwayTriesTest3)
                {
                    RwayTrie trie;
					Assert::AreEqual(0u, trie.height());
                }                               
				
				TEST_METHOD(RwayTriesTest4)
				{
					RwayTrie trie;
					std::string str = "by";
					trie.insert(str, 1);
					Assert::AreEqual(str.size(), trie.height());
				}

				TEST_METHOD(RwayTriesTest5)
				{
					RwayTrie trie;
					std::string str = "she";
					trie.insert(str, 1);
					Assert::AreEqual(str.size(), trie.height());
				}

				TEST_METHOD(RwayTriesTest6)
				{
					RwayTrie trie;
					std::string str = "seashells";
					trie.insert(str, 1);
					Assert::AreEqual(str.size(), trie.height());
				}

				TEST_METHOD(RwayTriesTest7)
				{
					RwayTrie trie;
					std::string str1 = "by";
					std::string str2 = "she";
					trie.insert(str1, 1);
					trie.insert(str2, 2);
					Assert::AreEqual(str2.size(), trie.height());
				}

				TEST_METHOD(RwayTriesTest8)
				{
					RwayTrie trie;
					std::string str1 = "by";
					std::string str2 = "seashells";
					std::string str3 = "she";
					trie.insert(str1, 1);
					trie.insert(str2, 2);
					trie.insert(str3, 3);
					Assert::AreEqual(str2.size(), trie.height());
				}

				TEST_METHOD(RwayTriesTest9)
				{
					RwayTrie trie;
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

				TEST_METHOD(RwayTriesTest10)
				{
					RwayTrie trie;
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

				TEST_METHOD(RwayTriesTest11)
				{
					RwayTrie trie;
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

				TEST_METHOD(RwayTriesTest12)
				{
					RwayTrie trie;
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
					catch (std::exception&) {	}

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

				TEST_METHOD(RwayTriesTest13)
				{
					RwayTrie trie;
					std::string str1 = "by";
					trie.insert(str1, 1);

					Assert::IsTrue(trie.exist(str1));
					Assert::AreEqual(1, trie.getValue(str1));
					
					trie.remove(str1);

					Assert::IsFalse(trie.exist(str1));
				}

				TEST_METHOD(RwayTriesTest14)
				{
					RwayTrie trie;
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

				TEST_METHOD(RwayTriesTest15)
				{
					RwayTrie trie;
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
        };
}