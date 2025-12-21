#include "Utils.h"
#include <iostream>
#include <random>
#include <cmath>

using namespace std;

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

vector<int> generateRandomArray(int n) {
    return generateRandomArray(n, 1000); // значение по умолчанию
}

vector<int> inputArrayFromUser() {
    int n;
    cout << "¬ведите количество элементов: ";
    cin >> n;

    vector<int> arr(n);
    cout << "¬ведите " << n << " элементов:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return arr;
}

void printArray(const vector<int>& arr) {
    for (int num : arr) cout << num << " ";
    cout << endl;
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}