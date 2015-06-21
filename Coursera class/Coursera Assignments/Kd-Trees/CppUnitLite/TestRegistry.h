#ifndef TESTREGISTRY_H
#define TESTREGISTRY_H

#include <vector>
#include <string>

class Test;
class TestResult;

class TestRegistry
{
public:
	static void addTest(Test *test);
	static void runAllTests(TestResult& result);
   static void runAllTests(TestResult& result, const std::string& testName);

private:
	static TestRegistry&	instance();

	void add(Test *test);
	void run(TestResult& result, const std::string& testName);

   std::vector<Test *> tests;
};

#endif