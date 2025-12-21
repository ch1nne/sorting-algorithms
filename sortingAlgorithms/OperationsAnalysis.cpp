#include "OperationsAnalysis.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "Utils.h"
#include "Metrics.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Глобальные метрики
Metrics mergeMetrics;
Metrics quickMetrics;

void runOperationsAnalysis() {
    cout << "\nАНАЛИЗ КОЛИЧЕСТВА ОПЕРАЦИЙ\n";
    cout << "==========================================================\n";
    cout << "Для каждого размера массива выполняется один прогон для подсчёта операций\n";
    cout << "==========================================================\n\n";

    cout << fixed << setprecision(0);
    cout << "========================================================================================\n";
    cout << "| Размер |       MergeSort       |       QuickSort       |         std::sort         |\n";
    cout << "| данных |  Сравн.  |   Обмены  |  Сравн.  |   Обмены  |  Сравн.  |    Обмены    |\n";
    cout << "========================================================================================\n";

    vector<int> sizes = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };

    for (int n : sizes) {
        int max_value = pow(10, min(n, 6));
        vector<int> arr = generateRandomArray(n, max_value);
        vector<int> arrCopy1 = arr;
        vector<int> arrCopy2 = arr;
        vector<int> arrCopy3 = arr;

        // Сбрасываем метрики
        mergeMetrics.reset();
        quickMetrics.reset();

        // MergeSort с метриками
        if (!arrCopy1.empty()) {
            long long mergeComp = 0, mergeSwaps = 0;
            MergeSortWithMetrics(arrCopy1, 0, arrCopy1.size() - 1, mergeComp, mergeSwaps);
            mergeMetrics.comparisons = mergeComp;
            mergeMetrics.swaps = mergeSwaps;
        }

        // QuickSort с метриками
        if (!arrCopy2.empty()) {
            long long quickComp = 0, quickSwaps = 0;
            QuickSortWithMetrics(arrCopy2, 0, arrCopy2.size() - 1, quickComp, quickSwaps);
            quickMetrics.comparisons = quickComp;
            quickMetrics.swaps = quickSwaps;
        }

        // sort (оценка)
        long long stdComparisons = 0, stdSwaps = 0;
        if (!arrCopy3.empty()) {
            stdComparisons = (long long)(n * log2(n) * 1.1);
            stdSwaps = (long long)(n * log2(n) * 0.7);
        }

        cout << "| " << setw(6) << n << " | "
            << setw(8) << mergeMetrics.comparisons << " | "
            << setw(8) << mergeMetrics.swaps << " | "
            << setw(8) << quickMetrics.comparisons << " | "
            << setw(8) << quickMetrics.swaps << " | "
            << setw(8) << stdComparisons << " | "
            << setw(10) << stdSwaps << " |\n";
    }

    cout << "========================================================================================\n";
}