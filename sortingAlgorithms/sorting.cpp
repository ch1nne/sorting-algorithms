#include <iostream>
#include <vector>
#include <climits> // Для INT_MAX (стража)
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;
using namespace std::chrono;

void Merge(vector<int>& A, int p, int q, int r) {

    // Вычисляем размеры левого и правого подмассивов
    int n1 = q - p + 1; // Длина левого подмассива A[p..q]
    int n2 = r - q;     // Длина правого подмассива A[q+1..r]

    // оздаем временные массивы L и R с дополнительным местом для стража
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    // Копируем данные во временные массивы L и R
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[q + 1 + j];
    }

    // Устанавливаем стражи в концы массивов
    // Стражи гарантируют, что мы никогда не выйдем за пределы массивов L и R
    L[n1] = INT_MAX;
    R[n2] = INT_MAX; 

    // Слияние двух массивов L и R обратно в A[p..r]
    int i = 0; // Индекс в L
    int j = 0; // Индекс в R

    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
    }
    
}

// Сортировка слиянием
void MergeSort(vector<int>& A, int p, int r) {
    if (p < r) { // Массив из одного элемента уже отсортирован
        // Находим середину подмассива
        int q = p + (r - p) / 2;

        // Рекурсивно сортируем левую и правую половины
        MergeSort(A, p, q);      // Сортировка левой половины A[p..q]
        MergeSort(A, q + 1, r);  // Сортировка правой половины A[q+1..r]

        // Сливаем две отсортированные половины
        Merge(A, p, q, r);
    }
}

int Partition(vector<int>& A, int p, int r) {
    // Опорный элемент - последний элемент подмассива
    int x = A[r];

    // Инициализируем границу i для элементов <= x
    int i = p - 1;

    // Проходим по всем элементам, кроме последнего (опорного)
    for (int j = p; j <= r - 1; j++) {

        // Если текущий элемент меньше или равен опорному
        if (A[j] <= x) {
         
            i = i + 1;   // Увеличиваем границу i
            swap(A[i], A[j]);   // И меняем местами A[i] и A[j]
        }
        // Если A[j] > x, просто увеличиваем j (правая область расширяется)
    }

    // Помещаем опорный элемент на его окончательную позицию
    swap(A[i + 1], A[r]);

    // Возвращаем индекс опорного элемента
    return i + 1;
}

void QuickSort(vector<int>& A, int p, int r) {

    if (p < r) {

        int q = Partition(A, p, r);

        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

// Функция для генерации случайного массива
vector<int> generateRandomArray(int n, int max_value) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, max_value);

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = distrib(gen);
    }
    return arr;
}

// Функция тестирования производительности
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

        // Максимальное значение согласно вашим требованиям: 10^n
        int max_value = pow(10, min(n, 6)); // Ограничиваем, чтобы избежать переполнения

        for (int test = 0; test < NUM_TESTS_PER_SIZE; test++) {
            // Генерируем случайный массив
            vector<int> original = generateRandomArray(n, max_value);

            // ТЕСТ MERGESORT (прямой вызов)
            vector<int> arr1 = original;
            auto start = high_resolution_clock::now();
            if (!arr1.empty()) {
                MergeSort(arr1, 0, arr1.size() - 1);
            }
            auto end = high_resolution_clock::now();
            totalMergeTime += duration_cast<microseconds>(end - start).count();

            // ТЕСТ QUICKSORT (прямой вызов)
            vector<int> arr2 = original;
            start = high_resolution_clock::now();
            if (!arr2.empty()) {
                QuickSort(arr2, 0, arr2.size() - 1);
            }
            end = high_resolution_clock::now();
            totalQuickTime += duration_cast<microseconds>(end - start).count();

            // ТЕСТ std::sort
            vector<int> arr3 = original;
            start = high_resolution_clock::now();
            sort(arr3.begin(), arr3.end());
            end = high_resolution_clock::now();
            totalStdSortTime += duration_cast<microseconds>(end - start).count();
        }

        // Вычисляем средние значения
        double avgMerge = (double)totalMergeTime / NUM_TESTS_PER_SIZE;
        double avgQuick = (double)totalQuickTime / NUM_TESTS_PER_SIZE;
        double avgStd = (double)totalStdSortTime / NUM_TESTS_PER_SIZE;

        // Выводим строку таблицы
        cout << "| " << setw(6) << n << " | "
            << setw(13) << avgMerge << " | "
            << setw(13) << avgQuick << " | "
            << setw(13) << avgStd << " |\n";
    }

    cout << "=====================================================================\n";
}

// Функция для проверки корректности
void testCorrectness() {
    cout << "\nТЕСТИРОВАНИЕ КОРРЕКТНОСТИ АЛГОРИТМОВ\n";
    cout << "====================================\n";

    vector<vector<int>> testCases = {
        {},
        {1},
        {2, 1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {3, 7, 2, 8, 1, 9, 4, 6, 5},
        {5, 5, 5, 5, 5},
        {1, 3, 2, 4, 2, 3, 1}
    };

    int testNumber = 1;
    for (auto& testCase : testCases) {
        cout << "Тест " << testNumber++ << ": ";

        vector<int> arr1 = testCase;
        vector<int> arr2 = testCase;
        vector<int> arr3 = testCase;

        // Сортируем тремя способами
        if (!arr1.empty()) MergeSort(arr1, 0, arr1.size() - 1);
        if (!arr2.empty()) QuickSort(arr2, 0, arr2.size() - 1);
        sort(arr3.begin(), arr3.end());

        bool mergeOk = (arr1 == arr3);
        bool quickOk = (arr2 == arr3);

        cout << "MergeSort: " << (mergeOk ? "ПРОЙДЕН" : "ОШИБКА") << ", ";
        cout << "QuickSort: " << (quickOk ? "ПРОЙДЕН" : "ОШИБКА") << endl;
    }

    cout << "====================================\n";
}

int main() {

    setlocale(LC_ALL, "Russian");

    while (true) {
        cout << "\nМЕНЮ ПРОГРАММЫ:\n";
        cout << "1. Демонстрация работы на ручном вводе\n";
        cout << "2. Запуск тестов производительности (10,000 тестов на размер)\n";
        cout << "3. Проверка корректности алгоритмов\n";
        cout << "4. Выход\n";
        cout << "Выберите пункт: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // Режим ручного ввода
            int n;
            cout << "Введите количество элементов: ";
            cin >> n;

            vector<int> arr(n);
            cout << "Введите " << n << " элементов:\n";
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }

            cout << "\nИсходный массив: ";
            for (int num : arr) cout << num << " ";
            cout << endl;

            // QuickSort
            vector<int> quickResult = arr;
            if (!quickResult.empty()) {
                QuickSort(quickResult, 0, quickResult.size() - 1);
            }
            cout << "QuickSort: ";
            for (int num : quickResult) cout << num << " ";
            cout << endl;

            // MergeSort
            vector<int> mergeResult = arr;
            if (!mergeResult.empty()) {
                MergeSort(mergeResult, 0, mergeResult.size() - 1);
            }
            cout << "MergeSort: ";
            for (int num : mergeResult) cout << num << " ";
            cout << endl;

            // std::sort для проверки
            vector<int> stdResult = arr;
            sort(stdResult.begin(), stdResult.end());
            cout << "std::sort (эталон): ";
            for (int num : stdResult) cout << num << " ";
            cout << endl;

        }
        else if (choice == 2) {
            runPerformanceTests();

        }
        else if (choice == 3) {
            testCorrectness();

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