#ifndef TEST_H
#define TEST_H

#include "TestAssert.h"
#include "TestResult.h"
#include "Failure.h"
#include <string>

#define TEST(testName, testDesc)\
   class testName##testDesc##Test: public Test\
   {\
   public:\
      testName##testDesc##Test(): Test(makeTestName(#testName), #testDesc) {}\
   protected:\
      void testMethod (TestResult& result_);\
   } testName##testDesc##Instance;\
   void testName##testDesc##Test::testMethod(TestResult& result_)


#define CHECK(condition)\
{ if (!(condition)) { result_.addFailure(Failure(name_, description_, __FILE__,__LINE__, #condition)); return; } }


#define CHECK_EQUAL(expected, actual)\
{ if (!assertEquals(result_, (expected), (actual), __FILE__, __LINE__)) return; }


#define DOUBLES_EQUAL(expected, actual, delta)\
{ if (!assertDoubleEquals(result_, (expected), (actual), (delta), __FILE__, __LINE__)) return; }


#define FAIL(text) \
{ result_.addFailure(Failure(name_, description_, __FILE__, __LINE__, (text))); return; }


#define TEST_TRY \
   try {

#define ASSERT_EXCEPTION(name) \
   { result_.addFailure (Failure (name_, description_, __FILE__, __LINE__, "expected an exception "#name)); return; } \
   } catch (name&) {} \
     catch (...) { result_.addFailure (Failure (name_, description_, __FILE__, __LINE__, "expected an exception "#name)); return; }


// defines for compatibility
#define LONGS_EQUAL(expected, actual) CHECK_EQUAL(expected, actual)
#define STRINGS_EQUAL(expected, actual) CHECK_EQUAL(expected, actual)


class Test
{
public:
   Test(const std::string& testName, const std::string& testDesc);

   void run(TestResult& result_);
   std::string getName() const;

   static std::string makeTestName(const std::string& name);

protected:
   template <class T>
   bool assertEquals(TestResult& result,
                     const T& expected,
                     const T& actual,
                     const std::string& fileName,
                     long lineNumber)
   {
      if (assertion_traits<T>::equal(expected, actual))
         return true;
      else
      {
         result.addFailure(Failure(name_, description_, fileName, lineNumber,
                                   assertion_traits<T>::toString(expected),
                                   assertion_traits<T>::toString(actual)));
         return false;
      }
   }

   bool assertEquals(TestResult& result,
                     const std::string& expected,
                     const std::string& actual,
                     const std::string& fileName,
                     long lineNumber);

   bool assertEquals(TestResult& result,
                     const char*        expected,
                     const char*        actual,
                     const std::string& fileName,
                     long lineNumber);

   bool assertEquals(TestResult& result,
                     const char*        expected,
                     const std::string& actual,
                     const std::string& fileName,
                     long lineNumber);

   bool assertEquals(TestResult& result,
                     const std::string& expected,
                     const char*        actual,
                     const std::string& fileName,
                     long lineNumber);

   bool assertEquals(TestResult& result,
                     long expected,
                     size_t actual,
                     const std::string& fileName,
                     long lineNumber);

   bool assertEquals(TestResult& result,
                     size_t expected,
                     long actual,
                     const std::string& fileName,
                     long lineNumber);

   bool assertDoubleEquals(TestResult& result,
                           double expected,
                           double actual,
                           double delta,
                           const std::string& fileName,
                           long lineNumber);

   virtual void testMethod(TestResult& result_) = 0;

   const std::string name_;
   const std::string description_;

private:
   Test& operator=(const Test&);
};

#endif