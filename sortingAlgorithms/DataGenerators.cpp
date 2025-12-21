#include "DataGenerators.h"
#include <random>
#include <algorithm>

using namespace std;

namespace DataGenerators {

    // Новая функция генерации случайного массива
    vector<int> generateRandomData(int n, int max_value) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, max_value);

        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = distrib(gen);
        }
        return arr;
    }

    // Уже отсортированный
    vector<int> generateSortedData(int n, int dummy) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1;  // 1, 2, 3, ..., n
        }
        return arr;
    }

    // Обратно отсортированный
    vector<int> generateReverseSortedData(int n, int dummy) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = n - i;  // n, n-1, n-2, ..., 1
        }
        return arr;
    }

    // Почти отсортированный
    vector<int> generateAlmostSortedData(int n, int num_swaps) {
        vector<int> arr = generateSortedData(n, 0);

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, n - 1);

        for (int i = 0; i < num_swaps; i++) {
            int a = distrib(gen);
            int b = distrib(gen);
            swap(arr[a], arr[b]);
        }
        return arr;
    }

    // Много одинаковых элементов
    vector<int> generateManyDuplicatesData(int n, int unique_count) {
        vector<int> arr(n);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, unique_count);

        for (int i = 0; i < n; i++) {
            arr[i] = distrib(gen);
        }
        return arr;
    }

    // Маленький диапазон значений
    vector<int> generateSmallRangeData(int n, int max_value) {
        return generateRandomData(n, max_value);
    }
}