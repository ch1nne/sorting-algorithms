#include <iostream>
#include <vector>
using namespace std;

vector<int> quickSort(vector<int> arr) {

    if (arr.size() <= 1) {
        return arr;
    }

    int pivot = arr[0];
    vector<int> less, big;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] <= pivot) {
            less.push_back(arr[i]);
        }
        else {
            big.push_back(arr[i]);
        }
    }

    vector<int> result;
    vector<int> sortedLess = quickSort(less);
    vector<int> sortedBig = quickSort(big);

    result.insert(result.end(), sortedLess.begin(), sortedLess.end());
    result.push_back(pivot);
    result.insert(result.end(), sortedBig.begin(), sortedBig.end());

    return result;
}

vector<int> mergeSort(vector<int> arr) {

    if (arr.size() <= 1) {
        return arr;
    }

    int mid = arr.size() / 2;

    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    left = mergeSort(left);
    right = mergeSort(right);

    vector<int> result;
    int i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i]);
            i++;
        }
        else {
            result.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    return result;
}

int main() {

    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите количество элементов в массиве: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Введите " << n << " элементов массива:" << endl;
    for (int i = 0; i < n; i++) {
        int item;
        cin >> item;
        arr[i] = item;
    }

    cout << "\nИсходный массив: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    vector<int> quickSorted = quickSort(arr);
    cout << "Быстрая сортировка: ";
    for (int num : quickSorted) cout << num << " ";
    cout << endl;
    vector<int> mergeSorted = mergeSort(arr);
    cout << "Сортировка слиянием: ";
    for (int num : mergeSorted) cout << num << " ";
    cout << endl;
}


//int partition(vector<int>& arr, int low, int high) {
//    int pivot = arr[high];  //Опорный элемент - последний элемент
//    int i = low - 1;        //Индекс меньшего элемента
//
//    for (int j = low; j < high; j++) {
//        //Если текущий элемент меньше или равен опорному
//        if (arr[j] <= pivot) {
//            i++;  //Сдвигаем границу меньших элементов
//            swap(arr[i], arr[j]);  //Помещаем меньший элемент в левую часть
//        }
//    }
//    // Размещаем опорный элемент на правильную позицию
//    swap(arr[i + 1], arr[high]);
//    return i + 1;  // Возвращаем индекс опорного элемента
//}