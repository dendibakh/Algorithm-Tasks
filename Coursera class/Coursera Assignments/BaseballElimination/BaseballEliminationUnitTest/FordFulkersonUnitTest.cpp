#include "stdafx.h"
#include "CppUnitTest.h"
#include "FordFulkerson.h"
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MaxFlowUnitTest
{
	TEST_CLASS(FordFulkersonUnitTest)
	{
	public:
		
		TEST_METHOD(TestFordFulkerson)
		{
			FlowNetwork flowNet(8);
			flowNet.addEdge(FlowEdge(0, 1, 10));
			flowNet.addEdge(FlowEdge(0, 4, 5));
			flowNet.addEdge(FlowEdge(0, 6, 15));
			flowNet.addEdge(FlowEdge(1, 2, 9));
			flowNet.addEdge(FlowEdge(1, 4, 4));
			flowNet.addEdge(FlowEdge(1, 5, 15));
			flowNet.addEdge(FlowEdge(2, 5, 15));
			flowNet.addEdge(FlowEdge(2, 3, 10));
			flowNet.addEdge(FlowEdge(4, 5, 8));	
			flowNet.addEdge(FlowEdge(4, 6, 4));
			flowNet.addEdge(FlowEdge(5, 7, 15));
			flowNet.addEdge(FlowEdge(5, 3, 10));
			flowNet.addEdge(FlowEdge(6, 7, 16));
			flowNet.addEdge(FlowEdge(7, 3, 10));
			flowNet.addEdge(FlowEdge(7, 4, 6));
			
			FordFulkerson ff(flowNet, 0, 3);
			Assert::AreEqual(28, ff.getMaxFlow());

			FordFulkerson::MinCutVertecies expected;
			expected.push_back(0);
			expected.push_back(6);
			expected.push_back(7);
			expected.push_back(4);
			FordFulkerson::MinCutVertecies actual = ff.getMinCutVertecies();
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}

		TEST_METHOD(TestFordFulkerson2)
		{
			FlowNetwork flowNet(7);
			flowNet.addEdge(FlowEdge(1, 2, 10));
			flowNet.addEdge(FlowEdge(1, 5, 5));
			flowNet.addEdge(FlowEdge(2, 3, 9));
			flowNet.addEdge(FlowEdge(2, 6, 4));
			flowNet.addEdge(FlowEdge(3, 4, 10));
			flowNet.addEdge(FlowEdge(3, 6, 15));
			flowNet.addEdge(FlowEdge(5, 2, 4));
			flowNet.addEdge(FlowEdge(5, 6, 8));
			flowNet.addEdge(FlowEdge(6, 4, 10));
			
			FordFulkerson ff(flowNet, 1, 4);
			Assert::AreEqual(15, ff.getMaxFlow());

			FordFulkerson::MinCutVertecies expected;
			expected.push_back(1);
			FordFulkerson::MinCutVertecies actual = ff.getMinCutVertecies();
			Assert::IsTrue(std::equal(expected.begin(), expected.end(), actual.begin()));
		}
	};
}