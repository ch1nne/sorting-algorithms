#pragma once
#include <vector>

using namespace std;

// Обычная версия MergeSort
void MergeSort(vector<int>& arr, int left, int right);

// Версия с метриками
void MergeSortWithMetrics(vector<int>& arr, int left, int right,
    long long& comparisons, long long& swaps);