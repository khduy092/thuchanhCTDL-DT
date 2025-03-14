#include <iostream>
#include <vector>
using namespace std;

// Sắp xếp đổi chỗ trực tiếp (Interchange Sort)
void interchangeSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[i] > arr[j])
                swap(arr[i], arr[j]);
        }
    }
}

// Sắp xếp chọn trực tiếp (Selection Sort)
void selectionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Sắp xếp chèn trực tiếp (Insertion Sort)
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Sắp xếp nổi bọt (Bubble Sort)
void bubbleSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Hàm in mảng
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Mảng đầu vào
    vector<int> arr1 = {39, 8, 5, 1, 3, 6, 9, 12, 4, 7, 10};
    vector<int> arr2 = arr1, arr3 = arr1, arr4 = arr1;

    cout << "Mang ban dau: ";
    printArray(arr1);

    // Áp dụng thuật toán Interchange Sort
    interchangeSort(arr1);
    cout << "Sau Interchange Sort: ";
    printArray(arr1);

    // Áp dụng thuật toán Selection Sort
    selectionSort(arr2);
    cout << "Sau Selection Sort: ";
    printArray(arr2);

    // Áp dụng thuật toán Insertion Sort
    insertionSort(arr3);
    cout << "Sau Insertion Sort: ";
    printArray(arr3);

    // Áp dụng thuật toán Bubble Sort
    bubbleSort(arr4);
    cout << "Sau Bubble Sort: ";
    printArray(arr4);

    return 0;
}