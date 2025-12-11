#include <iostream>
#include <vector>
#include <climits> // Для INT_MAX (стража)

using namespace std;


void Merge(vector<int>& A, int p, int q, int r) {

    // Вычисляем размеры левого и правого подмассивов
    int n1 = q - p + 1; // Длина левого подмассива A[p..q]
    int n2 = r - q;     // Длина правого подмассива A[q+1..r]

    // оздаем временные массивы L и R с дополнительным местом для стража
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    // Копируем данные во временные массивы L и R
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[q + 1 + j];
    }

    // Устанавливаем стражи в концы массивов
    // Стражи гарантируют, что мы никогда не выйдем за пределы массивов L и R
    L[n1] = INT_MAX;
    R[n2] = INT_MAX; 

    // Слияние двух массивов L и R обратно в A[p..r]
    int i = 0; // Индекс в L
    int j = 0; // Индекс в R

    for (int k = p; k <= r; k++) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
    }
    
}

// Сортировка слиянием
void MergeSort(vector<int>& A, int p, int r) {
    if (p < r) { // Массив из одного элемента уже отсортирован
        // Находим середину подмассива
        int q = p + (r - p) / 2;

        // Рекурсивно сортируем левую и правую половины
        MergeSort(A, p, q);      // Сортировка левой половины A[p..q]
        MergeSort(A, q + 1, r);  // Сортировка правой половины A[q+1..r]

        // Сливаем две отсортированные половины
        Merge(A, p, q, r);
    }
}

int Partition(vector<int>& A, int p, int r) {
    // Опорный элемент - последний элемент подмассива
    int x = A[r];

    // Инициализируем границу i для элементов <= x
    int i = p - 1;

    // Проходим по всем элементам, кроме последнего (опорного)
    for (int j = p; j <= r - 1; j++) {

        // Если текущий элемент меньше или равен опорному
        if (A[j] <= x) {
         
            i = i + 1;   // Увеличиваем границу i
            swap(A[i], A[j]);   // И меняем местами A[i] и A[j]
        }
        // Если A[j] > x, просто увеличиваем j (правая область расширяется)
    }

    // Помещаем опорный элемент на его окончательную позицию
    swap(A[i + 1], A[r]);

    // Возвращаем индекс опорного элемента
    return i + 1;
}

void QuickSort(vector<int>& A, int p, int r) {

    if (p < r) {

        int q = Partition(A, p, r);

        QuickSort(A, p, q - 1);
        QuickSort(A, q + 1, r);
    }
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

    //MergeSort(arr, 0, n-1);
    //cout << "Сортировка слиянием: ";
    //for (int num : arr) cout << num << " ";
    //cout << endl;

    QuickSort(arr, 0, n - 1);
    cout << "Быстрая сортировка: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
}