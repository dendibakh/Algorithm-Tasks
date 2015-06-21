#pragma once
#include "TestHarness.h"

void RunAllTest()
{
   TestResult result;
   TestRegistry::runAllTests(result);
}