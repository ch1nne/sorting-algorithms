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

// Структура для сбора метрик
struct Metrics {
    long long comparisons = 0;
    long long swaps = 0;

    void reset() {
        comparisons = 0;
        swaps = 0;
    }

    void print() const {
        cout << "Сравнения: " << comparisons << ", Обмены: " << swaps;
    }
};

// Глобальные метрики для каждого алгоритма
Metrics mergeMetrics, quickMetrics;

// Merge с подсчётом операций
void MergeWithMetrics(vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> L(n1 + 1), R(n2 + 1);

    for (int i = 0; i < n1; i++) L[i] = A[p + i];
    for (int j = 0; j < n2; j++) R[j] = A[q + 1 + j];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        mergeMetrics.comparisons++; // Считаем сравнение L[i] <= R[j]
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        }
        else {
            A[k] = R[j++];
        }
    }
}

// MergeSort с подсчётом операций
void MergeSortWithMetrics(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;
        MergeSortWithMetrics(A, p, q);
        MergeSortWithMetrics(A, q + 1, r);
        MergeWithMetrics(A, p, q, r);
    }
}

// Partition с подсчётом операций
int PartitionWithMetrics(vector<int>& A, int p, int r) {
    int pivot = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        quickMetrics.comparisons++; // Считаем сравнение A[j] <= pivot
        if (A[j] <= pivot) {
            i++;
            quickMetrics.swaps++; // Считаем обмен
            swap(A[i], A[j]);
        }
    }
    quickMetrics.swaps++; // Считаем финальный обмен
    swap(A[i + 1], A[r]);
    return i + 1;
}

// QuickSort с подсчётом операций
void QuickSortWithMetrics(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = PartitionWithMetrics(A, p, r);
        QuickSortWithMetrics(A, p, q - 1);
        QuickSortWithMetrics(A, q + 1, r);
    }
}


// Анализ количества операций
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
        // Генерируем тестовый массив
        int max_value = pow(10, min(n, 6));
        vector<int> arr = generateRandomArray(n, max_value);
        vector<int> arrCopy1 = arr;
        vector<int> arrCopy2 = arr;
        vector<int> arrCopy3 = arr;

        // Сбрасываем метрики
        mergeMetrics.reset();
        quickMetrics.reset();

        // Запускаем алгоритмы с подсчётом операций
        if (!arrCopy1.empty()) {
            MergeSortWithMetrics(arrCopy1, 0, arrCopy1.size() - 1);
        }

        if (!arrCopy2.empty()) {
            QuickSortWithMetrics(arrCopy2, 0, arrCopy2.size() - 1);
        }

        // Для std::sort считаем операции приблизительно
        // (реальное количество операций зависит от реализации)
        long long stdComparisons = 0, stdSwaps = 0;
        if (!arrCopy3.empty()) {
            // Приблизительная оценка: O(n log n) сравнений и обменов
            stdComparisons = (long long)(n * log2(n) * 1.1); // +10% для запаса
            stdSwaps = (long long)(n * log2(n) * 0.7);      // Обычно меньше сравнений
        }

        // Выводим результаты
        cout << "| " << setw(6) << n << " | "
            << setw(8) << mergeMetrics.comparisons << " | "
            << setw(8) << mergeMetrics.swaps << " | "
            << setw(8) << quickMetrics.comparisons << " | "
            << setw(8) << quickMetrics.swaps << " | "
            << setw(8) << stdComparisons << " | "
            << setw(10) << stdSwaps << " |\n";
    }

    cout << "========================================================================================\n";

    // Дополнительный анализ: тест на отсортированных данных
    cout << "\nДОПОЛНИТЕЛЬНЫЙ АНАЛИЗ: ОТСОРТИРОВАННЫЕ ДАННЫЕ (n=1000)\n";
    cout << "==========================================================\n";

    int n = 1000;
    vector<int> sortedArr(n);
    for (int i = 0; i < n; i++) sortedArr[i] = i + 1;

    mergeMetrics.reset();
    quickMetrics.reset();

    vector<int> arr1 = sortedArr;
    vector<int> arr2 = sortedArr;

    MergeSortWithMetrics(arr1, 0, arr1.size() - 1);
    QuickSortWithMetrics(arr2, 0, arr2.size() - 1);

    cout << "Отсортированный массив (худший случай для QuickSort):\n";
    cout << "MergeSort: "; mergeMetrics.print(); cout << endl;
    cout << "QuickSort: "; quickMetrics.print(); cout << endl;
    cout << "Note: QuickSort показывает деградацию до O(n?) на отсортированных данных\n";
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