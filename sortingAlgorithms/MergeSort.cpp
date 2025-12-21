#include "MergeSort.h"
#include "Metrics.h"
#include <climits>

using namespace std;

// Обычная версия
void Merge(vector<int>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> L(n1 + 1), R(n2 + 1);

    for (int i = 0; i < n1; i++) L[i] = A[p + i];
    for (int j = 0; j < n2; j++) R[j] = A[q + 1 + j];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        }
        else {
            A[k] = R[j++];
        }
    }
}

void MergeSort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

// Версия с метриками
void MergeWithMetrics(vector<int>& A, int p, int q, int r,
    long long& comparisons, long long& assignments) {
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<int> L(n1 + 1), R(n2 + 1);

    for (int i = 0; i < n1; i++) L[i] = A[p + i];
    for (int j = 0; j < n2; j++) R[j] = A[q + 1 + j];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        comparisons++; // Считаем сравнение L[i] <= R[j]
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        }
        else {
            A[k] = R[j++];
        }
        assignments++; // Каждое присваивание в массив A
    }
}

void MergeSortWithMetrics(vector<int>& A, int p, int r,
    long long& comparisons, long long& swaps) {
    if (p < r) {
        int q = p + (r - p) / 2;
        MergeSortWithMetrics(A, p, q, comparisons, swaps);
        MergeSortWithMetrics(A, q + 1, r, comparisons, swaps);
        MergeWithMetrics(A, p, q, r, comparisons, swaps);
    }
}