#include "BubbleSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "HeapSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include <iostream>
#include <time.h>

using namespace std;

bool check(int* arr1, int* arr2, int size)
{
   for (int i = 0; i < size; i++)
   {
      if (arr1[i] != arr2[i])
         return false;
   }
   return true;
}

bool checkSort(int* arr1, int size)
{
   for (int i = 0; i < size - 1; i++)
   {
      if (arr1[i] > arr1[i + 1])
         return false;
   }
   return true;
}

void correctionTest()
{
   int arr[] = { 15, 78, 8, 7, 99, 45, 26, 67, 19, 31, 44, 65, 82, 73 };
   int correct[] = { 7, 8, 15, 19, 26, 31, 44, 45, 65, 67, 73, 78, 82, 99 };
   int size = sizeof(arr) / sizeof(int);
   QuickSort(arr, size);
   if ( check(arr, correct, size) && checkSort(arr, size))
      cout << "correct" << endl;
   else
      cout << "wrong" << endl;
}

void speedTest1(int N)
{
   int* arr1 = new int[N];
   int* arr2 = new int[N];
   int* arr3 = new int[N];
   for (int i = 0; i < N; i++)
   {
      arr1[i] = rand() % N;
      arr2[i] = rand() % N;
      arr3[i] = rand() % N;
   }

   QuickSort(arr1, N);    
   MergeSort(arr2, N);
   ShellSort(arr3, N);

   delete[] arr1;
   delete[] arr2;
   delete[] arr3;
}

void speedTest2(int N)
{
   int* arr1 = new int[N];
   int* arr2 = new int[N];
   for (int i = 0; i < N; i++)
   {
      arr1[i] = rand() % N;
      arr2[i] = rand() % N;
   }

   QuickSort(arr1, N);    
   MergeSort(arr2, N);

   delete[] arr1;
   delete[] arr2;
}

int main()
{
   //correctionTest();
   srand (time(NULL));
   //speedTest1(100000);
   // ¥§γ«μβ βλ:
   // QuickSort - 0.2%. MergeSort - 0.3%. ShellSort - 99.5%.
   speedTest2(1000000);
   // ¥§γ«μβ βλ:
   // QuickSort - 34.1%. MergeSort - 60.4%.
   //system("pause");
}