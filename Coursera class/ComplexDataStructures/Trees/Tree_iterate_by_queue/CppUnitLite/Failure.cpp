#include "Failure.h"
#include <sstream>

Failure::Failure(const std::string& theTestName,
                 const std::string& theFileName,
                 long               theLineNumber,
                 const std::string& theCondition):
   message(theCondition),
   testName(theTestName),
   fileName(theFileName),
   lineNumber(theLineNumber)
{
}


Failure::Failure(const std::string& theTestName,
                 const std::string& theTestDesc,
                 const std::string& theFileName,
                 long               theLineNumber,
                 const std::string& theCondition):
   message(theCondition),
   testName(theTestName),
   testDesc(theTestDesc),
   fileName(theFileName),
   lineNumber(theLineNumber)
{
}


Failure::Failure(const std::string& theTestName,
                 const std::string& theTestDesc,
                 const std::string& theFileName,
                 long               theLineNumber,
                 const std::string& expected,
                 const std::string& actual):
   testName(theTestName),
   fileName(theFileName),
   testDesc(theTestDesc),
   lineNumber(theLineNumber)
{  
   std::stringstream s;
   s << "expected " << expected << " but was: " << actual;
   message = s.str();
}


std::ostream& operator<<(std::ostream& stream, const Failure& failure)
{
   stream << failure.testName << " failed: ";
   stream << "\"" << failure.message << "\", ";
   if (failure.testDesc != "")
      stream << "\"" << failure.testDesc << "\", ";
   stream << "line " << failure.lineNumber << " ";
   stream << "in " << failure.fileName;
   stream << std::endl;
   return stream;
}
