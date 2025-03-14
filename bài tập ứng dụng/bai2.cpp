#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Định nghĩa cấu trúc số hạng của dãy thức bậc n
struct Term {
    double coefficient; // Hệ số
    int degree;         // Bậc (0 ≤ degree ≤ 100)
};

// so sánh để sắp xếp các số hạng theo bậc tăng dần
bool compareTerms(const Term &a, const Term &b) {
    return a.degree < b.degree;
}

// in ra danh sách các số hạng của dãy thức
void printPolynomial(const vector<Term>& polynomial) {
    for (const Term &term : polynomial) {
        cout << term.coefficient << "x^" << term.degree << " ";
    }
    cout << endl;
}

int main() {
    // Khai báo danh sách các số hạng của dãy thức
    vector<Term> polynomial = {
        {3.5, 2}, {1.2, 5}, {4.0, 3}, {2.1, 0}, {5.7, 4}
    };

    cout << "Day thuc truoc khi sap xep: ";
    printPolynomial(polynomial);

    // Sắp xếp theo thứ tự tăng dần của bậc bằng thuật toán quicksort (std::sort)
    sort(polynomial.begin(), polynomial.end(), compareTerms);

    cout << "Day thuc sau khi sap xep: ";
    printPolynomial(polynomial);

    return 0;
}
