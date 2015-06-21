#include "RunAllTest.h"
#include "TestHarness.h"

void RunAllTest()
{
	TestResult testResult;
	TestRegistry::runAllTests(testResult);
}

TEST(BoggleBoard, constructor)
{

}
