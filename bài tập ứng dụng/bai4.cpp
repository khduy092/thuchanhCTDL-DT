#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Hàm kiểm tra số nguyên tố
bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Hàm tìm số nguyên tố lớn nhất trong ma trận
int findMaxPrime(const vector<vector<int>>& matrix) {
    int maxPrime = -1;
    for (const auto& row : matrix) {
        for (int num : row) {
            if (isPrime(num) && num > maxPrime) {
                maxPrime = num;
            }
        }
    }
    return maxPrime;
}

// Hàm tìm các dòng có chứa ít nhất một số nguyên tố
vector<int> findRowsWithPrimes(const vector<vector<int>>& matrix) {
    vector<int> rows;
    for (int i = 0; i < matrix.size(); i++) {
        for (int num : matrix[i]) {
            if (isPrime(num)) {
                rows.push_back(i);
                break;
            }
        }
    }
    return rows;
}

// Hàm tìm các dòng chỉ chứa toàn số nguyên tố
vector<int> findRowsWithOnlyPrimes(const vector<vector<int>>& matrix) {
    vector<int> rows;
    for (int i = 0; i < matrix.size(); i++) {
        bool allPrime = true;
        for (int num : matrix[i]) {
            if (!isPrime(num)) {
                allPrime = false;
                break;
            }
        }
        if (allPrime) rows.push_back(i);
    }
    return rows;
}

// Hàm nhập ma trận
void inputMatrix(vector<vector<int>>& matrix, int m, int n) {
    cout << "Nhap ma tran " << m << "x" << n << ":\n";
    for (int i = 0; i < m; i++) {
        matrix.push_back(vector<int>(n));
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
}

// Hàm in ma trận
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

int main() {
    int m, n;
    cout << "Nhap so dong m: ";
    cin >> m;
    cout << "Nhập so cot n: ";
    cin >> n;

    vector<vector<int>> matrix;
    inputMatrix(matrix, m, n);

    cout << "\nMa tran da nhap:\n";
    printMatrix(matrix);

    //Tìm số nguyên tố lớn nhất
    int maxPrime = findMaxPrime(matrix);
    if (maxPrime != -1)
        cout << "So nguyen to lon nhat trong ma tran: " << maxPrime << endl;
    else
        cout << "khong co so nguyen to trong ma tran.\n";

    //Tìm dòng có chứa ít nhất một số nguyên tố
    vector<int> rowsWithPrimes = findRowsWithPrimes(matrix);
    cout << "Cac dong co chua it nhat 1 so nguyen to: ";
    if (!rowsWithPrimes.empty()) {
        for (int row : rowsWithPrimes) cout << row + 1 << " ";
        cout << endl;
    } else {
        cout << "Khong co dong nao co chua so nguyen to.\n";
    }

    //Tìm dòng chỉ chứa toàn số nguyên tố
    vector<int> rowsWithOnlyPrimes = findRowsWithOnlyPrimes(matrix);
    cout << "Cac dong chi chua toan so nguyen to: ";
    if (!rowsWithOnlyPrimes.empty()) {
        for (int row : rowsWithOnlyPrimes) cout << row + 1 << " ";
        cout << endl;
    } else {
        cout << "Khong co dong nao chi chua toan so nguyen to.\n";
    }

    return 0;
}
