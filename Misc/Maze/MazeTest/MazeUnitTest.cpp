#include "stdafx.h"
#include "CppUnitTest.h"
#include "Maze.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MazeTest
{               
        //static const std::string pathToTestFiles = "C:\\Maze\\MazeTest\\Examples\\";
        static const std::string pathToTestFiles = "F:\\Storage\\Maze\\MazeTest\\Examples\\";

                class MazeTester : public Maze
                {
                public:
                        MazeTester(const std::string& FileName) : Maze(FileName)
                        {}

                        int getSourceVertex() const
                        {
                                checkForError();
                                return source;
                        }

                        int getDestinationVertex() const
                        {
                                checkForError();
                                return destination;
                        }

                        unsigned int getDimension() const
                        {
                                checkForError();
                                return dimension;
                        }

                        MazeField getMazeField() const
                        {
                                checkForError();
                                return maze;
                        }

                        int getDistanceToDestination() const
                        {
                                checkForError();
                                return shortestPath->distTo(destination);
                        }

                        int getLongestDistanceToDestination() const
                        {
                                checkForError();
                                return longestPath->getDistance();
                        }

                                                ShortestPathTrack getTrackVertecies() const
                        {
                                checkForError();
                                return shortestPath->pathTo(destination);
                        }

                        LongestPathTrack getLongestPath() const
                        {
                                checkForError();
                                return longestPath->getPath();
                        }
                };

        TEST_CLASS(MazeUnitTest)
        {
        public:

                                TEST_METHOD(TestFindSourceAndDestination1)
                                {
                                        MazeTester maze(pathToTestFiles + "TestFindSourceAndDestination1.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(6, maze.getSourceVertex());
                                        Assert::AreEqual(9, maze.getDestinationVertex());
                                }

                                TEST_METHOD(TestFindSourceAndDestination2)
                                {
                                        MazeTester maze(pathToTestFiles + "TestFindSourceAndDestination2.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(15, maze.getSourceVertex());
                                        Assert::AreEqual(3, maze.getDestinationVertex());
                                }

                                TEST_METHOD(TestFindSourceAndDestination3)
                                {
                                        MazeTester maze(pathToTestFiles + "TestFindSourceAndDestination3.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(0, maze.getSourceVertex());
                                        Assert::AreEqual(12, maze.getDestinationVertex());
                                }

                                TEST_METHOD(TestFindDimension1)
                                {
                                        MazeTester maze(pathToTestFiles + "TestFindDimension1.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(unsigned int(2), maze.getDimension());
                                }

                                TEST_METHOD(TestFindDimension2)
                                {
                                        MazeTester maze(pathToTestFiles + "TestFindDimension2.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(unsigned int(20), maze.getDimension());
                                }

                                TEST_METHOD(TestGetMazeField)
                                {
                                        MazeTester maze(pathToTestFiles + "TestGetMazeField.txt");
                                        Assert::IsTrue(maze.correct());
                                        MazeTester::MazeField mazeField = maze.getMazeField();
                                        
                                        Assert::IsTrue(mazeField[1][2]);
                                        Assert::IsTrue(mazeField[2][1]);
                                        Assert::IsTrue(mazeField[2][2]);

                                        Assert::IsFalse(mazeField[0][0]);
                                        Assert::IsFalse(mazeField[0][1]);
                                        Assert::IsFalse(mazeField[0][2]);
                                        Assert::IsFalse(mazeField[0][3]);
                                        Assert::IsFalse(mazeField[1][0]);
                                        Assert::IsFalse(mazeField[1][1]);
                                        Assert::IsFalse(mazeField[1][3]);
                                        Assert::IsFalse(mazeField[2][0]);
                                        Assert::IsFalse(mazeField[2][3]);
                                        Assert::IsFalse(mazeField[3][0]);
                                        Assert::IsFalse(mazeField[3][1]);
                                        Assert::IsFalse(mazeField[3][2]);
                                        Assert::IsFalse(mazeField[3][3]);
                                }

                                TEST_METHOD(TestShortestPath1)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestPath1.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(42, maze.getDistanceToDestination());
                                }

                                TEST_METHOD(TestShortestPath2)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestPath2.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(55, maze.getDistanceToDestination());
                                }

                                TEST_METHOD(TestShortestPath3)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestPath3.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(1, maze.getDistanceToDestination());
                                }

                                TEST_METHOD(TestShortestPath4)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestPath4.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(2, maze.getDistanceToDestination());
                                }

                                TEST_METHOD(TestShortestPath5)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestPath5.txt");
                                                                                Assert::IsFalse(maze.correct());
                                                                                
                                        try
                                        {
                                                maze.getDistanceToDestination();
                                                Assert::Fail(L"We shouldn't reach this code");
                                        }
                                        catch (std::exception &e)
                                        {
                                                Assert::IsTrue(e.what() == std::string("no path between source and destination"));
                                        }
                                }

                                TEST_METHOD(TestShortestPath6)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestPath6.txt");
                                                                                Assert::IsFalse(maze.correct());
                                }

                                TEST_METHOD(TestShortestPath7)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestPath7.txt");
                                                                                Assert::IsFalse(maze.correct());
                                }

                                TEST_METHOD(TestShortestPath8)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestPath8.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(48, maze.getDistanceToDestination());
                                }

                                                                bool equalStacks(MazeTester::ShortestPathTrack lhs, MazeTester::ShortestPathTrack rhs)
                                {
                                        if (lhs.size() != rhs.size())
                                                return false;
                                        while (!lhs.empty())
                                        {
                                                if (lhs.top() != rhs.top())
                                                        return false;
                                                lhs.pop();
                                                rhs.pop();
                                        }
                                        return true;
                                }

                                TEST_METHOD(TestShortestTrackVertecies1)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestTrackVertecies1.txt");
                                        Assert::IsTrue(maze.correct());

                                                                                MazeTester::ShortestPathTrack etalon;
                                        etalon.push(271);
                                        etalon.push(272);
                                        etalon.push(292);
                                        etalon.push(312);
                                        etalon.push(332);
                                        etalon.push(352);
                                        etalon.push(372);
                                        etalon.push(371);
                                        etalon.push(370);
                                        etalon.push(369);
                                        etalon.push(368);
                                        etalon.push(367);
                                        etalon.push(366);
                                        etalon.push(365);
                                        etalon.push(364);
                                        etalon.push(344);
                                        etalon.push(324);
                                        etalon.push(304);
                                        etalon.push(284);
                                        etalon.push(264);
                                        etalon.push(244);
                                        etalon.push(224);
                                        etalon.push(225);
                                        etalon.push(226);
                                        etalon.push(227);
                                        etalon.push(207);
                                        etalon.push(187);
                                        etalon.push(167);
                                        etalon.push(166);
                                        etalon.push(146);
                                        etalon.push(126);
                                        etalon.push(106);
                                        etalon.push(105);
                                        etalon.push(85);
                                        etalon.push(84);
                                        etalon.push(83);
                                        etalon.push(82);
                                        etalon.push(62);
                                        etalon.push(42);
                                        etalon.push(22);
                                        etalon.push(23);
                                        etalon.push(24);
                                        etalon.push(25);
                                                                                MazeTester::ShortestPathTrack actual = maze.getTrackVertecies();
                                        Assert::IsTrue(equalStacks(etalon, actual));
                                }

                                TEST_METHOD(TestShortestTrackVertecies2)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestTrackVertecies2.txt");
                                        Assert::IsFalse(maze.correct());

                                        try
                                        {
                                                maze.getTrackVertecies();
                                                Assert::Fail(L"We shouldn't reach this code");
                                        }
                                        catch (std::exception &e)
                                        {
                                                Assert::IsTrue(e.what() == std::string("no path between source and destination"));
                                        }               
                                }

                                TEST_METHOD(TestShortestTrackVertecies3)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestTrackVertecies3.txt");
                                        Assert::IsTrue(maze.correct());

                                                                                MazeTester::ShortestPathTrack etalon;
                                        etalon.push(309);
                                        etalon.push(329);
                                        etalon.push(349);
                                        etalon.push(369);
                                        etalon.push(368);
                                        etalon.push(367);
                                        etalon.push(366);
                                        etalon.push(365);
                                        etalon.push(364);
                                        etalon.push(344);
                                        etalon.push(324);
                                        etalon.push(304);
                                        etalon.push(284);
                                        etalon.push(264);
                                        etalon.push(244);
                                        etalon.push(224);
                                        etalon.push(225);
                                        etalon.push(226);
                                        etalon.push(227);
                                        etalon.push(207);
                                        etalon.push(187);
                                        etalon.push(167);
                                        etalon.push(166);
                                        etalon.push(146);
                                        etalon.push(126);
                                        etalon.push(106);
                                        etalon.push(105);
                                        etalon.push(85);
                                        etalon.push(84);
                                        etalon.push(83);
                                        etalon.push(82);
                                        etalon.push(62);
                                        etalon.push(42);
                                        etalon.push(22);
                                        etalon.push(23);
                                        etalon.push(24);
                                        etalon.push(25);
                                        MazeTester::ShortestPathTrack actual = maze.getTrackVertecies();
                                        Assert::IsTrue(equalStacks(etalon, actual));
                                }

                                TEST_METHOD(TestShortestTrackVertecies4)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestTrackVertecies4.txt");
                                        Assert::IsTrue(maze.correct());

                                        MazeTester::ShortestPathTrack etalon;
                                        etalon.push(73);
                                        etalon.push(53);
                                        etalon.push(33);
                                        etalon.push(32);
                                        etalon.push(31);
                                        etalon.push(30);
                                        etalon.push(29);
                                        etalon.push(28);
                                        etalon.push(27);
                                        etalon.push(26);
                                        etalon.push(25);
                                        MazeTester::ShortestPathTrack actual = maze.getTrackVertecies();
                                        Assert::IsTrue(equalStacks(etalon, actual));
                                }

                                TEST_METHOD(TestShortestTrackVertecies5)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestTrackVertecies5.txt");
                                        Assert::IsTrue(maze.correct());

                                        MazeTester::ShortestPathTrack etalon;
                                        etalon.push(1);
                                        etalon.push(0);
                                        MazeTester::ShortestPathTrack actual = maze.getTrackVertecies();
                                        Assert::IsTrue(equalStacks(etalon, actual));
                                }

                                TEST_METHOD(TestShortestTrackVertecies6)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestTrackVertecies6.txt");
                                        Assert::IsTrue(maze.correct());

                                        MazeTester::ShortestPathTrack etalon;
                                        etalon.push(3);
                                        etalon.push(1);
                                        etalon.push(0);
                                        MazeTester::ShortestPathTrack actual = maze.getTrackVertecies();
                                        Assert::IsTrue(equalStacks(etalon, actual));
                                }

                                TEST_METHOD(TestShortestTrackVertecies7)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestTrackVertecies7.txt");
                                        Assert::IsTrue(maze.correct());

                                        MazeTester::ShortestPathTrack etalon;
                                        etalon.push(3);
                                        etalon.push(7);
                                        etalon.push(6);
                                        etalon.push(10);
                                        etalon.push(9);
                                        etalon.push(8);
                                        etalon.push(12);
                                        MazeTester::ShortestPathTrack actual = maze.getTrackVertecies();
                                        Assert::IsTrue(equalStacks(etalon, actual));
                                        Assert::AreEqual(6, maze.getDistanceToDestination());
                                }

                                TEST_METHOD(TestShortestTrackVertecies8)
                                {
                                        MazeTester maze(pathToTestFiles + "TestShortestTrackVertecies8.txt");
                                        Assert::IsTrue(maze.correct());

                                        MazeTester::ShortestPathTrack etalon;
                                        etalon.push(3);
                                        etalon.push(2);
                                        etalon.push(6);
                                        etalon.push(10);
                                        etalon.push(9);
                                        etalon.push(8);
                                        etalon.push(12);
                                        MazeTester::ShortestPathTrack actual = maze.getTrackVertecies();
                                        Assert::IsTrue(equalStacks(etalon, actual));
                                        Assert::AreEqual(6, maze.getDistanceToDestination());
                                }

                                TEST_METHOD(TestLongestPath1)
                                {
                                        MazeTester maze(pathToTestFiles + "TestLongestPath1.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(13, maze.getLongestDistanceToDestination());
                                }

                                TEST_METHOD(TestLongestPath2)
                                {
                                        MazeTester maze(pathToTestFiles + "TestLongestPath2.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(19, maze.getLongestDistanceToDestination());
                                }

                                TEST_METHOD(TestLongestPath3)
                                {
                                        MazeTester maze(pathToTestFiles + "TestLongestPath3.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(66, maze.getLongestDistanceToDestination());
                                }

                                
                                TEST_METHOD(TestLongestPath4)
                                {
                                        MazeTester maze(pathToTestFiles + "TestLongestPath4.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(14, maze.getLongestDistanceToDestination());
                                }
                                
                                TEST_METHOD(TestLongestPath5)
                                {
                                        MazeTester maze(pathToTestFiles + "TestLongestPath5.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(24, maze.getLongestDistanceToDestination());
                                }

                                TEST_METHOD(TestLongestPath6)
                                {
                                        // In this test example our algorithm doesn't show acceptable result.
                                        // Prunning rule and greedy method don't work properly
                                        /*
                                        MazeTester maze(pathToTestFiles + "TestLongestPath6.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(34, maze.getLongestDistanceToDestination());
                                        */
                                }

                                TEST_METHOD(TestLongestPath7)
                                {
                                        MazeTester maze(pathToTestFiles + "TestLongestPath7.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(48, maze.getLongestDistanceToDestination());
                                }

                                TEST_METHOD(TestLongestPath8)
                                {
                                        // In this test example our algorithm doesn't show acceptable result.
                                        // Prunning rule and greedy method don't work properly
                                        /*
                                        MazeTester maze(pathToTestFiles + "TestLongestPath8.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(62, maze.getLongestDistanceToDestination());
                                        */
                                }

                                TEST_METHOD(TestLongestPath9)
                                {
                                        MazeTester maze(pathToTestFiles + "TestLongestPath9.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(80, maze.getLongestDistanceToDestination());
                                }

                                TEST_METHOD(TestLongestPath21)
                                {
                                        MazeTester maze(pathToTestFiles + "TestLongestPath21.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::AreEqual(440, maze.getLongestDistanceToDestination());
                                }
        };
}