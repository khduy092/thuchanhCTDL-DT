#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Cấu trúc lưu trữ kết quả
struct KetQua {
    long long soLanSoSanh;
    long long soLanDoiCho;
    long long thoiGianChay; // Thời gian chạy (microseconds)
};

// Hàm tạo mảng ngẫu nhiên
vector<int> taoMangNgauNhien(int n) {
    vector<int> arr(n);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000; // Số ngẫu nhiên từ 0 đến 99999
    }
    return arr;
}

// Bubble Sort
KetQua bubbleSort(vector<int>& arr) {
    KetQua kq = {0, 0, 0};
    int n = arr.size();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            kq.soLanSoSanh++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                kq.soLanDoiCho++;
            }
        }
    }
    auto end = high_resolution_clock::now();
    kq.thoiGianChay = duration_cast<microseconds>(end - start).count();
    return kq;
}

// Selection Sort
KetQua selectionSort(vector<int>& arr) {
    KetQua kq = {0, 0, 0};
    int n = arr.size();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            kq.soLanSoSanh++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            kq.soLanDoiCho++;
        }
    }
    auto end = high_resolution_clock::now();
    kq.thoiGianChay = duration_cast<microseconds>(end - start).count();
    return kq;
}

// Insertion Sort
KetQua insertionSort(vector<int>& arr) {
    KetQua kq = {0, 0, 0};
    int n = arr.size();
    auto start = high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            kq.soLanSoSanh++;
            arr[j + 1] = arr[j];
            j--;
            kq.soLanDoiCho++;
        }
        arr[j + 1] = key;
    }
    auto end = high_resolution_clock::now();
    kq.thoiGianChay = duration_cast<microseconds>(end - start).count();
    return kq;
}

// Quick Sort
int partition(vector<int>& arr, int low, int high, KetQua& kq) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        kq.soLanSoSanh++;
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
            kq.soLanDoiCho++;
        }
    }
    swap(arr[i + 1], arr[high]);
    kq.soLanDoiCho++;
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high, KetQua& kq) {
    if (low < high) {
        int pi = partition(arr, low, high, kq);
        quickSort(arr, low, pi - 1, kq);
        quickSort(arr, pi + 1, high, kq);
    }
}

KetQua quickSort(vector<int>& arr) {
    KetQua kq = {0, 0, 0};
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1, kq);
    auto end = high_resolution_clock::now();
    kq.thoiGianChay = duration_cast<microseconds>(end - start).count();
    return kq;
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right, KetQua& kq) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        kq.soLanSoSanh++;
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

void mergeSort(vector<int>& arr, int left, int right, KetQua& kq) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid, kq);
        mergeSort(arr, mid + 1, right, kq);
        merge(arr, left, mid, right, kq);
    }
}

KetQua mergeSort(vector<int>& arr) {
    KetQua kq = {0, 0, 0};
    auto start = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1, kq);
    auto end = high_resolution_clock::now();
    kq.thoiGianChay = duration_cast<microseconds>(end - start).count();
    return kq;
}

// Hàm in kết quả
void inKetQua(const string& tenThuatToan, const KetQua& kq) {
    cout << tenThuatToan << ":\n";
    cout << " - So lan so sanh: " << kq.soLanSoSanh << "\n";
    cout << " - So lan doi cho: " << kq.soLanDoiCho << "\n";
    cout << " - Thoi gian chay: " << kq.thoiGianChay << " microseconds\n";
}

int main() {
    vector<int> n_values = {10, 100, 200, 500, 1000, 2000, 5000, 10000};
    int t = 5; // Số lần lặp lại

    for (int n : n_values) {
        cout << "Kich thuoc mang: " << n << "\n";
        for (int i = 0; i < t; i++) {
            vector<int> arr = taoMangNgauNhien(n);

            // Bubble Sort
            vector<int> arr_bubble = arr;
            KetQua kq_bubble = bubbleSort(arr_bubble);
            inKetQua("Bubble Sort", kq_bubble);

            // Selection Sort
            vector<int> arr_selection = arr;
            KetQua kq_selection = selectionSort(arr_selection);
            inKetQua("Selection Sort", kq_selection);

            // Insertion Sort
            vector<int> arr_insertion = arr;
            KetQua kq_insertion = insertionSort(arr_insertion);
            inKetQua("Insertion Sort", kq_insertion);

            // Quick Sort
            vector<int> arr_quick = arr;
            KetQua kq_quick = quickSort(arr_quick);
            inKetQua("Quick Sort", kq_quick);

            // Merge Sort
            vector<int> arr_merge = arr;
            KetQua kq_merge = mergeSort(arr_merge);
            inKetQua("Merge Sort", kq_merge);

            cout << "----------------------------\n";
        }
    }

    return 0;
}