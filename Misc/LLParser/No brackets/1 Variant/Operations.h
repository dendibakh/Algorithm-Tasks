#pragma once

enum Operations
{
   OPER_PLUS = 0,
   OPER_MINUS,
   OPER_MULTI,
   OPER_DIV
};

enum LEXEM
{
   VALUE = 0,
   SIGN,
   BRACKET
};

class Expression
{
   public:
      virtual int getType() = 0;
      virtual int getValue() = 0;
};

class Value : public Expression
{
   public:
      Value(int val) : val(val)
      {

      }

      virtual int getType()
      {
         return VALUE;
      }

      virtual int getValue()
      {
         return val;
      }
   private:
      int val;
};

class Operation : public Expression
{
   public:
      Operation(int oper) : oper(oper)
      {

      }

      virtual int getType()
      {
         return SIGN;
      }

      virtual int getValue()
      {
         return oper;
      }
   private:
      int oper;
};