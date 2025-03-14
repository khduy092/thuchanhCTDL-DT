#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//Hàm tính tổng các chữ số của một số nguyên
int sumOfDigits(int num) {
    int sum = 0;
    while (num) {
        sum += abs(num % 10);
        num /= 10;
    }
    return sum;
}

//Hàm kiểm tra số nguyên tố
bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

//Tìm vị trí của k phần tử lớn nhất
vector<int> findLargestKIndices(vector<int> arr, int k) {
    vector<pair<int, int>> indexedArr;
    for (int i = 0; i < arr.size(); i++) {
        indexedArr.push_back({arr[i], i});
    }
    sort(indexedArr.rbegin(), indexedArr.rend()); // Sắp xếp giảm dần
    vector<int> indices;
    for (int i = 0; i < k; i++) {
        indices.push_back(indexedArr[i].second);
    }
    return indices;
}

//Sắp xếp theo tổng các chữ số của từng phần tử
void sortByDigitSum(vector<int>& arr) {
    sort(arr.begin(), arr.end(), [](int a, int b) {
        return sumOfDigits(a) < sumOfDigits(b);
    });
}

//Xóa tất cả số nguyên tố trong dãy
void removePrimes(vector<int>& arr) {
    arr.erase(remove_if(arr.begin(), arr.end(), isPrime), arr.end());
}

int main() {
    vector<int> arr = {12, 29, 35, 5, 97, 44, 88, 13};
    int k = 3;
    
    //Tìm vị trí của k phần tử lớn nhất
    vector<int> indices = findLargestKIndices(arr, k);
    cout << "Vi tri cua " << k << " phan tu lon nhat : ";
    for (int idx : indices) cout << idx << " ";
    cout << endl;
    
    //Sắp xếp theo tổng các chữ số
    sortByDigitSum(arr);
    cout << "Day sau khi sap xep theo tong chu so: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    
    //Xóa số nguyên tố
    removePrimes(arr);
    cout << "Day sau khi xoa so nguyen to: ";
    for (int num : arr) cout << num << " ";
    cout << endl;
    
    return 0;
}
