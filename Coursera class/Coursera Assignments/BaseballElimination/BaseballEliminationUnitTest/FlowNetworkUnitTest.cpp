#include "stdafx.h"
#include "CppUnitTest.h"
#include "FlowNetwork.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EWGraphUnitTest
{
	TEST_CLASS(FlowNetworkUnitTest)
	{
	public:

		TEST_METHOD(CheckConstruct)
		{
			FlowNetwork flowNet(10);
		}

		TEST_METHOD(CheckConstructInWork)
		{
			FlowNetwork flowNet(2);
			Assert::AreEqual(flowNet.getVertexCount(), 2);
			FlowNetwork::EdgesList list = flowNet.getAdjacentVertex(1);
			Assert::IsTrue(list.empty());
		}

		TEST_METHOD(CheckAddEdge)
		{
			FlowNetwork flowNet(2);
			flowNet.addEdge(FlowEdge(0, 1, 9));
			{
				FlowNetwork::EdgesList list0 = flowNet.getAdjacentVertex(0);
				Assert::AreEqual(int(list0.size()), 1);
				int v = list0.front().from();
				int w = list0.front().to();
				Assert::AreEqual(v, 0);
				Assert::AreEqual(w, 1);
				Assert::AreEqual(list0.front().getCapacity(), 9);
				Assert::AreEqual(list0.front().getFlow(), 0);
			}
			
			{
				FlowNetwork::EdgesList list1 = flowNet.getAdjacentVertex(1);
				Assert::AreEqual(int(list1.size()), 1);
				int v = list1.front().from();
				int w = list1.front().to();
				Assert::AreEqual(v, 0);
				Assert::AreEqual(w, 1);
				Assert::AreEqual(list1.front().getCapacity(), 9);
				Assert::AreEqual(list1.front().getFlow(), 0);
			}
		}

		TEST_METHOD(CheckAddWrongEdge)
		{
			FlowNetwork flowNet(2);
			try
			{
				flowNet.addEdge(FlowEdge(0, 3, 9));
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckAddMoreEdge)
		{
			FlowNetwork flowNet(5);
			flowNet.addEdge(FlowEdge(0, 1, 5));
			flowNet.addEdge(FlowEdge(0, 2, 5));
			flowNet.addEdge(FlowEdge(1, 2, 5));
			flowNet.addEdge(FlowEdge(2, 3, 5));
			flowNet.addEdge(FlowEdge(3, 4, 5));
			flowNet.addEdge(FlowEdge(2, 4, 5));

			FlowNetwork::EdgesList expected1;
			expected1.push_front(FlowEdge(1, 2, 5));
			expected1.push_front(FlowEdge(0, 1, 5));
			FlowNetwork::EdgesList list1 = flowNet.getAdjacentVertex(1);
			Assert::IsTrue(std::equal(list1.begin(), list1.end(), expected1.begin()));

			FlowNetwork::EdgesList expected2;
			expected2.push_front(FlowEdge(2, 4, 5));
			expected2.push_front(FlowEdge(2, 3, 5));
			expected2.push_front(FlowEdge(1, 2, 5));
			expected2.push_front(FlowEdge(0, 2, 5));
			FlowNetwork::EdgesList list2 = flowNet.getAdjacentVertex(2);
			Assert::IsTrue(std::equal(list2.begin(), list2.end(), expected2.begin()));

			FlowNetwork::EdgesList expected4;
			FlowNetwork::EdgesList list4 = flowNet.getAdjacentVertex(4);
			expected4.push_front(FlowEdge(2, 4, 5));
			expected4.push_front(FlowEdge(3, 4, 5));
			Assert::IsTrue(std::equal(list4.begin(), list4.end(), expected4.begin()));
		}

		TEST_METHOD(CheckGetWrongAdjacentVertex)
		{
			FlowNetwork flowNet(5);
			flowNet.addEdge(FlowEdge(0, 1, 5));
			flowNet.addEdge(FlowEdge(0, 4, 5));

			try
			{
				FlowNetwork::EdgesList list10 = flowNet.getAdjacentVertex(10);
				Assert::Fail(L"There must be exception");
			}
			catch (std::exception&)
			{
			}
		}

		TEST_METHOD(CheckCounts)
		{
			FlowNetwork flowNet(5);
			flowNet.addEdge(FlowEdge(0, 1, 5));
			flowNet.addEdge(FlowEdge(0, 2, 5));
			flowNet.addEdge(FlowEdge(1, 2, 5));
			flowNet.addEdge(FlowEdge(2, 3, 5));
			flowNet.addEdge(FlowEdge(3, 4, 5));
			flowNet.addEdge(FlowEdge(2, 4, 5));

			Assert::AreEqual(flowNet.getEdgesCount(), 6);
			Assert::AreEqual(flowNet.getVertexCount(), 5);
		}

		TEST_METHOD(CheckCounts2)
		{
			FlowNetwork flowNet(5);
			flowNet.addEdge(FlowEdge(0, 1, 5));
			flowNet.addEdge(FlowEdge(0, 2, 5));
			flowNet.addEdge(FlowEdge(0, 2, 5));
			flowNet.addEdge(FlowEdge(1, 2, 5));
			flowNet.addEdge(FlowEdge(2, 3, 5));
			flowNet.addEdge(FlowEdge(3, 4, 5));
			flowNet.addEdge(FlowEdge(3, 4, 5));
			flowNet.addEdge(FlowEdge(2, 4, 5));

			Assert::AreEqual(flowNet.getEdgesCount(), 6);
			Assert::AreEqual(flowNet.getVertexCount(), 5);
		}
		
		TEST_METHOD(ChecktoString)
		{
			FlowNetwork flowNet(5);
			flowNet.addEdge(FlowEdge(0, 1, 5));
			flowNet.addEdge(FlowEdge(0, 2, 5));
			flowNet.addEdge(FlowEdge(1, 2, 5));
			flowNet.addEdge(FlowEdge(2, 3, 5));
			flowNet.addEdge(FlowEdge(3, 4, 5));
			flowNet.addEdge(FlowEdge(2, 4, 5));

			Assert::IsTrue(flowNet.toString() == std::string("0 - 1 0/5\n0 - 2 0/5\n1 - 2 0/5\n2 - 3 0/5\n2 - 4 0/5\n3 - 4 0/5\n"));
		}

		TEST_METHOD(CheckgetAllEdges)
		{
			FlowNetwork flowNet(5);
			flowNet.addEdge(FlowEdge(0, 1, 5));
			flowNet.addEdge(FlowEdge(0, 2, 5));
			flowNet.addEdge(FlowEdge(1, 2, 5));
			flowNet.addEdge(FlowEdge(2, 3, 5));
			flowNet.addEdge(FlowEdge(3, 4, 5));
			flowNet.addEdge(FlowEdge(2, 4, 5));

			FlowNetwork::EdgesList expected;
			expected.push_back(FlowEdge(0, 1, 5));
			expected.push_back(FlowEdge(0, 2, 5));
			expected.push_back(FlowEdge(1, 2, 5));
			expected.push_back(FlowEdge(2, 3, 5));
			expected.push_back(FlowEdge(2, 4, 5));
			expected.push_back(FlowEdge(3, 4, 5));

			FlowNetwork::EdgesList actual = flowNet.getAllEdges();
			Assert::IsTrue(std::equal(actual.begin(), actual.end(), expected.begin()));
		}

		TEST_METHOD(CheckAddFlow)
		{
			FlowNetwork flowNet(2);
			flowNet.addEdge(FlowEdge(0, 1, 9));
			{
				FlowNetwork::EdgesList list0 = flowNet.getAdjacentVertex(0);
				Assert::AreEqual(list0.front().getCapacity(), 9);
				Assert::AreEqual(list0.front().getFlow(), 0);
			}

			flowNet.addFlow(0, 1, 4);

			{
				FlowNetwork::EdgesList list0 = flowNet.getAdjacentVertex(0);
				Assert::AreEqual(list0.front().getCapacity(), 9);
				Assert::AreEqual(list0.front().getFlow(), 4);
				Assert::AreEqual(list0.front().getResidualCapacityTo(0), 4);
				Assert::AreEqual(list0.front().getResidualCapacityTo(1), 5);
			}

			flowNet.addFlow(1, 0, 1);

			{
				FlowNetwork::EdgesList list0 = flowNet.getAdjacentVertex(0);
				Assert::AreEqual(list0.front().getCapacity(), 9);
				Assert::AreEqual(list0.front().getFlow(), 3);
				Assert::AreEqual(list0.front().getResidualCapacityTo(0), 3);
				Assert::AreEqual(list0.front().getResidualCapacityTo(1), 6);
			}
		}
	};
}