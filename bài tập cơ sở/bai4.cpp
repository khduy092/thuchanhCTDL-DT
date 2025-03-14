#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

// Hàm tạo dữ liệu ngẫu nhiên và ghi vào file
void taoDuLieu(const string& filename, int n) {
    ofstream outFile(filename);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        outFile << rand() % 100000 << " ";
    }
    outFile.close();
}

// Hàm đọc dữ liệu từ file
vector<int> docDuLieu(const string& filename) {
    ifstream inFile(filename);
    vector<int> arr;
    int num;
    while (inFile >> num) {
        arr.push_back(num);
    }
    inFile.close();
    return arr;
}

// Hàm ghi kết quả sắp xếp và thời gian vào file
void ghiKetQua(const string& filename, const vector<int>& arr, long long time) {
    ofstream outFile(filename);
    outFile << "Thoi gian chay: " << time << " ms\n";
    for (int num : arr) {
        outFile << num << " ";
    }
    outFile.close();
}

// Các thuật toán sắp xếp
void interchangeSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
        }
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (int p = 0; p < k; p++) {
        arr[left + p] = temp[p];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Hàm đo thời gian chạy của một thuật toán
long long doThoiGian(void (*sortFunction)(vector<int>&), vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

long long doThoiGianQuickSort(void (*sortFunction)(vector<int>&, int, int), vector<int>& arr, int left, int right) {
    auto start = high_resolution_clock::now();
    sortFunction(arr, left, right);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

int main() {
    const string inputFile = "input.txt";
    const int n = 30000;

    // Tạo dữ liệu ngẫu nhiên
    taoDuLieu(inputFile, n);

    // Đọc dữ liệu từ file
    vector<int> arr = docDuLieu(inputFile);

    // Đo thời gian và sắp xếp
    vector<int> tempArr;

    // Interchange Sort
    tempArr = arr;
    long long time = doThoiGian(interchangeSort, tempArr);
    ghiKetQua("interchange_sort_output.txt", tempArr, time);
    cout << "Interchange Sort: " << time << " ms\n";

    // Selection Sort
    tempArr = arr;
    time = doThoiGian(selectionSort, tempArr);
    ghiKetQua("selection_sort_output.txt", tempArr, time);
    cout << "Selection Sort: " << time << " ms\n";

    // Insertion Sort
    tempArr = arr;
    time = doThoiGian(insertionSort, tempArr);
    ghiKetQua("insertion_sort_output.txt", tempArr, time);
    cout << "Insertion Sort: " << time << " ms\n";

    // Bubble Sort
    tempArr = arr;
    time = doThoiGian(bubbleSort, tempArr);
    ghiKetQua("bubble_sort_output.txt", tempArr, time);
    cout << "Bubble Sort: " << time << " ms\n";

    // Quick Sort
    tempArr = arr;
    time = doThoiGianQuickSort(quickSort, tempArr, 0, tempArr.size() - 1);
    ghiKetQua("quick_sort_output.txt", tempArr, time);
    cout << "Quick Sort: " << time << " ms\n";

    // Merge Sort
    tempArr = arr;
    time = doThoiGianQuickSort(mergeSort, tempArr, 0, tempArr.size() - 1);
    ghiKetQua("merge_sort_output.txt", tempArr, time);
    cout << "Merge Sort: " << time << " ms\n";

    // Heap Sort
    tempArr = arr;
    time = doThoiGian(heapSort, tempArr);
    ghiKetQua("heap_sort_output.txt", tempArr, time);
    cout << "Heap Sort: " << time << " ms\n";

    return 0;
}