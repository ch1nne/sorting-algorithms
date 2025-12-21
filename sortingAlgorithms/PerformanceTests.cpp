#include "PerformanceTests.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "Utils.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace chrono;

void runPerformanceTests() {
    vector<int> sizes = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000 };
    const int NUM_TESTS_PER_SIZE = 10000;

    cout << "ЗАПУСК ТЕСТОВ ПРОИЗВОДИТЕЛЬНОСТИ\n";
    cout << "==========================================================\n";
    cout << "Количество тестов для каждого размера: " << NUM_TESTS_PER_SIZE << "\n";
    cout << "==========================================================\n\n";

    cout << fixed << setprecision(2);
    cout << "=====================================================================\n";
    cout << "| Размер |   MergeSort   |   QuickSort   |   std::sort   |\n";
    cout << "| данных |   (микросек)  |   (микросек)  |   (микросек)  |\n";
    cout << "=====================================================================\n";

    for (int n : sizes) {
        long long totalMergeTime = 0;
        long long totalQuickTime = 0;
        long long totalStdSortTime = 0;

        int max_value = pow(10, min(n, 6));

        for (int test = 0; test < NUM_TESTS_PER_SIZE; test++) {
            vector<int> original = generateRandomArray(n, max_value);

            // MergeSort
            vector<int> arr1 = original;
            auto start = high_resolution_clock::now();
            if (!arr1.empty()) {
                MergeSort(arr1, 0, arr1.size() - 1);
            }
            auto end = high_resolution_clock::now();
            totalMergeTime += duration_cast<microseconds>(end - start).count();

            // QuickSort
            vector<int> arr2 = original;
            start = high_resolution_clock::now();
            if (!arr2.empty()) {
                QuickSort(arr2, 0, arr2.size() - 1);
            }
            end = high_resolution_clock::now();
            totalQuickTime += duration_cast<microseconds>(end - start).count();

            // sort
            vector<int> arr3 = original;
            start = high_resolution_clock::now();
            sort(arr3.begin(), arr3.end());
            end = high_resolution_clock::now();
            totalStdSortTime += duration_cast<microseconds>(end - start).count();
        }

        double avgMerge = (double)totalMergeTime / NUM_TESTS_PER_SIZE;
        double avgQuick = (double)totalQuickTime / NUM_TESTS_PER_SIZE;
        double avgStd = (double)totalStdSortTime / NUM_TESTS_PER_SIZE;

        cout << "| " << setw(6) << n << " | "
            << setw(13) << avgMerge << " | "
            << setw(13) << avgQuick << " | "
            << setw(13) << avgStd << " |\n";
    }

    cout << "=====================================================================\n";
}