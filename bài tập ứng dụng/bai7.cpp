#include <iostream>
#include <vector>

void evenOddPartition(std::vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    // Hai con trỏ để phân vùng mảng
    while (left < right) {
        // Tìm số lẻ ngoài cùng bên trái
        while (left < right && arr[left] % 2 == 0) {
            left++;
        }
        
        // Tìm số chẵn ngoài cùng bên phải
        while (left < right && arr[right] % 2 == 1) {
            right--;
        }
        
        // Đổi vị trí số chẵn và số lẻ
        if (left < right) {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
}

// Hàm in 
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    int n;
    std::cout << "So luong phan tu trong mang: ";
    std::cin >> n;
    
    std::vector<int> arr(n);
    std::cout << "Enter " << n << " phan tu cach nhau boi dau cach: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    std::cout << "Mang ban dau: ";
    printArray(arr);
    
    evenOddPartition(arr);
    
    std::cout << "Mang sau khi sap xep: ";
    printArray(arr);
    
    return 0;
}