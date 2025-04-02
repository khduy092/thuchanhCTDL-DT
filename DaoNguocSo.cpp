#include <iostream>
#include <stack>
#include <cmath>

class NumberReversal {
public:
    // Khu de quy
    static int reverseNumberRecursive(int num) {
        // Truong hop co ban
        if (num < 10) return num;
        
        // Xac dinh chu so
        int digits = countDigits(num);
        int multiplier = std::pow(10, digits - 1);
        
        // dao nguoc so
        return (num % 10) * multiplier + reverseNumberRecursive(num / 10);
    }
    
    // Stack
    static int reverseNumberStack(int num) {
        // Xu ly
        int sign = (num < 0) ? -1 : 1;
        num = std::abs(num);
        
        std::stack<int> digitStack;
        
        // Day so vao stack
        while (num > 0) {
            digitStack.push(num % 10);
            num /= 10;
        }
        
        // Dao nguoc so
        int reversedNum = 0;
        int multiplier = 1;
        
        while (!digitStack.empty()) {
            reversedNum += digitStack.top() * multiplier;
            digitStack.pop();
            multiplier *= 10;
        }
        
        return sign * reversedNum;
    }
    
    // Dem chu so
    static int countDigits(int n) {
        int count = 0;
        while (n > 0) {
            count++;
            n /= 10;
        }
        return count;
    }
    
    // Thuc hien
    static void demonstrateNumberReversal() {
        int testNumbers[] = {12345, 7890, 1000, 54321};
        
        std::cout << "Dao nguoc so bang de quy:\n";
        for (int num : testNumbers) {
            std::cout << num << " -> " << reverseNumberRecursive(num) << std::endl;
        }
        
        std::cout << "\nDao nguoc so bang Stack:\n";
        for (int num : testNumbers) {
            std::cout << num << " -> " << reverseNumberStack(num) << std::endl;
        }
    }
};

int main() {
    NumberReversal::demonstrateNumberReversal();
    
    return 0;
}