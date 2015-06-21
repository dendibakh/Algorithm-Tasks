#pragma once

class DynArrayQueue
{
   void resize()
   {
      //if (cur_size() == )
      size *= 2; 
      int* tmp = new int[size];
      for (int i = 0; i < size; i++)
         tmp[i] = arr[i];
      delete[] arr;
      arr = tmp;
   }

public:
   DynArrayQueue() : headOffset(0), tailOffset(0), size(10)
   {
      arr = new int[size];
   }

   ~DynArrayQueue()
   {
      delete[] arr;
   }

   bool isEmpty()
   {
      return headOffset == tailOffset;
   }

   int max_size()
   {
      return size;
   }

   int cur_size()
   {
      return tailOffset - headOffset;
   }

   void push(int val)
   {
      arr[tailOffset] = val;
      tailOffset++;
      if (tailOffset == size)
         resize();
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
   int size;
   int *arr;
};