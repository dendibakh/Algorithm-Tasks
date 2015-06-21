#pragma once

#include "utils.h"

void ShellSort(int *arr, int size)
{
   int h = 1;

   while (h < size / 3)
      h = h * 3 + 1;

   while (h >= 1)
   {
      for (int i = h; i < size; i++)
         for (int j = i; j >= h; j -= h)
            if (arr[j] < arr[j-h])
               swap(&arr[j], &arr[j-h]);
      h = h / 3;
   }
}