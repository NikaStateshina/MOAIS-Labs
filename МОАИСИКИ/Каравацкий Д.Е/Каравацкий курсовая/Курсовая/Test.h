#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "IntroSort.h"
#include "HeapSort.h"
#include "QuickSort.h"

using namespace std;

int getSequenceLenght(string file) {
	ifstream f(file);
	int n;
	f >> n;
	return n;
	f.close();
}

void getSequence(int* arr, string file) {
	ifstream f(file);
	int n;
	f >> n;
	
	for (int i = 0; i < n; i++) {
		f >> arr[i];
	}
	f.close();
}

void testSort(float& time1, float& time2, unsigned& comp1, unsigned& comp2, unsigned& assignment1, unsigned& assignment2, string file) {

	int* arr;
	int n = getSequenceLenght(file);
	arr = new int[n];
	getSequence(arr, file);

	clock_t t;

	t = clock();
	quickSort(arr, 0, n - 1, comp1, assignment1);
	t = clock() - t;

	time1 = t;

	//////////////////////////////////////////

	getSequence(arr, file);

	//////////////////////////////////////////

	t = clock();
	introSort(arr, 0, n, comp2, assignment2);
	t = clock() - t;

	time2 = t;
}