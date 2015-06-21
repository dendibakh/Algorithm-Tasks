#ifndef FAILURE_H
#define FAILURE_H

#include <string>
#include <iostream>

class Failure
{
public:
   Failure(const std::string& theTestName,
           const std::string& theFileName,
           long               theLineNumber,
           const std::string& theCondition);

   Failure(const std::string& theTestName,
           const std::string& theTestDesc,
           const std::string& theFileName,
           long               theLineNumber,
           const std::string& theCondition);

   Failure(const std::string& theTestName,
           const std::string& theTestDesc,
           const std::string& theFileName,
           long               theLineNumber,
           const std::string& expected,
           const std::string& actual);

   std::string message;
   std::string testName;
   std::string testDesc;
   std::string fileName;
   long        lineNumber;
};

std::ostream& operator<<(std::ostream& stream, const Failure& failure);

#endif