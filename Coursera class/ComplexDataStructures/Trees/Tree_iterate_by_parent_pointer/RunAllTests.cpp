#include "RunAllTests.h"
#include "TestHarness.h"

void RunAllTests()
{
	TestResult result;
	TestRegistry::runAllTests(result);
}