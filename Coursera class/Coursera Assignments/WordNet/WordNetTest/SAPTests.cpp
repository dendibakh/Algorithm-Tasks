#include "stdafx.h"
#include "util.h"
#include "SAP.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace std;

namespace SAPUnitTest
{
	[TestClass]
	public ref class SAPClassTests
	{
	public:
		[TestMethod]
		void CheckConstruct()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph1);
			SAP sap(graph);
		}

		[TestMethod]
		void CheckLength()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph1);
			SAP sap(graph);

			Assert::AreEqual(sap.findClosestAncestor(3, 11).lenght, 4);
			Assert::AreEqual(sap.findClosestAncestor(9, 12).lenght, 3);
			Assert::AreEqual(sap.findClosestAncestor(7, 2).lenght, 4);
			Assert::AreEqual(sap.findClosestAncestor(7, 12).lenght, 5);
			Assert::AreEqual(sap.findClosestAncestor(11, 12).lenght, 2);
			Assert::AreEqual(sap.findClosestAncestor(4, 5).lenght, 2);
			Assert::AreEqual(sap.findClosestAncestor(12, 2).lenght, 5);
			
			Assert::AreEqual(sap.findClosestAncestor(0, 2).lenght, 1);
			Assert::AreEqual(sap.findClosestAncestor(2, 2).lenght, 0);

			Assert::AreEqual(sap.findClosestAncestor(12, 6).lenght, -1);
			Assert::AreEqual(sap.findClosestAncestor(1, 6).lenght, -1);
		}

		[TestMethod]
		void CheckLength2()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph2);
			SAP sap(graph);

			Assert::AreEqual(sap.findClosestAncestor(1, 5).lenght, 2);
			Assert::AreEqual(sap.findClosestAncestor(0, 0).lenght, 0);
			Assert::AreEqual(sap.findClosestAncestor(1, 0).lenght, 1);
			Assert::AreEqual(sap.findClosestAncestor(2, 4).lenght, 2);
			Assert::AreEqual(sap.findClosestAncestor(1, 4).lenght, 3);
		}

		[TestMethod]
		void CheckAncestor()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph1);
			SAP sap(graph);

			Assert::AreEqual(sap.findClosestAncestor(3, 11).ancestorID, 1);
			Assert::AreEqual(sap.findClosestAncestor(9, 12).ancestorID, 5);
			Assert::AreEqual(sap.findClosestAncestor(7, 2).ancestorID, 0);
			Assert::AreEqual(sap.findClosestAncestor(7, 12).ancestorID, 1);
			Assert::AreEqual(sap.findClosestAncestor(11, 12).ancestorID, 10);
			Assert::AreEqual(sap.findClosestAncestor(4, 5).ancestorID, 1);
			Assert::AreEqual(sap.findClosestAncestor(12, 2).ancestorID, 0);

			Assert::AreEqual(sap.findClosestAncestor(0, 2).ancestorID, 0);
			Assert::AreEqual(sap.findClosestAncestor(2, 2).ancestorID, 2);

			Assert::AreEqual(sap.findClosestAncestor(12, 6).ancestorID, -1);
			Assert::AreEqual(sap.findClosestAncestor(1, 6).ancestorID, -1);
		}

		[TestMethod]
		void CheckAncestor2()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph2);
			SAP sap(graph);

			Assert::AreEqual(sap.findClosestAncestor(1, 5).ancestorID, 0);
			Assert::AreEqual(sap.findClosestAncestor(0, 0).ancestorID, 0);
			Assert::AreEqual(sap.findClosestAncestor(1, 0).ancestorID, 0);
			Assert::AreEqual(sap.findClosestAncestor(2, 4).ancestorID, 4);
			Assert::AreEqual(sap.findClosestAncestor(1, 4).ancestorID, 4);
		}

		[TestMethod]
		void CheckList1()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph2);
			SAP sap(graph);

			int arr1[] = { 1 };
			int arr2[] = { 5 };
			list<int> First(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
			list<int> Second(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
			
			Assert::AreEqual(sap.findClosestAncestorFromTwoLists(First, Second).lenght, 2);
			Assert::AreEqual(sap.findClosestAncestorFromTwoLists(First, Second).ancestorID, 0);
		}

		[TestMethod]
		void CheckList2()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph2);
			SAP sap(graph);

			int arr1[] = { 1, 3, 4 };
			int arr2[] = { 0 };
			list<int> First(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
			list<int> Second(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
			
			Assert::AreEqual(sap.findClosestAncestorFromTwoLists(First, Second).lenght, 1);
			Assert::AreEqual(sap.findClosestAncestorFromTwoLists(First, Second).ancestorID, 0);
		}

		[TestMethod]
		void CheckList3()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph1);
			SAP sap(graph);

			int arr1[] = { 7, 9, 11 };
			int arr2[] = { 12 };
			list<int> First(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
			list<int> Second(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
			
			Assert::AreEqual(sap.findClosestAncestorFromTwoLists(First, Second).lenght, 2);
			Assert::AreEqual(sap.findClosestAncestorFromTwoLists(First, Second).ancestorID, 10);
		}

		[TestMethod]
		void CheckList4()
		{
			DiGraph graph = getDiGraphFromFile(DIGraph1);
			SAP sap(graph);

			int arr1[] = { 4, 5, 3, 10, 2 };
			int arr2[] = { 0 };
			list<int> First(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
			list<int> Second(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
			
			Assert::AreEqual(sap.findClosestAncestorFromTwoLists(First, Second).lenght, 1);
			Assert::AreEqual(sap.findClosestAncestorFromTwoLists(First, Second).ancestorID, 0);
		}
	};
}