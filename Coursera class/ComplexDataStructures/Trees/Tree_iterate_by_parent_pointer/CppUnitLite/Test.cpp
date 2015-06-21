#include "Test.h"
#include "TestRegistry.h"
#include <sstream>
#include <math.h>

Test::Test(const std::string& testName, const std::string& testDesc):
   name_(testName),
   description_(testDesc)
{
   TestRegistry::addTest(this);
}

void Test::run(TestResult& result_)
{
   try
   {
      result_.testStarted(name_);
      testMethod(result_);
   }
   catch (std::exception& e)
   {
      std::stringstream s;
      s << "Exception " << e.what();
      FAIL(s.str().c_str());
   }
   catch (std::string& e)
   {
      std::stringstream s;
      s << "Exception " << e;
      FAIL(s.str().c_str());
   }
   catch (const char* e)
   {
      std::stringstream s;
      s << "Exception " << e;
      FAIL(s.str().c_str());
   }
   catch (int e)
   {
      std::stringstream s;
      s << "Exception int(" << e << ")";
      FAIL(s.str().c_str());
   }
   catch (...)
   {
      FAIL("Unknown exception");
   }
}

std::string Test::getName() const
{
   return name_;
}

std::string Test::makeTestName(const std::string& name)
{
   return name + "Test";
}

bool Test::assertEquals(TestResult& result,
                  const std::string& expected,
                  const std::string& actual,
                  const std::string& fileName,
                  long lineNumber)
{
   return assertEquals<std::string>(result, expected, actual, fileName, lineNumber);
}

bool Test::assertEquals(TestResult& result,
                  const char*        expected,
                  const char*        actual,
                  const std::string& fileName,
                  long lineNumber)
{
   return assertEquals<std::string>(result, std::string(expected), std::string(actual), fileName, lineNumber);
}

bool Test::assertEquals(TestResult& result,
                  const char*        expected,
                  const std::string& actual,
                  const std::string& fileName,
                  long lineNumber)
{
   return assertEquals<std::string>(result, std::string(expected), actual, fileName, lineNumber);
}

bool Test::assertEquals(TestResult& result,
                  const std::string& expected,
                  const char*        actual,
                  const std::string& fileName,
                  long lineNumber)
{
   return assertEquals<std::string>(result, expected, std::string(actual), fileName, lineNumber);
}

bool Test::assertEquals(TestResult& result,
                  long expected,
                  size_t actual,
                  const std::string& fileName,
                  long lineNumber)
{
   if (expected >= 0)
      return assertEquals<size_t>(result, (size_t)expected, actual, fileName, lineNumber);
   else
   {
      result.addFailure(Failure(name_, description_, fileName, lineNumber,
                                assertion_traits<long>::toString(expected),
                                assertion_traits<size_t>::toString(actual)));
      return false;
   }
}

bool Test::assertEquals(TestResult& result,
                  size_t expected,
                  long actual,
                  const std::string& fileName,
                  long lineNumber)
{
   if (actual >= 0)
      return assertEquals<size_t>(result, expected, (size_t)actual, fileName, lineNumber);
   else
   {
      result.addFailure(Failure(name_, description_, fileName, lineNumber,
                                assertion_traits<size_t>::toString(expected),
                                assertion_traits<long>::toString(actual)));
      return false;
   }
}


bool Test::assertDoubleEquals(TestResult& result,
                        double expected,
                        double actual,
                        double delta,
                        const std::string& fileName,
                        long lineNumber)
{
   if (fabs(expected - actual) <= delta)
      return true;
   else
   {
      result.addFailure(Failure(name_, description_, fileName, lineNumber,
                                assertion_traits<double>::toString(expected),
                                assertion_traits<double>::toString(actual)));
      return false;
   }
}
