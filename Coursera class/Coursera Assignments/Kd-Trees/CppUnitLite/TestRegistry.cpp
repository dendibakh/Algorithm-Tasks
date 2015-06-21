#include "Test.h"
#include "TestRegistry.h"

void TestRegistry::addTest(Test *test) 
{
   instance().add(test);
}

void TestRegistry::runAllTests(TestResult& result) 
{
   instance().run(result, "");
}

void TestRegistry::runAllTests(TestResult& result, const std::string& testName) 
{
   instance().run(result, Test::makeTestName(testName));
}

TestRegistry& TestRegistry::instance() 
{
   static TestRegistry registry;
   return registry;
}

void TestRegistry::add(Test *test) 
{
   tests.push_back(test);
}

void TestRegistry::run(TestResult& result, const std::string& testName) 
{
   result.testsStarted();
   for (std::vector<Test *>::iterator it = tests.begin(); it != tests.end(); ++it)
      if ((testName == "") || (testName == (*it)->getName()))
         (*it)->run(result);
   result.testsEnded();
}
