#pragma once

class ArrayStack
{
public:
   ArrayStack(int N) : curOffset(0)
   {
      arr = new int[N];
   }

   ~ArrayStack()
   {
      delete[] arr;
   }

   bool isEmpty()
   {
      return curOffset == 0;
   }

   void push(int val)
   {
      arr[curOffset] = val;
      curOffset++;
   }

   int pop()
   {
      if (isEmpty())
         return 0;
      curOffset--;
      return arr[curOffset];
   }

private:
   int curOffset;
   int *arr;
};