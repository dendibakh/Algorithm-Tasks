#ifndef TESTASSERT_H
#define TESTASSERT_H

#include <sstream>

template <class T>
struct assertion_traits
{
   static bool equal(const T& x, const T& y)
   {
      return x == y;
   }

   static std::string toString(const T& x)
   {
      std::stringstream s;
      s << x;
      return s.str();
   }
};

template <>
struct assertion_traits<char*>
{
   static bool equal(const char* x, const char* y)
   {
      return std::string(x) == std::string(y);
   }

   static std::string toString(const char* x)
   {
      std::stringstream s;
      s << x;
      return s.str();
   }
};

template <>
struct assertion_traits<bool>
{
   static bool equal(bool x, bool y)
   {
      return x == y;
   }

   static std::string toString(bool x)
   {
      if (x)
         return "true";
      else
         return "false";
   }
};

template <int size>
struct assertion_traits<char[size]>
{
   static bool equal(const char x[size], const char y[size])
   {
      return std::string(x) == std::string(y);
   }

   static std::string toString(const char x[size])
   {
      std::stringstream s;
      s << x;
      return s.str();
   }
};

#endif