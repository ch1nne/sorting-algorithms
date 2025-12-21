#pragma once
#include <iostream>

using namespace std;

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