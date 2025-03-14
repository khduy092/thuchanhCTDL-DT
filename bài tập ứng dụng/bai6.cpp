#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> sortEvenOdd(const std::vector<int>& arr) {
    // Xác định vị trí số 0
    std::vector<int> zeroPositions;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 0) {
            zeroPositions.push_back(i);
        }
    }
    
    // Tách các số chẵn, số lẻ
    std::vector<int> evenNums;
    std::vector<int> oddNums;
    
    for (int num : arr) {
        if (num != 0 && num % 2 == 0) {
            evenNums.push_back(num);
        } else if (num % 2 != 0) {
            oddNums.push_back(num);
        }
    }
    
    // Sắp xếp mảng số chẵn
    std::sort(evenNums.begin(), evenNums.end());
    
    // Sắp xếp mảng số lẻ
    std::sort(oddNums.begin(), oddNums.end(), std::greater<int>());
    
    // Mảng sau khi sắp xếp
    std::vector<int> result(arr.size());
    int evenIndex = 0;
    int oddIndex = 0;
    
    for (int i = 0; i < arr.size(); i++) {
        if (std::find(zeroPositions.begin(), zeroPositions.end(), i) != zeroPositions.end()) {
            //Giữ 0 ở vị trí của nó
            result[i] = 0;
        } else if (arr[i] % 2 == 0) {
            //Đặt số chẵn đã sắp xếp
            result[i] = evenNums[evenIndex++];
        } else {
            //Đặt số lẻ đã sắp xếp
            result[i] = oddNums[oddIndex++];
        }
    }
    
    return result;
}

int main() {
    int n;
    std::cout << "So luong phan tu trong mang: ";
    std::cin >> n;
    
    std::vector<int> arr(n);
    std::cout << "Enter " << n << " Nhap cac phan tu cua mang cach nhau boi dau cach: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    std::cout << "Mang ban dau: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::vector<int> sortedArr = sortEvenOdd(arr);
    
    std::cout << "Mang sau khi sap xep: ";
    for (int num : sortedArr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    return 0;
}