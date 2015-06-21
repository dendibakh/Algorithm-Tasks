#include "RunAllTests.h"
#include "TestHarness.h"

void RunAllTests()
{
	TestResult testResult;
	TestRegistry::runAllTests(testResult);
}