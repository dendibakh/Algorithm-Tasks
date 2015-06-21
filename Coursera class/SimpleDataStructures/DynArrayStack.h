#pragma once

class DynArrayStack
{
   void resize()
   {
      size *= 2; 
      int* tmp = new int[size];
      for (int i = 0; i < size; i++)
         tmp[i] = arr[i];
      delete[] arr;
      arr = tmp;
   }

public:
   DynArrayStack(int N) : curOffset(0), size(N)
   {
      arr = new int[size];
   }

   ~DynArrayStack()
   {
      delete[] arr;
   }

   bool isEmpty()
   {
      return curOffset == 0;
   }

   int max_size()
   {
      return size;
   }

   int cur_size()
   {
      return curOffset;
   }

   void push(int val)
   {
      arr[curOffset] = val;
      curOffset++;
      if (curOffset == size)
         resize();
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
   int size;
   int *arr;
};