#include <iostream>
#include <vector>
#include <stack>

class FibonacciSolver {
public:
    // De quy fibonacci
    static int fibonacciRecursive(int n) {
        if (n <= 1) return n;
        
        return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
    }
    
    // Trien khai fibonacci dựa vào Stack
    static int fibonacciStack(int n) {
        if (n <= 1) return n;
        
        // Sử dụng biến thay vì ngăn xếp đầy đủ để tăng hiệu quả
        int a = 0, b = 1, temp;
        for (int i = 2; i <= n; ++i) {
            temp = a + b;
            a = b;
            b = temp;
        }
        
        return b;
    }
    
    static void demonstrateFibonacci() {
        std::cout << "De quy fibonacci: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << fibonacciRecursive(i) << " ";
        }
        
        std::cout << "\n\nStack fibonacci: ";
        for (int i = 0; i < 10; ++i) {
            std::cout << fibonacciStack(i) << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    FibonacciSolver::demonstrateFibonacci();
    
    return 0;
}