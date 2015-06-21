#include "TestHarness.h"
#include "Matrix.h"
#include "Tree.h"

#include <string>

using namespace std; // std::

const double Eps = 0.0001;

TEST(Tree, Sample)
{
	Tree<int> T;
	T.Insert( 1 );

	T.Remove( 1 );

	CHECK( T.IsEmpty() );
}

TEST(Tree, IsEmpty)
{
	Tree<int> T;

	CHECK( T.IsEmpty() );
}

TEST(Tree, Height_int)
{
	Tree<int> T;
	T.Insert( 5 );
	T.Insert( 6 );
	T.Insert( 3 );
	T.Insert( 4 );
	T.Insert( 2 );
	T.Insert( 1 );

	CHECK_EQUAL(4, T.Height());
}

TEST(Tree, Height_double)
{
	Tree<double> T;

	T.Insert( 3.0 );
	T.Insert( 2.0 );
	T.Insert( 1.0 );
	T.Insert( 5.0 );
	T.Insert( 4.0 );
	T.Insert( 6.0 );
	T.Insert( 5.5 );
	T.Insert( 5.4 );
	T.Insert( 6.5 );
	T.Insert( 4.5 );
	T.Insert( 3.5 );

	CHECK_EQUAL(5, T.Height());
}

TEST(Tree, Assignment_ItSelf_Empty)
{
	Tree<int> T;
	T = T;

	CHECK( T.IsEmpty() );
}

TEST(Tree, Assignment_ItSelf_int)
{
	Tree<int> T;
	T.Insert( 1 );
	T.Insert( 2 );
	T.Insert( 3 );
	T = T;

	CHECK( T.Find(1) );
	CHECK( T.Find(2) );
	CHECK( T.Find(3) );
}

TEST(Tree, Assignment_int)
{
	Tree<int> T1;
	T1.Insert( 1 );
	T1.Insert( 2 );
	T1.Insert( 3 );

	Tree<int> T2;
	T2.Insert( 4 );
	T2.Insert( 5 );
	T2.Insert( 6 );

	T1 = T2;

	T1.Remove( 4 );
	T1.Remove( 5 );
	T1.Remove( 6 );

	CHECK( T1.IsEmpty() );

	CHECK( !T2.Find(1) );
	CHECK( !T2.Find(2) );
	CHECK( !T2.Find(3) );
	CHECK( T2.Find(4) );
	CHECK( T2.Find(5) );
	CHECK( T2.Find(6) );
}

TEST(Tree, Copy_Empty)
{
	Tree<int> T1;
	Tree<int> T2(T1);

	CHECK( T2.IsEmpty() );
}

TEST(Tree, Copy_int)
{
	Tree<int> T1;
	T1.Insert( 1 );
	T1.Insert( 2 );
	T1.Insert( 3 );

	Tree<int> T2(T1);

	T1.Remove( 1 );
	T1.Remove( 2 );
	T1.Remove( 3 );

	CHECK( T1.IsEmpty() );

	CHECK( T2.Find(1) );
	CHECK( T2.Find(2) );
	CHECK( T2.Find(3) );
}

TEST(Tree, Insert_Find)
{
	Tree<int> T;
	T.Insert( 1 );
	T.Insert( 2 );
	T.Insert( 3 );

	CHECK( T.Find(1) );
	CHECK( T.Find(2) );
	CHECK( T.Find(3) );
}

TEST(Tree, Remove_FromEnd)
{
	Tree<int> T;
	T.Insert( 1 );
	T.Insert( 2 );
	T.Insert( 3 );

	T.Remove( 3 );

	CHECK( T.Find(1) );
	CHECK( T.Find(2) );
	CHECK( !T.Find(3) );
}

TEST(Tree, Remove_FromRoot)
{
	Tree<int> T;
	T.Insert( 1 );
	T.Insert( 2 );
	T.Insert( 3 );

	T.Remove( 1 );

	CHECK( !T.Find(1) );
	CHECK( T.Find(2) );
	CHECK( T.Find(3) );
}

TEST(Tree, Remove_FromMiddle_int)
{
	Tree<int> T;
	T.Insert( 3 );
	T.Insert( 2 );
	T.Insert( 1 );
	T.Insert( 5 );
	T.Insert( 4 );
	T.Insert( 6 );

	T.Remove( 5 );
	T.Remove( 3 );
	T.Remove( 2 );

	CHECK( T.Find(1) );
	CHECK( !T.Find(2) );
	CHECK( !T.Find(3) );
	CHECK( T.Find(4) );
	CHECK( !T.Find(5) );
	CHECK( T.Find(6) );
}

