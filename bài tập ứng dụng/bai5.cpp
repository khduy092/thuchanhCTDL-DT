#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Hàm tính tổng các phần tử của một dòng
int rowSum(const vector<int>& row) {
    int sum = 0;
    for (int num : row) {
        sum += num;
    }
    return sum;
}

// Hàm tìm dòng có tổng lớn nhất
int findMaxSumRowIndex(const vector<vector<int>>& matrix) {
    int maxIndex = 0;
    int maxSum = rowSum(matrix[0]);

    for (int i = 1; i < matrix.size(); i++) {
        int sum = rowSum(matrix[i]);
        if (sum > maxSum) {
            maxSum = sum;
            maxIndex = i;
        }
    }
    return maxIndex;
}

// Hàm sắp xếp các dòng theo tổng giảm dần
void sortRowsBySum(vector<vector<int>>& matrix) {
    sort(matrix.begin(), matrix.end(), [](const vector<int>& a, const vector<int>& b) {
        return rowSum(a) > rowSum(b); // Sắp xếp giảm dần theo tổng dòng
    });
}

//nhập ma trận
void inputMatrix(vector<vector<int>>& matrix, int m, int n) {
    cout << "Nhap ma tran " << m << "x" << n << ":\n";
    for (int i = 0; i < m; i++) {
        matrix.push_back(vector<int>(n));
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
}

//in ma trận
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
    cout << "Nhap so cot n: ";
    cin >> n;

    vector<vector<int>> matrix;
    inputMatrix(matrix, m, n);

    cout << "\nMa tran da nhap:\n";
    printMatrix(matrix);

    //Tìm dòng có tổng lớn nhất
    int maxRowIndex = findMaxSumRowIndex(matrix);
    cout << "Dong co tong lon nhat: " << maxRowIndex + 1 << " (tong = " << rowSum(matrix[maxRowIndex]) << ")\n";

    //Sắp xếp các dòng theo tổng giảm dần
    sortRowsBySum(matrix);
    cout << "\nMa tran sau khi xep theo tong giam dan:\n";
    printMatrix(matrix);

    return 0;
}
