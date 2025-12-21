#pragma once
#include <vector>

using namespace std;

// Генерация случайного массива с указанным максимальным значением
vector<int> generateRandomArray(int n, int max_value);

// Генерация случайного массива с максимальным значением по умолчанию
vector<int> generateRandomArray(int n);

// Получение массива от пользователя
vector<int> inputArrayFromUser();


void printArray(const vector<int>& arr);
bool isSorted(const vector<int>& arr);