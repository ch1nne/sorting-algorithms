#pragma once
#include <vector>

// Обычная версия QuickSort
void QuickSort(std::vector<int>& arr, int left, int right);

// Версия с метриками
void QuickSortWithMetrics(std::vector<int>& arr, int left, int right,
    long long& comparisons, long long& swaps);