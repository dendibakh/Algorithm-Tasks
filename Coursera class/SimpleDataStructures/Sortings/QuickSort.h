#pragma once

#include <algorithm>

void QuickSort(int* arr, int left, int right)
{
   int i = left;
   int j = right;
   int pivot = arr[(right + left) / 2];

   while (i <= j)
   {
      while (arr[i] < pivot)
         i++;
      while (arr[j] > pivot)
         j--;
      if (i <= j)
      {
         std::swap(&arr[i], &arr[j]);
         i++;
         j--;
      }
   }

   if (left < j)
      QuickSort(arr, left, j);
   if (i < right)
      QuickSort(arr, i, right);
}

void QuickSort(int* arr, int size)
{
   QuickSort(arr, 0, size - 1);
}