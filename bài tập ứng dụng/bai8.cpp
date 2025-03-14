#include <iostream>
#include <vector>
using namespace std;

// Hàm tìm mảng nghịch thế
vector<int> findInverseArray(const vector<int>& A) {
    int N = A.size();
    vector<int> B(N, 0);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (A[j] > A[i]) {
                B[i]++;
            }
        }
    }
    
    return B;
}


// IN
void printVector(const vector<int>& vec) {
    cout << "(";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;
}

int main() {

    vector<int> A = {5, 9, 1, 8, 2, 6, 4, 7, 3};
    
    cout << "Mang A: ";
    printVector(A);
    
    // Tinh toan mang nghich the
    vector<int> B = findInverseArray(A);
    cout << "Mang nghich the B: ";
    printVector(B);
    
    
    return 0;
}