TEST(Tree, Remove_FromMiddle_double)
{
	Tree<double> T;
	T.Insert( 3.0 );
	T.Insert( 2.0 );
	T.Insert( 1.0 );
	T.Insert( 5.0 );
	T.Insert( 4.0 );
	T.Insert( 6.0 );
	T.Insert( 5.5 );
	T.Insert( 6.5 );
	T.Insert( 4.5 );
	T.Insert( 3.5 );

	T.Remove( 5.0 );
	T.Remove( 3.5 );
	T.Remove( 4.0 );
	
	CHECK( T.Find(1.0) );
	CHECK( T.Find(2.0) );
	CHECK( T.Find(3.0) );
	CHECK( !T.Find(3.5) );
	CHECK( !T.Find(4.0) );
	CHECK( T.Find(4.5) );
	CHECK( !T.Find(5.0) );
	CHECK( T.Find(5.5) );
	CHECK( T.Find(6.0) );
	CHECK( T.Find(6.5) );
}

TEST(Tree, Remove_Exception)
{
	try
	{
		Tree<double> T;
		T.Insert( 1.0 );
		T.Insert( 2.0 );
		T.Insert( 3.0 );

		T.Remove( 4.0 );

		FAIL("Должно быть исключение");
	}
	catch (exception& e)
	{
		CHECK_EQUAL("Элемент отсутствует", e.what());
	}
}

TEST(Tree, GetLE_Equal_int)
{
	Tree<int> T;
	T.Insert( 1 );
	T.Insert( 2 );
	T.Insert( 3 );

	CHECK_EQUAL(1, T.GetLE(1));
	CHECK_EQUAL(3, T.GetLE(3));
}

TEST(Tree, GetLE_NotEqual_int)
{
	Tree<int> T;
	T.Insert( 1 );
	T.Insert( 3 );
	T.Insert( 4 );

	CHECK_EQUAL(1, T.GetLE(2));
	CHECK_EQUAL(4, T.GetLE(5));
}

TEST(Tree, GetLE_Equal_double)
{
	Tree<double> T;
	T.Insert( 1.0 );
	T.Insert( 2.0 );
	T.Insert( 3.0 );

	DOUBLES_EQUAL(1.0, T.GetLE(1.0), Eps);
	DOUBLES_EQUAL(3.0, T.GetLE(3.0), Eps);
}

TEST(Tree, GetLE_NotEqual_double)
{
	Tree<double> T;
	T.Insert( 1.0 );
	T.Insert( 2.0 );
	T.Insert( 3.0 );

	DOUBLES_EQUAL(1.0, T.GetLE(1.1), Eps);
	DOUBLES_EQUAL(3.0, T.GetLE(4.0), Eps);
}

TEST(Tree, GetLE_NotEqual_double_CurveOrder)
{
	Tree<double> T;
	T.Insert( 3.0 );
	T.Insert( 2.0 );
	T.Insert( 1.0 );
	T.Insert( 5.0 );
	T.Insert( 4.0 );
	T.Insert( 6.0 );
	T.Insert( 5.5 );
	T.Insert( 6.5 );
	T.Insert( 4.5 );
	T.Insert( 3.5 );

	DOUBLES_EQUAL(1.0, T.GetLE(1.1), Eps);
	DOUBLES_EQUAL(3.5, T.GetLE(3.9), Eps);
}

TEST(Tree, GetLE_NotEqual_double_CurveOrder_Exception)
{
	try
	{
		Tree<double> T;

		T.Insert( 3.0 );
		T.Insert( 2.0 );
		T.Insert( 1.0 );
		T.Insert( 5.0 );
		T.Insert( 4.0 );
		T.Insert( 6.0 );
		T.Insert( 5.5 );
		T.Insert( 6.5 );
		T.Insert( 4.5 );
		T.Insert( 3.5 );

		DOUBLES_EQUAL(1.0, T.GetLE(0.1), Eps);

		FAIL("Должно быть исключение");
	}
	catch (exception& e)
	{
		CHECK_EQUAL("Элемент отсутствует", e.what());
	}
}

TEST(Tree, Intersection_int)
{
	Tree<int> T1;
	T1.Insert( 5 );
	T1.Insert( 6 );
	T1.Insert( 3 );
	T1.Insert( 4 );
	T1.Insert( 2 );
	T1.Insert( 1 );

	Tree<int> T2;
	T2.Insert( 3 );
	T2.Insert( 5 );
	T2.Insert( 7 );

	Tree<int> TResult = T1.Intersection(T2);

	CHECK( !TResult.Find(1) );
	CHECK( !TResult.Find(2) );
	CHECK( TResult.Find(3) );
	CHECK( !TResult.Find(4) );
	CHECK( TResult.Find(5) );
	CHECK( !TResult.Find(6) );
	CHECK( !TResult.Find(7) );
}

