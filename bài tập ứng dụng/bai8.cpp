#include <iostream>
#include <vector>
#include <algorithm>

// Hàm tìm mảng nghịch đảo từ một hoán vị
std::vector<int> findInversionArray(const std::vector<int>& permutation) {
    int n = permutation.size();  // Lấy kích thước của hoán vị
    std::vector<int> inversionArray(n); // Tạo mảng kết quả để lưu mảng nghịch đảo

    // Tạo một mảng lưu vị trí của từng phần tử trong hoán vị
    std::vector<int> position(n + 1);
    for (int i = 0; i < n; i++) {
        position[permutation[i]] = i;  // Lưu vị trí của giá trị permutation[i]
    }

    // Tính toán mảng nghịch đảo
    for (int i = 1; i <= n; i++) { // Lặp qua các giá trị từ 1 đến n
        int pos = position[i];  // Lấy vị trí của số i trong hoán vị
        int count = 0;  // Biến đếm số phần tử lớn hơn i đứng trước i

        // Duyệt qua các phần tử đứng trước vị trí của i
        for (int j = 0; j < pos; j++) {
            if (permutation[j] > i) {  // Nếu phần tử trước đó lớn hơn i
                count++;  
            }
        }

        inversionArray[i - 1] = count;  // Gán giá trị vào mảng nghịch đảo
    }

    return inversionArray;  // Trả về mảng nghịch đảo
}

// Hàm hỗ trợ in ra một vector
void printVector(const std::vector<int>& vec) {
    std::cout << "(";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i];
        if (i < vec.size() - 1) std::cout << ", ";  // In dấu phẩy giữa các phần tử
    }
    std::cout << ")" << std::endl;
}

int main() {
    // Khởi tạo một hoán vị bất kỳ
    std::vector<int> A = {5, 9, 1, 8, 2, 6, 4, 7, 3};

    // Gọi hàm tìm mảng nghịch đảo
    std::vector<int> B = findInversionArray(A);
    
    // In kết quả
    std::cout << "Hoan vi ban dau: ";
    printVector(A);
    std::cout << "Mang nghich dao: ";
    printVector(B);

    return 0;
}
