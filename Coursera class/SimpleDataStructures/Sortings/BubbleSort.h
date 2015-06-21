#pragma once

#include "utils.h"

void BubbleSort(int *arr, int size)
{
   for (int i = 0; i < size; i++)
      for (int j = i + 1; j < size; j++)
         if (arr[j] < arr[i])
            swap(&arr[i], &arr[j]);
}