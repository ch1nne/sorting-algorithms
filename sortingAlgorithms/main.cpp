#include <iostream>
#include "MergeSort.h"
#include "QuickSort.h"
#include "PerformanceTests.h"
#include "OperationsAnalysis.h"
#include "Utils.h"
#include <algorithm>

using namespace std;

void demonstrateManualInput() {
    auto arr = inputArrayFromUser();

    cout << "\nИсходный массив: ";
    printArray(arr);

    // QuickSort
    vector<int> quickResult = arr;
    if (!quickResult.empty()) {
        QuickSort(quickResult, 0, quickResult.size() - 1);
    }
    cout << "QuickSort: ";
    printArray(quickResult);

    // MergeSort
    vector<int> mergeResult = arr;
    if (!mergeResult.empty()) {
        MergeSort(mergeResult, 0, mergeResult.size() - 1);
    }
    cout << "MergeSort: ";
    printArray(mergeResult);

    // std::sort для проверки
    vector<int> stdResult = arr;
    sort(stdResult.begin(), stdResult.end());
    cout << "std::sort (эталон): ";
    printArray(stdResult);
}

int main() {
    setlocale(LC_ALL, "Russian");

    while (true) {
        cout << "\nМЕНЮ ПРОГРАММЫ:\n";
        cout << "1. Демонстрация работы на ручном вводе\n";
        cout << "2. Запуск тестов производительности (10,000 тестов на размер)\n";
        cout << "3. Анализ количества операций (сравнения и обмены)\n";
        cout << "4. Выход\n";
        cout << "Выберите пункт: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            demonstrateManualInput();
        }
        else if (choice == 2) {
            runPerformanceTests();
        }
        else if (choice == 3) {
            runOperationsAnalysis();
        }
        else if (choice == 4) {
            cout << "Выход из программы.\n";
            break;
        }
        else {
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}