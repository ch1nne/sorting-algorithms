#pragma once
#include <vector>

using namespace std;

// Обычная версия
void MergeSort(vector<int>& arr, int left, int right);

// Версия с метриками (передаём счётчики по ссылке)
void MergeSortWithMetrics(vector<int>& arr, int left, int right,
    long long& comparisons, long long& swaps);