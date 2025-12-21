#include "QuickSort.h"
#include "Metrics.h"
#include <algorithm>

using namespace std;

// ================== ÎÁÛ×ÍÀß ÂÅÐÑÈß ==================

int Partition(vector<int>& A, int p, int r) {
    int x = A[r];
    int i = p - 1;

    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i = i + 1;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

void QuickSort(vector<int>& A, int p, int r) {
    if (p < r) {
        int q = Partition(A, p, r);
        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
}

// ================== ÂÅÐÑÈß Ñ ÌÅÒÐÈÊÀÌÈ ==================

int PartitionWithMetrics(vector<int>& A, int p, int r,
    long long& comparisons, long long& swaps) {
    int pivot = A[r];
    int i = p - 1;

    for (int j = p; j < r; j++) {
        comparisons++;
        if (A[j] <= pivot) {
            i++;
            swap(A[i], A[j]);
            swaps++;
        }
    }
    swap(A[i + 1], A[r]);
    swaps++;
    return i + 1;
}

void QuickSortWithMetrics(vector<int>& A, int p, int r,
    long long& comparisons, long long& swaps) {
    if (p < r) {
        int q = PartitionWithMetrics(A, p, r, comparisons, swaps);
        QuickSortWithMetrics(A, p, q - 1, comparisons, swaps);
        QuickSortWithMetrics(A, q + 1, r, comparisons, swaps);
    }
}