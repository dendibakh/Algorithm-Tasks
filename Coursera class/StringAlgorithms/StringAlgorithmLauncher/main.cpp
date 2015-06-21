#include <iostream>
#include "RwayTries.h"
#include "TernarySearchTrie.h"
#include "vld.h"

void RwayTriesTest1()
{
	RwayTrie trie;
}

void RwayTriesTest2()
{
	RwayTrie trie;
	trie.clear();
}

void RwayTriesTest3()
{
	RwayTrie trie;
	trie.height();
}

void RwayTriesTest4()
{
	RwayTrie trie;
	std::string str = "by";
	trie.insert(str, 1);
	trie.height();
}

void RwayTriesTest5()
{
	RwayTrie trie;
	std::string str = "she";
	trie.insert(str, 1);
	trie.height();
}

void RwayTriesTest6()
{
	RwayTrie trie;
	std::string str = "seashells";
	trie.insert(str, 1);
	trie.height();
}

void RwayTriesTest7()
{
	RwayTrie trie;
	std::string str1 = "by";
	std::string str2 = "she";
	trie.insert(str1, 1);
	trie.insert(str2, 2);
	trie.height();
}

void RwayTriesTest8()
{
	RwayTrie trie;
	std::string str1 = "by";
	std::string str2 = "seashells";
	std::string str3 = "she";
	trie.insert(str1, 1);
	trie.insert(str2, 2);
	trie.insert(str3, 3);
	trie.height();
}

void RwayTriesTest9()
{
	RwayTrie trie;
	std::string str1 = "by";
	std::string str2 = "seashells";
	std::string str3 = "she";
	trie.insert(str1, 1);
	trie.insert(str2, 2);
	trie.insert(str3, 3);
	trie.height();
	trie.clear();
	trie.height();
}

void RwayTriesTest10()
{
	RwayTrie trie;
	std::string str1 = "she";
	trie.insert(str1, 1);
	trie.exist(str1);
	trie.exist("sh");
	trie.exist("sha");
	trie.exist("sht");
	trie.exist("shee");
	trie.exist("she ");
	trie.exist("s");
	trie.exist("");
}

void RwayTriesTest11()
{
	RwayTrie trie;
	std::string str1 = "by";
	std::string str2 = "seashells";
	std::string str3 = "she";
	trie.insert(str1, 1);
	trie.insert(str2, 2);
	trie.insert(str3, 3);
	trie.exist(str1);
	trie.exist(str2);
	trie.exist(str3);

	trie.exist("sea");
	trie.exist("seashell");
	trie.exist("b");
	trie.exist("sh");
	trie.exist("shea");
	trie.exist("she ");
	trie.exist("s");
}

void RwayTriesTest12()
{
	RwayTrie trie;
	std::string str1 = "by";
	std::string str2 = "seashells";
	std::string str3 = "she";
	trie.insert(str1, 1);
	trie.insert(str2, 2);
	trie.insert(str3, 3);

	1, trie.getValue(str1);
	2, trie.getValue(str2);
	3, trie.getValue(str3);

	try
	{
		trie.getValue("sea");
	}
	catch (std::exception&) {}

	try
	{
		trie.getValue("seashell");
	}
	catch (std::exception&) {}

	try
	{
		trie.getValue("b");
	}
	catch (std::exception&) {}

	try
	{
		trie.getValue("sh");
	}
	catch (std::exception&) {}

	try
	{
		trie.getValue("shea");
	}
	catch (std::exception&) {}

	try
	{
		trie.getValue("she ");
	}
	catch (std::exception&) {}

	try
	{
		trie.getValue("s");
	}
	catch (std::exception&) {}
}

void RwayTriesTest13()
{
	RwayTrie trie;
	std::string str1 = "by";
	trie.insert(str1, 1);

	trie.exist(str1);
	trie.getValue(str1);

	trie.remove(str1);

	trie.exist(str1);
}

void RwayTriesTest14()
{
	RwayTrie trie;
	trie.exist("by");
	trie.exist(" ");
	trie.exist("");

	try
	{
		trie.getValue("");
	}
	catch (std::exception&) {}

	try
	{
		trie.getValue(" se");
	}
	catch (std::exception&) {}

	try
	{
		trie.remove("");
	}
	catch (std::exception&) {}

	try
	{
		trie.remove(" se");
	}
	catch (std::exception&) {}
}

void RwayTriesTest15()
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

	trie.exist(str1);
	trie.exist(str2);
	trie.exist(str3);
	trie.exist(str4);

	trie.remove(str1);

	trie.exist(str1);
	trie.exist(str2);
	trie.exist(str3);
	trie.exist(str4);

	trie.remove(str3);

	trie.exist(str1);
	trie.exist(str2);
	trie.exist(str3);
	trie.exist(str4);

	trie.remove(str4);

	trie.exist(str1);
	trie.exist(str2);
	trie.exist(str3);
	trie.exist(str4);
}

int main()
{
	// test memory leaks
	RwayTriesTest1();
	RwayTriesTest2();
	RwayTriesTest3();
	RwayTriesTest4();
	RwayTriesTest5();
	RwayTriesTest6();
	RwayTriesTest7();
	RwayTriesTest8();
	RwayTriesTest9();
	RwayTriesTest10();
	RwayTriesTest11();
	RwayTriesTest12();
	RwayTriesTest13();
	RwayTriesTest14();
	RwayTriesTest15();

	// print test
	{
		TernarySearchTrie trie;
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
		std::string traversal = trie.getLeftTraversal();
		std::cout << traversal;
	}

	{
		RwayTrie trie;
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
		std::string traversal = trie.getLeftTraversal();
		//std::cout << traversal;
	}

	return 0;
}