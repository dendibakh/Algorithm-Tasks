#include "Failure.h"
#include "TestResult.h"
#include <iostream>

TestResult::TestResult():
   testCount(0),
   failureCount(0)
{
}

void TestResult::testsStarted()
{
}

void TestResult::testStarted(const std::string&)
{
   testCount++;
}

void TestResult::addFailure(const Failure& failure)
{
   std::cout << failure;
   failureCount++;
}

void TestResult::testsEnded()
{
   std::cout << testCount << " tests run. ";
   if (failureCount > 0)
      std::cout << "There were " << failureCount << " failures" << std::endl;
   else
      std::cout << "There were no test failures" << std::endl;
}
