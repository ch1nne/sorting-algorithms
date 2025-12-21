#include "Utils.h"
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

// Генерация случайного массива с указанным максимальным значением
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

// Генерация случайного массива с максимальным значением по умолчанию
vector<int> generateRandomArray(int n) {
    return generateRandomArray(n, 1000); // значение по умолчанию
}

// Получение массива от пользователя
vector<int> inputArrayFromUser() {
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Введите " << n << " элементов:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return arr;
}

// Вывод массива в консоль
void printArray(const vector<int>& arr) {
    for (int num : arr) cout << num << " ";
    cout << endl;
}

// Проверка отсортирован ли массив по возрастанию
bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}