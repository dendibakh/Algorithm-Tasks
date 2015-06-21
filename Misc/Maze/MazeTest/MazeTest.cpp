#include "stdafx.h"
#include "CppUnitTest.h"
#include "Maze.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MazeTest
{               
        //static const std::string pathToTestFiles = "C:\\Maze\\MazeTest\\Examples\\";
	static const std::string pathToTestFiles = "F:\\Storage\\Maze\\MazeTest\\Examples\\";

        TEST_CLASS(MazeUnitTest)
        {
        public:
               
                                TEST_METHOD(TestCorrectness0)
                                {
                                        Maze maze(pathToTestFiles + "abracadabra.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("no such file"));
                                }

                                                                TEST_METHOD(TestCorrectness1)
                                                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness1.txt");
                                        Assert::IsTrue(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string(""));
                                                                }

                                TEST_METHOD(TestCorrectness2)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness2.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("source A is missing"));

                                        try
                                        {
                                                maze.printMazeToFile("");
                                                Assert::Fail(L"We shouldn't reach this code");
                                        }
                                        catch (std::exception &)
                                        {
                                        }

                                        try
                                        {
                                                maze.printMazeToFile("");
                                                Assert::Fail(L"We shouldn't reach this code");
                                        }
                                        catch (std::exception &)
                                        {
                                        }

                                        try
                                        {
                                                maze.printMazeToFile("");
                                                Assert::Fail(L"We shouldn't reach this code");
                                        }
                                        catch (std::exception &)
                                        {
                                        }
                                }

                                TEST_METHOD(TestCorrectness3)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness3.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("destination B is missing"));
                                }

                                TEST_METHOD(TestCorrectness4)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness4.txt");
                                        Assert::IsTrue(maze.correct());
                                }

                                TEST_METHOD(TestCorrectness5)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness5.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("source A is missing"));
                                }

                                TEST_METHOD(TestCorrectness6)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness6.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("maze is not quadratic"));
                                }

                                TEST_METHOD(TestCorrectness7)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness7.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("maze is not quadratic"));
                                }

                                TEST_METHOD(TestCorrectness8)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness8.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("unexpected symbol"));
                                }
                                        
                                TEST_METHOD(TestCorrectness9)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness9.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("source A is missing"));
                                }

                                TEST_METHOD(TestCorrectness10)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness10.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("maze is not quadratic"));
                                }

                                TEST_METHOD(TestCorrectness11)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness11.txt");
                                        Assert::IsFalse(maze.correct());
                                        Assert::IsTrue(maze.getError() == std::string("destination B is missing"));
                                }

                                TEST_METHOD(TestCorrectness12)
                                {
                                        Maze maze(pathToTestFiles + "TestCorrectness12.txt");
                                        Assert::IsTrue(maze.correct());
                                }

                                TEST_METHOD(TestPrint)
                                {
                                        Maze maze(pathToTestFiles + "TestPrint.txt");
                                        Assert::IsTrue(maze.correct());
                                        maze.printMazeToFile(pathToTestFiles + "TestPrintOut.txt");
                                        std::ifstream file;
                                        file.open(pathToTestFiles + "TestPrintOut.txt");
                                        Assert::IsTrue(file.is_open());
                                        file.close();
                                }
        };
}