TEST(Tree, Intersection_ResultIsEmpty_int)
{
	Tree<int> T1;
	T1.Insert( 5 );
	T1.Insert( 6 );
	T1.Insert( 3 );
	T1.Insert( 4 );
	T1.Insert( 2 );
	T1.Insert( 1 );

	Tree<int> T2;
	T2.Insert( 7 );
	T2.Insert( 8 );
	T2.Insert( 9 );

	Tree<int> TResult = T1.Intersection(T2);

	CHECK( TResult.IsEmpty() );
}

TEST(Tree, Intersection_EmptyWithEmpty)
{
	Tree<int> T1;
	Tree<int> T2;
	Tree<int> TResult = T1.Intersection(T2);

	CHECK( TResult.IsEmpty() );
}

TEST(Tree, Intersection_Improved_int)
{
	Tree<int> T1;
	T1.Insert( 5 );
	T1.Insert( 6 );
	T1.Insert( 3 );
	T1.Insert( 4 );
	T1.Insert( 2 );
	T1.Insert( 1 );

	Tree<int> T2;
	T2.Insert( 3 );
	T2.Insert( 5 );
	T2.Insert( 7 );

	Tree<int> TResult = T1.Intersection_(T2);

	CHECK( !TResult.Find(1) );
	CHECK( !TResult.Find(2) );
	CHECK( TResult.Find(3) );
	CHECK( !TResult.Find(4) );
	CHECK( TResult.Find(5) );
	CHECK( !TResult.Find(6) );
	CHECK( !TResult.Find(7) );
}

TEST(Tree, Intersection_Improved_ResultIsEmpty_int)
{
	Tree<int> T1;
	T1.Insert( 5 );
	T1.Insert( 6 );
	T1.Insert( 3 );
	T1.Insert( 4 );
	T1.Insert( 2 );
	T1.Insert( 1 );

	Tree<int> T2;
	T2.Insert( 7 );
	T2.Insert( 8 );
	T2.Insert( 9 );

	Tree<int> TResult = T1.Intersection_(T2);

	CHECK( TResult.IsEmpty() );
}

TEST(Tree, Intersection_Improved_FilledWithEmpty)
{
	Tree<int> T1;
	T1.Insert( 1 );

	Tree<int> T2;
	Tree<int> TResult = T1.Intersection_(T2);

	CHECK( TResult.IsEmpty() );
}

TEST(Tree, Intersection_Improved_EmptyWithEmpty)
{
	Tree<int> T1;
	Tree<int> T2;
	Tree<int> TResult = T1.Intersection_(T2);

	CHECK( TResult.IsEmpty() );
}

TEST(Tree, ToString)
{
	Tree<int> T;
	T.Insert( 1 );
	T.Insert( 2 );
	T.Insert( 3 );

	CHECK_EQUAL("1 2 3", T.ToString());
}

TEST(Tree, ToString_Empty)
{
	Tree<int> T;

	CHECK_EQUAL("", T.ToString());
}

TEST(Tree, ToString_int)
{
	Tree<int> T;
	T.Insert( 5 );
	T.Insert( 6 );
	T.Insert( 3 );
	T.Insert( 4 );
	T.Insert( 2 );
	T.Insert( 1 );

	CHECK_EQUAL("1 2 3 4 5 6", T.ToString());
}

TEST(Tree, ToString_double)
{
	Tree<double> T;
	T.Insert( 5.5 );
	T.Insert( 6.6 );
	T.Insert( 3.3 );
	T.Insert( 4.4 );
	T.Insert( 2.2 );
	T.Insert( 1.1 );

	CHECK_EQUAL("1.1 2.2 3.3 4.4 5.5 6.6", T.ToString());
}

TEST(Tree, LeftTraversal_int)
{
	Tree<int> T;
	T.Insert( 5 );
	T.Insert( 6 );
	T.Insert( 3 );
	T.Insert( 4 );
	T.Insert( 2 );
	T.Insert( 1 );

	CHECK_EQUAL("5 \n3 6 \n2 4 \n1 \n", T.PrintLeftTraversalToString());
	//T.PrintLeftTraversal();
}

TEST(Tree, LeftTraversal_Empty)
{
	Tree<int> T;

	CHECK_EQUAL("", T.PrintLeftTraversalToString());
	//T.PrintLeftTraversal();
}