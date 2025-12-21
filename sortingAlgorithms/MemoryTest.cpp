#include "MemoryTest.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace chrono;

// Глобальные счетчики для оценки использования памяти
size_t mergeSortMemoryUsage = 0;
size_t quickSortMemoryUsage = 0;

// Специальные версии для подсчета памяти
void MergeSortWithMemoryTracking(vector<int>& arr, int left, int right, int depth = 0) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // Рекурсивные вызовы
    MergeSortWithMemoryTracking(arr, left, mid, depth + 1);
    MergeSortWithMemoryTracking(arr, mid + 1, right, depth + 1);

    // Временный массив для слияния - основное потребление памяти
    vector<int> temp(right - left + 1);
    mergeSortMemoryUsage = max(mergeSortMemoryUsage,
        temp.size() * sizeof(int) +
        depth * sizeof(void*) * 2); // стек рекурсии

    // Слияние (упрощенное)
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int idx = 0; idx < k; idx++) {
        arr[left + idx] = temp[idx];
    }
}

void QuickSortWithMemoryTracking(vector<int>& arr, int left, int right, int depth = 0) {
    if (left >= right) return;

    // Отслеживаем максимальную глубину рекурсии
    quickSortMemoryUsage = max(quickSortMemoryUsage,
        depth * sizeof(void*) * 2); // только стек

    // Разделение (упрощенное)
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    int pivotPos = i + 1;

    QuickSortWithMemoryTracking(arr, left, pivotPos - 1, depth + 1);
    QuickSortWithMemoryTracking(arr, pivotPos + 1, right, depth + 1);
}

void runMemoryUsageTest() {
    cout << "\n=== ТЕСТ ИСПОЛЬЗОВАНИЯ ПАМЯТИ ===\n\n";

    vector<int> sizes = { 100, 1000, 10000, 50000 };

    cout << "Сравнение дополнительной памяти (помимо исходного массива):\n\n";
    cout << "Размер | MergeSort    | QuickSort    | \n";
    cout << "-------+--------------+--------------+\n";

    for (int N : sizes) {
        // Генерируем тестовые данные
        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            arr[i] = rand() % 10000;
        }

        // Сбрасываем счетчики
        mergeSortMemoryUsage = 0;
        quickSortMemoryUsage = 0;

        // Копии для тестов
        vector<int> arr1 = arr;
        vector<int> arr2 = arr;

        // Запускаем с подсчетом памяти
        MergeSortWithMemoryTracking(arr1, 0, N - 1);
        QuickSortWithMemoryTracking(arr2, 0, N - 1);

        // Теоретические расчеты
        size_t mergeTheory = N * sizeof(int);  // O(n) для временного массива
        size_t quickTheory = (size_t)(log2(N)) * sizeof(void*) * 8;  // O(log n) для стека

        cout << N;
        cout << " | " << mergeSortMemoryUsage / 1024 << " KB";
        cout << " | " << quickSortMemoryUsage / 1024 << " KB";
        cout << endl;
    }

    cout << "\n==================================================\n";
   
}