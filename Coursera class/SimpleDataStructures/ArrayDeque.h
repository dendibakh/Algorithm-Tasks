#pragma once

class ArrayDeque
{
public:
   ArrayDeque(int N) : headOffset(0), tailOffset(0)
   {
      arr = new int[N];
   }

   ~ArrayDeque()
   {
      delete[] arr;
   }

   bool isEmpty()
   {
      return headOffset == tailOffset;
   }

   void push(int val)
   {
      arr[tailOffset] = val;
      tailOffset++;
   }

   int pop()
   {
      if (isEmpty())
         return 0;
      int retval = arr[headOffset];
      headOffset++;
      return retval;
   }

private:
   int headOffset;
   int tailOffset;
   int *arr;
};