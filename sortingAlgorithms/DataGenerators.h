#pragma once
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

namespace DataGenerators {

    // Cлучайный массив
    vector<int> generateRandomData(int n, int max_value);

    // Уже отсортированный по возрастанию (с двумя параметрами)
    vector<int> generateSortedData(int n, int dummy = 0);

    // Обратно отсортированный (по убыванию) (с двумя параметрами)
    vector<int> generateReverseSortedData(int n, int dummy = 0);

    // Почти отсортированный (делаем несколько случайных обменов)
    vector<int> generateAlmostSortedData(int n, int num_swaps = 10);

    // Много одинаковых элементов
    vector<int> generateManyDuplicatesData(int n, int unique_count = 5);

    // Маленький диапазон значений
    vector<int> generateSmallRangeData(int n, int max_value = 10);
}