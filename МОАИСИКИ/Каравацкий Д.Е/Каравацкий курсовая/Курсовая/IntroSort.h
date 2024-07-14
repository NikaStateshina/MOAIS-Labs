#pragma once

#include<iostream> 
#include "QuickSort.h"
#include "HeapSort.h"

using namespace std;

using namespace std;


void InsertionSort(int arr[], int begin, int end, unsigned& comp, unsigned& assignmentCount)
{

    int left = begin;
    int right = end;

    for (int i = left + 1; i <= right; i++)
    {
        int key = arr[i];
        int j = i - 1;

        comp++;
        while (j >= left && arr[j] > key)
        {
            comp++;
            arr[j + 1] = arr[j];
            assignmentCount++;
            j = j - 1;
        }
        arr[j + 1] = key;
        assignmentCount++;
    }

    return;
}


/*int medianOfThree(int arr[], int left, int right, unsigned long long& comp, unsigned long long& assignmentCount) {
    int mid = left + (right - left) / 2;

    comp++;
    if (arr[left] > arr[mid]) {
        swap(arr[left], arr[mid]);
        assignmentCount+= 3;
    }
    comp++;
    if (arr[left] > arr[right]) {
        swap(arr[left], arr[right]);
        assignmentCount+= 3;
    }
    comp++;
    if (arr[mid] > arr[right]) {
        swap(arr[mid], arr[right]);
        assignmentCount+= 3;
    }

    swap(arr[mid], arr[right - 1]);
    assignmentCount+= 3;

    return arr[right - 1];
}*/


/*int partition(int arr[], int left, int right, unsigned long long& comp, unsigned long long& assignmentCount) {

    int pivot = medianOfThree(arr, left, right, comp, assignmentCount);

    int i = left - 1;
    int j = right - 1;

    while (true) {
        comp++;
        while (arr[++i] < pivot) {
            comp++;
        };
        comp++;
        while (arr[--j] > pivot) {
            comp++;
        };

        if (i < j) {
            swap(arr[i], arr[j]);
            assignmentCount+= 3;
        }
        else
            break;
    }

    swap(arr[i], arr[right - 1]);
    assignmentCount+= 3;
    return i;
}*/

 
void IntrosortUtil(int arr[], int begin, int end, int depthLimit, unsigned& comp, unsigned& assignmentCount) {

    int size = end - begin;

    if (size < 16)
    {
        InsertionSort(arr, begin, end, comp, assignmentCount);
        return;
    }
 
    if (depthLimit == 0)
    {
        /*make_heap(begin + arr, end + arr + 1);
        sort_heap(begin + arr, end + arr + 1);
        */
        heapSort(arr + begin, end - begin, comp, assignmentCount);
        return;
    }
 
    int partitionPoint = partition(arr, begin, end, comp, assignmentCount);
    IntrosortUtil(arr, begin, partitionPoint - 1, depthLimit - 1, comp, assignmentCount);
    IntrosortUtil(arr, partitionPoint + 1, end, depthLimit - 1, comp, assignmentCount);

    return;
}

void introSort(int arr[], int begin, int end, unsigned& comp, unsigned& assignmentCount)
{
    int depthLimit = 2 * log(end - begin);

    IntrosortUtil(arr, begin, end, depthLimit, comp, assignmentCount);

    return;
}