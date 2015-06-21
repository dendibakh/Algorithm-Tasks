#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <string>

class Failure;

class TestResult
{
public:
   TestResult();
   virtual void testsStarted();
   virtual void testStarted(const std::string& testName);
   virtual void addFailure(const Failure& failure);
   virtual void testsEnded();

private:
   int testCount;
   int failureCount;
};

#endif