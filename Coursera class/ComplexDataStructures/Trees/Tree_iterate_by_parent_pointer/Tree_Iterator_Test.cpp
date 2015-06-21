#include "TestHarness.h"
#include "Tree.h"

using namespace MyTree; // MyTree::

const double Eps = 0.0001;

TEST(Tree_Iterator, Sample)
{
	Tree<int> T;
	T.Insert( 5 );
	T.Insert( 6 );
	T.Insert( 3 );
	T.Insert( 4 );
	T.Insert( 2 );
	T.Insert( 1 );

	Tree<int>::Iterator It = T.Begin();

	CHECK_EQUAL(1, *It);
	++It;
	CHECK_EQUAL(2, *It);
	++It;
	CHECK_EQUAL(3, *It);
	++It;
	CHECK_EQUAL(4, *It);
	++It;
	CHECK_EQUAL(5, *It);
	++It;
	CHECK_EQUAL(6, *It);
}

TEST(Tree_Iterator, Exception)
{
	try
	{
		Tree<int> T;
		T.Insert( 1 );
		T.Insert( 2 );
		T.Insert( 3 );

		Tree<int>::Iterator It = T.Begin();

		CHECK_EQUAL(1, *It);
		++It;
		CHECK_EQUAL(2, *It);
		++It;
		CHECK_EQUAL(3, *It);
		++It;
		CHECK_EQUAL(4, *It);

		FAIL("Должно быть исключение");
	}
	catch (std::exception& e)
	{
		CHECK_EQUAL("Недействительное состояние итератора", e.what());
	}
}

TEST(Tree_Iterator, OrderOfIncrement)
{
	Tree<int> T;
	T.Insert( 1 );
	T.Insert( 2 );
	T.Insert( 3 );

	Tree<int>::Iterator It = T.Begin();
	Tree<int>::Iterator It_Before;
	Tree<int>::Iterator It_After;

	It_After = It++;
	CHECK_EQUAL(2, *It);
	CHECK_EQUAL(1, *It_After);

	It_Before = ++It;
	CHECK_EQUAL(3, *It);
	CHECK_EQUAL(3, *It_Before);
}

TEST(Tree_Iterator, End)
{
	Tree<int> T;
	Tree<int>::Iterator It = T.Begin();

	CHECK(It == T.End());
}

TEST(Tree_Iterator, Assignment_EmptyToEmpty)
{
	Tree<int> T;

	Tree<int>::Iterator It1 = T.Begin();
	Tree<int>::Iterator It2 = It1;

	CHECK(It1 == T.End());
	CHECK(It2 == T.End());
}

TEST(Tree_Iterator, Assignment_EmptyToFilled)
{
	Tree<int> T1;
	T1.Insert( 1 );
	T1.Insert( 2 );
	T1.Insert( 3 );

	Tree<int> T2;

	Tree<int>::Iterator It1 = T1.Begin();
	Tree<int>::Iterator It2 = T2.Begin();

	It1 = It2;

	CHECK(It1 == T1.End());
	CHECK(It2 == T1.End());	
}

TEST(Tree_Iterator, Assignment_FilledToEmpty)
{
	Tree<int> T1;
	T1.Insert( 1 );
	T1.Insert( 2 );
	T1.Insert( 3 );

	Tree<int> T2;

	Tree<int>::Iterator It1 = T1.Begin();
	Tree<int>::Iterator It2 = T2.Begin();

	It2 = It1;

	CHECK_EQUAL(1, *It1);
	CHECK_EQUAL(1, *It2);
	++It1;
	++It2;
	CHECK_EQUAL(2, *It1);
	CHECK_EQUAL(2, *It2);
	++It1;
	++It2;
	CHECK_EQUAL(3, *It1);
	CHECK_EQUAL(3, *It2);
	++It1;
	++It2;
}

TEST(Tree_Iterator, Assignment_FilledToFilled)
{
	Tree<int> T1;
	T1.Insert( 1 );
	T1.Insert( 2 );
	T1.Insert( 3 );

	Tree<int> T2;
	T2.Insert( 4 );
	T2.Insert( 5 );
	T2.Insert( 6 );

	Tree<int>::Iterator It1 = T1.Begin();
	Tree<int>::Iterator It2 = T2.Begin();

	It2 = It1;

	CHECK_EQUAL(1, *It1);
	CHECK_EQUAL(1, *It2);
	++It1;
	++It2;
	CHECK_EQUAL(2, *It1);
	CHECK_EQUAL(2, *It2);
	++It1;
	++It2;
	CHECK_EQUAL(3, *It1);
	CHECK_EQUAL(3, *It2);
	++It1;
	++It2;
}

TEST(Tree_Iterator, OperatorOfEquality)
{
	Tree<int> T1;
	T1.Insert( 1 );
	T1.Insert( 2 );
	T1.Insert( 3 );

	Tree<int>::Iterator It1 = T1.Begin();
	Tree<int>::Iterator It2 = T1.Begin();

	CHECK(It1 == It1);
	CHECK(It1 == It2);
	CHECK(It2 == It2);

	Tree<int> T2;
	It2 = T2.Begin();

	CHECK(It1 != It2);
}

TEST(Tree_Iterator, Dereferencing)
{
	Tree<std::vector<int>> T;
	T.Insert( std::vector<int>(NULL, NULL) );
	Tree<std::vector<int>>::Iterator It = T.Begin();

	CHECK_EQUAL(0, It->size());
}

