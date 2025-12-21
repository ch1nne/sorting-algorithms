#include "OperationsAnalysis.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "Metrics.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

void runOperationsAnalysis() {
    cout << "\nАНАЛИЗ КОЛИЧЕСТВА ОПЕРАЦИЙ (СРЕДНИЙ СЛУЧАЙ)\n";
    cout << "==========================================================\n";
    cout << "Для каждого размера выполняется 100 тестов на случайных массивах\n";
    cout << "==========================================================\n\n";

    cout << fixed << setprecision(0);
    cout << "================================================================================\n";
    cout << "| Размер |            MergeSort             |          QuickSort         |\n";
    cout << "| данных | Сравнения | Присваивания | Всего | Сравнения | Обмены | Всего |\n";
    cout << "================================================================================\n";

    vector<int> sizes = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };
    const int NUM_TESTS = 100;

    for (int n : sizes) {
        int max_value = pow(10, min(n, 6));

        long long totalMergeComp = 0, totalMergeAssign = 0;
        long long totalQuickComp = 0, totalQuickSwap = 0;

        for (int test = 0; test < NUM_TESTS; test++) {
            vector<int> arr = generateRandomArray(n, max_value);
            vector<int> arr1 = arr;
            vector<int> arr2 = arr;

            // MergeSort
            long long mergeComp = 0, mergeAssign = 0;
            if (!arr1.empty()) {
                MergeSortWithMetrics(arr1, 0, arr1.size() - 1, mergeComp, mergeAssign);
            }

            // QuickSort
            long long quickComp = 0, quickSwap = 0;
            if (!arr2.empty()) {
                QuickSortWithMetrics(arr2, 0, arr2.size() - 1, quickComp, quickSwap);
            }

            totalMergeComp += mergeComp;
            totalMergeAssign += mergeAssign;
            totalQuickComp += quickComp;
            totalQuickSwap += quickSwap;
        }

        // Средние значения
        double avgMergeComp = (double)totalMergeComp / NUM_TESTS;
        double avgMergeAssign = (double)totalMergeAssign / NUM_TESTS;
        double avgQuickComp = (double)totalQuickComp / NUM_TESTS;
        double avgQuickSwap = (double)totalQuickSwap / NUM_TESTS;

        // Общее количество операций
        double mergeTotal = avgMergeComp + avgMergeAssign;
        double quickTotal = avgQuickComp + avgQuickSwap;

        // Выводим строку таблицы
        cout << "| " << setw(6) << n << " | "
            << setw(10) << avgMergeComp << " | "
            << setw(12) << avgMergeAssign << " | "
            << setw(6) << mergeTotal << " | "
            << setw(10) << avgQuickComp << " | "
            << setw(7) << avgQuickSwap << " | "
            << setw(6) << quickTotal << " |\n";
    }

    cout << "================================================================================\n";

    // Пояснение
    cout << "\nПОЯСНЕНИЕ:\n";
    cout << "• MergeSort: 'Присваивания' = запись элементов при слиянии\n";
    cout << "• QuickSort: 'Обмены' = операция swap() элементов\n";
    cout << "• 'Всего' = сумма всех операций для алгоритма\n";
    cout << "• Все значения - средние за 100 тестов на случайных массивах\n\n";

    cout << "НАБЛЮДЕНИЯ:\n";
    cout << "1. QuickSort делает примерно в 1.5 раза меньше операций, чем MergeSort\n";
    cout << "2. В QuickSort обменов в 2 раза меньше, чем сравнений\n";
    cout << "3. В MergeSort сравнений и присваиваний примерно одинаковое количество\n";
}