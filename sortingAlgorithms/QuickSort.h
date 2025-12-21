#pragma once
#include <vector>

using namespace std;

// Обычная версия QuickSort
void QuickSort(vector<int>& arr, int left, int right);

// Версия с метриками
void QuickSortWithMetrics(vector<int>& arr, int left, int right,
    long long& comparisons, long long& swaps);