TEST(Iterator, LifeTime_Exception)
{
	Tree<int>::Iterator It;
	try
	{
		Tree<int> T;
		T.Insert( 1 );
		T.Insert( 2 );
		T.Insert( 3 );
		It = T.Begin();
		
		CHECK_EQUAL(1, *It);
		++It;
		CHECK_EQUAL(2, *It);
		++It;
		CHECK_EQUAL(3, *It);
		++It;
		CHECK(It == T.End());

		++It;
	}
	catch (std::exception& e)
	{
		CHECK_EQUAL("Недействительное состояние итератора", e.what());
	}

	try
	{
		*It;
		FAIL("Должно быть исключение");
	}
	catch (std::exception& e)
	{
		CHECK_EQUAL("Недействительное состояние итератора", e.what());
	}

	try
	{
		++It;
		FAIL("Должно быть исключение");
	}
	catch (std::exception& e)
	{
		CHECK_EQUAL("Недействительное состояние итератора", e.what());
	}

	try
	{
		It++;
		FAIL("Должно быть исключение");
	}
	catch (std::exception& e)
	{
		CHECK_EQUAL("Недействительное состояние итератора", e.what());
	}
}

TEST(Tree_Iterator, Passing)
{
	Tree<int> T;
	T.Insert( 3 );
	T.Insert( 2 );
	T.Insert( 1 );
	T.Insert( 5 );
	T.Insert( 4 );
	T.Insert( 6 );

	int i = 1;
	//const int CheckValue[6] = { 1, 2, 3, 4, 5, 6 };
	for (Tree<int>::Iterator It = T.Begin(); It != T.End(); ++It)
	{
		CHECK_EQUAL(i++, *It)
	}
}

TEST(Tree_Iterator, CrossPassing)
{
	Tree<int> T;
	T.Insert( 3 );
	T.Insert( 2 );
	T.Insert( 1 );
	T.Insert( 5 );
	T.Insert( 4 );
	T.Insert( 6 );

	Tree<int>::Iterator It1 = T.Begin();
	Tree<int>::Iterator It2 = T.Begin();

	CHECK_EQUAL(1, *It1);
	CHECK_EQUAL(1, *It2);

	++It2;
	CHECK_EQUAL(1, *It1);
	CHECK_EQUAL(2, *It2);

	++It1;
	++It2;
	CHECK_EQUAL(2, *It1);
	CHECK_EQUAL(3, *It2);

	++(++It1);
	++It2;
	CHECK_EQUAL(4, *It1);
	CHECK_EQUAL(4, *It2);

	++It1;
	CHECK_EQUAL(5, *It1);
	CHECK_EQUAL(4, *It2);

	++It1;
	++(++It2);
	CHECK_EQUAL(6, *It1);
	CHECK_EQUAL(6, *It2);

	++It1;
	++It2;
	CHECK(It1 == T.End());
	CHECK(It2 == T.End());
}

TEST(Tree_Iterator, IteratorToInsertItem)
{
	Tree<int> T;
	CHECK_EQUAL(3, *T.Insert( 3 ));
	CHECK_EQUAL(2, *T.Insert( 2 ));
	CHECK_EQUAL(1, *T.Insert( 1 ));
	CHECK_EQUAL(5, *T.Insert( 5 ));
	CHECK_EQUAL(4, *T.Insert( 4 ));
	CHECK_EQUAL(6, *T.Insert( 6 ));
}

TEST(Tree_Iterator, IteratorToFindItem)
{
	Tree<int> T;
	T.Insert( 3 );
	T.Insert( 2 );
	T.Insert( 1 );
	T.Insert( 5 );
	T.Insert( 4 );
	T.Insert( 6 );

	CHECK_EQUAL(3, *T.Find( 3 ));
	CHECK_EQUAL(2, *T.Find( 2 ));
	CHECK_EQUAL(1, *T.Find( 1 ));
	CHECK_EQUAL(5, *T.Find( 5 ));
	CHECK_EQUAL(4, *T.Find( 4 ));
	CHECK_EQUAL(6, *T.Find( 6 ));
}

TEST(Tree_Iterator, Erase)
{
	Tree<int> T;
	T.Insert( 3 );
	T.Insert( 2 );
	T.Insert( 1 );
	T.Insert( 5 );
	T.Insert( 4 );
	T.Insert( 6 );

	Tree<int>::Iterator It = T.Begin();

	T.Erase(It);
	T.Erase(It);
	T.Erase(It);
	T.Erase(It);
	T.Erase(It);
	T.Erase(It);
	CHECK(It == T.End());
}

//TEST(Tree_Iterator, Insert_and_Erase)
//{
//	Tree<int> T;
//	T.Insert( 1 );
//	T.Insert( 3 );
//	T.Insert( 5 );
//
//	Tree<int>::Iterator It1 = T.Begin();
//	CHECK_EQUAL(1, *It1);
//	++It1;
//	CHECK_EQUAL(3, *It1);
//
//	T.Insert( 0 );
//	Tree<int>::Iterator It2 = T.Begin();
//	CHECK_EQUAL(0, *It2);
//	++It2;
//	CHECK_EQUAL(1, *It2);
//
//	T.Insert( 2 );
//	++It2;
//	CHECK_EQUAL(2, *It2);
//
//	++It2;
//	CHECK_EQUAL(3, *It2);
//
//	++It1;
//	CHECK_EQUAL(5, *It1);
//	++It2;
//	CHECK_EQUAL(5, *It2);
//
//	T.Insert( 4 );
//	T.Insert( 6 );
//
//	T.Erase( 5 );
//	CHECK_EQUAL(6, *It1);
//	CHECK_EQUAL(6, *It2);
//
//	T.Erase( 6 );
//	CHECK_EQUAL(4, *It1);
//	CHECK_EQUAL(4, *It2);
//}
