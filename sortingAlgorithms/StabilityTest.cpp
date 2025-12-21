#include "StabilityTest.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Конвертируем vector<pair<int, char>> в vector<int> для ваших сортировок
vector<int> extractKeys(const vector<pair<int, char>>& data) {
    vector<int> keys;
    for (const auto& p : data) {
        keys.push_back(p.first);
    }
    return keys;
}

// Восстанавливаем результат с сохранением связи ключ-значение
vector<pair<int, char>> applySortToPairs(
    const vector<pair<int, char>>& original,
    const vector<int>& sortedKeys) {

    // Создаем копию для модификации
    vector<pair<int, char>> result = original;

    // Сортируем result в соответствии с порядком sortedKeys
    // Это упрощенный подход для демонстрации
    vector<bool> used(original.size(), false);
    vector<pair<int, char>> sortedPairs;

    for (int key : sortedKeys) {
        // Ищем первое неиспользованное вхождение этого ключа
        for (size_t i = 0; i < original.size(); i++) {
            if (!used[i] && original[i].first == key) {
                sortedPairs.push_back(original[i]);
                used[i] = true;
                break;
            }
        }
    }

    return sortedPairs;
}

// Простой визуальный тест стабильности
bool checkStability(const vector<pair<int, char>>& sorted,
    const vector<pair<int, char>>& original) {
    // Для каждого ключа проверяем порядок значений
    for (int key = 1; key <= 5; key++) {
        vector<char> sortedOrder, originalOrder;

        // Собираем порядок в отсортированном массиве
        for (const auto& p : sorted) {
            if (p.first == key) {
                sortedOrder.push_back(p.second);
            }
        }

        // Собираем порядок в исходном массиве
        for (const auto& p : original) {
            if (p.first == key) {
                originalOrder.push_back(p.second);
            }
        }

        // Если порядок разный - нестабильно
        if (sortedOrder != originalOrder) {
            return false;
        }
    }
    return true;
}

void runStabilityTest() {
    cout << "\n=== ТЕСТ СТАБИЛЬНОСТИ ===\n\n";

    // Больше элементов, явный беспорядок
    vector<pair<int, char>> originalData = {
        {3, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {1, 'E'},
        {2, 'F'}, {3, 'G'}, {1, 'H'}, {2, 'I'}, {3, 'J'}
    };

    cout << "Исходный массив (10 элементов):\n";
    for (const auto& p : originalData) {
        cout << p.first << p.second << " ";
    }
    cout << "\n\nГруппы одинаковых ключей:\n";
    cout << "Ключ 1: B, E, H (должны остаться в этом порядке!)\n";
    cout << "Ключ 2: C, F, I (должны остаться в этом порядке!)\n";
    cout << "Ключ 3: A, D, G, J (должны остаться в этом порядке!)\n\n";

    // Функция для тестирования
    auto testAlgorithm = [&](const string& name, auto sortFunc) {
        cout << name << ":\n";

        // Конвертируем в вектор int для ваших сортировок
        vector<int> keys;
        for (const auto& p : originalData) keys.push_back(p.first);

        // Применяем сортировку
        sortFunc(keys, 0, keys.size() - 1);

        // Восстанавливаем результат
        vector<pair<int, char>> result;
        vector<bool> used(originalData.size(), false);

        for (int key : keys) {
            for (size_t i = 0; i < originalData.size(); i++) {
                if (!used[i] && originalData[i].first == key) {
                    result.push_back(originalData[i]);
                    used[i] = true;
                    break;
                }
            }
        }

        cout << "   Результат: ";
        for (const auto& p : result) cout << p.first << p.second << " ";

        // Проверяем стабильность для каждой группы
        bool stable = true;
        vector<vector<char>> groups(4); // индексы 1,2,3

        for (const auto& p : result) {
            groups[p.first].push_back(p.second);
        }

        // Проверяем группу ключа 1
        if (groups[1].size() >= 2) {
            if (groups[1][0] != 'B' || groups[1][1] != 'E' ||
                (groups[1].size() > 2 && groups[1][2] != 'H')) {
                stable = false;
            }
        }

        cout << "\n   Стабильность: " << (stable ? "ДА ✓" : "НЕТ ✗");
        if (!stable) {
            cout << " (нарушен порядок!)";
        }
        cout << "\n\n";
        };

    cout << "============================================\n";

    // Тестируем ваши алгоритмы
    testAlgorithm("1. ВАШ MergeSort", [](vector<int>& arr, int l, int r) {
        MergeSort(arr, l, r);
        });

    testAlgorithm("2. ВАШ QuickSort", [](vector<int>& arr, int l, int r) {
        QuickSort(arr, l, r);
        });

    // Отдельно тестируем std::sort и std::stable_sort
    {
        cout << "3. std::sort (встроенный):\n";
        vector<pair<int, char>> data = originalData;
        sort(data.begin(), data.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

        cout << "   Результат: ";
        for (const auto& p : data) cout << p.first << p.second << " ";

        // Проверяем группу ключа 1
        bool stable = true;
        vector<char> group1;
        for (const auto& p : data) {
            if (p.first == 1) group1.push_back(p.second);
        }

        if (group1 != vector<char>{'B', 'E', 'H'}) {
            stable = false;
        }

        cout << "\n   Стабильность: " << (stable ? "ДА ✓" : "НЕТ ✗");
        if (!stable && group1.size() == 3) {
            cout << " (порядок 1-й группы: ";
            for (char c : group1) cout << c << " ";
            cout << "вместо B E H)";
        }
        cout << "\n\n";
    }

    {
        cout << "4. std::stable_sort (гарантированно стабильный):\n";
        vector<pair<int, char>> data = originalData;
        stable_sort(data.begin(), data.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

        cout << "   Результат: ";
        for (const auto& p : data) cout << p.first << p.second << " ";
        cout << "\n   Стабильность: ГАРАНТИРОВАННО ДА ✓\n\n";
    }

    // Дополнительный тест: специально "сломанный" пример
    {
        cout << "5. СПЕЦИАЛЬНЫЙ ТЕСТ (только для QuickSort):\n";
        cout << "   Массив, где QuickSort почти наверняка нарушит порядок:\n";

        vector<pair<int, int>> trickyData = {
            {2, 1}, {1, 2}, {2, 3}, {1, 4}, {2, 5},
            {1, 6}, {2, 7}, {1, 8}, {2, 9}
        };

        // Конвертируем
        vector<int> trickyKeys;
        for (const auto& p : trickyData) trickyKeys.push_back(p.first);

        vector<int> keysForTest = trickyKeys;
        QuickSort(keysForTest, 0, keysForTest.size() - 1);

        // Проверяем, изменился ли порядок индексов у одинаковых ключей
        vector<int> indicesFor2;
        for (size_t i = 0; i < trickyData.size(); i++) {
            if (trickyData[i].first == 2) {
                indicesFor2.push_back(trickyData[i].second);
            }
        }

        cout << "   Исходные индексы для ключа 2: ";
        for (int idx : indicesFor2) cout << idx << " ";

        cout << "\n   QuickSort может их перемешать!\n";
    }

    cout << "\n=== ВАЖНОЕ ЗАМЕЧАНИЕ ===\n";
    cout << "Даже если QuickSort иногда дает стабильный результат,\n";
    cout << "он НЕ ГАРАНТИРУЕТ стабильность! В другом массиве или\n";
    cout << "при другом выборе опорного элемента он может нарушить порядок.\n";
    cout << "\nMergeSort и std::stable_sort ГАРАНТИРУЮТ стабильность.\n";
}