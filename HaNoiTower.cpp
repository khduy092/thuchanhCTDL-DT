#include <iostream>
#include <stack>
#include <tuple>

class TowerOfHanoi {
public:
    // De quy thap Ha Noi
    static void hanoidRecursive(int n, char source, char auxiliary, char destination) {
        
        if (n == 1) {
            std::cout << "Di chuyen dia tu " << source << " den " << destination << std::endl;
            return;
        }
        
        // Di chuyen dia (n - 1)
        hanoidRecursive(n-1, source, destination, auxiliary);
        
        // Di chuyen n dia
        std::cout << "Di chuyen dia " << n << " tu " << source << " den " << destination << std::endl;
        
        // Di chuyen (n - 1) dia den dich
        hanoidRecursive(n-1, auxiliary, source, destination);
    }
    
    // Thap Ha Noi Stack
    static void hanoidStack(int n) {
        // Tao ngan xep
        std::stack<std::tuple<int, char, char, char>> callStack;
        
        // Day trang thai ban dau
        callStack.push(std::make_tuple(n, '1', '2', '3'));
        
        while (!callStack.empty()) {
            int numDisks = std::get<0>(callStack.top());
            char source = std::get<1>(callStack.top());
            char auxiliary = std::get<2>(callStack.top());
            char destination = std::get<3>(callStack.top());
            callStack.pop();
            
            if (numDisks == 1) {
                std::cout << "Di chuyen dia tu " << source << " den " << destination << std::endl;
            }
            else {
                // Day cac hoat dong theo huong nguoc lai
                
                // di chuyen (n - 1) dia tu dich den phu
                callStack.push(std::make_tuple(numDisks-1, auxiliary, source, destination));
                
                // Di chuyen n dia tu nguon den dich
                callStack.push(std::make_tuple(1, source, auxiliary, destination));
                
                // DI chuyen (n - 1) dia tu nguon den dich
                callStack.push(std::make_tuple(numDisks-1, source, destination, auxiliary));
            }
        }
    }
    
    static void demonstrateTowerOfHanoi() {
        std::cout << "De quy thap Ha Noi (3 dia):\n";
        hanoidRecursive(3, '1', '2', '3');
        
        std::cout << "\nStack thap Ha Noi (3 stack):\n";
        hanoidStack(3);
    }
};

int main() {
    
    std::cout << "\n\nThap Ha Noi:\n";
    TowerOfHanoi::demonstrateTowerOfHanoi();
    
    return 0;
}