#pragma once

#include "utils.h"

static void merge(int *arr, size_t begin, size_t middle, size_t end)
{
   if (begin >= end || middle < begin || middle > end) 
      return;

   if ( end == begin + 1 ) 
   {
      if (arr[begin] > arr[end])
         swap(&arr[begin], &arr[end]);
      return;
   }

   size_t arr_size = end + 1 - begin;
   int *tmp = new int[arr_size];
   for (size_t i = 0, k = begin ; i < arr_size; i++, k++)
      tmp[i] = arr[k];

   for(size_t i = begin, j = 0, k = middle - begin + 1; i <= end; i++)
   {
       if(j > middle - begin)   
          arr[i] = tmp[k++];
       else if(k > end - begin) 
          arr[i] = tmp[j++];
       else                     
          arr[i] = (tmp[j] < tmp[k]) ? tmp[j++] : tmp[k++];
   }
   delete [] tmp;
}

static void MergeSort(int *arr, size_t begin, size_t end)
{
   if( begin >= end) 
      return;

   size_t middle = (begin + end) / 2;

   MergeSort(arr, begin, middle);
   MergeSort(arr, middle + 1, end);

   merge(arr, begin, middle, end);
}

void MergeSort(int *arr, int size)
{
   MergeSort(arr, 0, size - 1);
}