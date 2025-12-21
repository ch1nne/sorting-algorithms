#include "DataTypesAnalysis.h"
#include "DataGenerators.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "Metrics.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;
using namespace DataGenerators;

void runDataTypesAnalysis() {
    const int N = 1000;  // Фиксированный размер
    cout << "\nСРАВНЕНИЕ АЛГОРИТМОВ НА РАЗНЫХ ТИПАХ ДАННЫХ (n = " << N << ")\n";
    cout << "================================================================\n\n";

    // Определяем тестовые случаи с НОВЫМИ именами функций
    struct TestCase {
        string name;
        vector<int>(*generator)(int, int);
    };

    TestCase testCases[] = {
        {"Случайные числа", generateRandomData},           // Используем generateRandomData
        {"Уже отсортированные", generateSortedData},       // Используем generateSortedData
        {"Обратно отсортированные", generateReverseSortedData}, // Используем generateReverseSortedData
        {"Почти отсортированные", generateAlmostSortedData},    // Используем generateAlmostSortedData
        {"Много одинаковых чисел", generateManyDuplicatesData}  // Используем generateManyDuplicatesData
    };

    // Параметры для каждой функции
    int params[] = {
        1000,  // max_value для случайных чисел
        0,     // не используется для отсортированных
        0,     // не используется для обратно отсортированных
        10,    // количество перестановок для почти отсортированных
        5      // количество уникальных значений для дубликатов
    };

    cout << fixed << setprecision(0);

    // Проходим по всем типам данных
    for (size_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i) {
        const auto& test = testCases[i];
        int param = params[i];

        cout << "\n" << test.name << ":\n";
        cout << string(50, '-') << "\n";

        // Генерируем массив
        vector<int> arr = test.generator(N, param);

        // Копии для каждого алгоритма
        vector<int> arr1 = arr;  // для MergeSort
        vector<int> arr2 = arr;  // для QuickSort  
        vector<int> arr3 = arr;  // для std::sort

        // 1. MERGESORT
        long long mergeComp = 0, mergeAssign = 0;
        auto start = high_resolution_clock::now();
        if (!arr1.empty()) {
            MergeSortWithMetrics(arr1, 0, static_cast<int>(arr1.size()) - 1, mergeComp, mergeAssign);
        }
        auto end = high_resolution_clock::now();
        auto mergeTime = duration_cast<microseconds>(end - start).count();
        long long mergeTotalOps = mergeComp + mergeAssign;

        // 2. QUICKSORT
        long long quickComp = 0, quickSwaps = 0;
        start = high_resolution_clock::now();
        if (!arr2.empty()) {
            QuickSortWithMetrics(arr2, 0, static_cast<int>(arr2.size()) - 1, quickComp, quickSwaps);
        }
        end = high_resolution_clock::now();
        auto quickTime = duration_cast<microseconds>(end - start).count();
        long long quickTotalOps = quickComp + quickSwaps;

        // 3. STD::SORT (только время, операции неизвестны)
        start = high_resolution_clock::now();
        sort(arr3.begin(), arr3.end());
        end = high_resolution_clock::now();
        auto stdTime = duration_cast<microseconds>(end - start).count();

        // Выводим результаты в таблице
        cout << "| Алгоритм   | Время (мкс) | Операций всего |\n";
        cout << "|------------|-------------|----------------|\n";
        cout << "| MergeSort  | " << setw(11) << mergeTime << " | "
            << setw(14) << mergeTotalOps << " |\n";
        cout << "| QuickSort  | " << setw(11) << quickTime << " | "
            << setw(14) << quickTotalOps << " |\n";
        cout << "| std::sort  | " << setw(11) << stdTime << " | "
            << setw(14) << "N/A" << " |\n";
    }

    cout << "\n" << string(60, '=') << "\n";
    cout << "ВЫВОДЫ:\n";
    cout << "1. На случайных данных QuickSort быстрее и делает меньше операций\n";
    cout << "2. На отсортированных данных QuickSort медленнее из-за плохого выбора опорного\n";
    cout << "3. MergeSort стабилен на всех типах данных\n";
    cout << "4. std::sort обычно самый быстрый (оптимизированная реализация)\n";
}