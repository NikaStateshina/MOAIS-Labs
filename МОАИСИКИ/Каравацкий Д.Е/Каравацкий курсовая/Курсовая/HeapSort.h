#pragma once

#include<iostream> 
using namespace std;

void heapify(int* arr, int n, int i, unsigned& comp, unsigned& assignmentCount)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    comp++;
    if (l < n && arr[l] > arr[largest])
        largest = l;

    comp++;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        assignmentCount += 3;
        heapify(arr, n, largest, comp, assignmentCount);
    }
}


void heapSort(int* arr, int n, unsigned& comp, unsigned& assignmentCount)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comp, assignmentCount);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        assignmentCount += 3;
        heapify(arr, i, 0, comp, assignmentCount);
    }
}