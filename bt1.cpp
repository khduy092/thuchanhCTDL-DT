#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

// Stack sử dụng mảng
class StackInt {
private:
    static const int MAX = 100;
    int arr[MAX];
    int top;
public:
    StackInt() { top = -1; }
    bool IsEmpty() { return top == -1; }
    bool IsFull() { return top == MAX - 1; }
    void PushStack(int x) { if (!IsFull()) arr[++top] = x; }
    int PopStack() { return IsEmpty() ? -1 : arr[top--]; }
    int PeekStack() { return IsEmpty() ? -1 : arr[top]; }
    void Clear() { top = -1; }
};

// Stack sử dụng danh sách liên kết
struct Node {
    int data;
    Node* next;
};

class LinkedStackInt {
private:
    Node* top;
public:
    LinkedStackInt() { top = nullptr; }
    bool IsEmpty() { return top == nullptr; }
    void PushStack(int x) {
        Node* temp = new Node{x, top};
        top = temp;
    }
    int PopStack() {
        if (IsEmpty()) return -1;
        int value = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return value;
    }
    int PeekStack() { return IsEmpty() ? -1 : top->data; }
    void Clear() {
        while (!IsEmpty()) PopStack();
    }
};

// Đảo số
int ReverseNumber(int num) {
    stack<int> s;
    while (num > 0) {
        s.push(num % 10);
        num /= 10;
    }
    int reversed = 0, place = 1;
    while (!s.empty()) {
        reversed += s.top() * place;
        s.pop();
        place *= 10;
    }
    return reversed;
}

// Kiểm tra xâu đối xứng
bool IsPalindrome(string str) {
    stack<char> s;
    for (char ch : str) s.push(ch);
    for (char ch : str) {
        if (ch != s.top()) return false;
        s.pop();
    }
    return true;
}

// Chuyển số thập phân sang nhị phân
string DecimalToBinary(int num) {
    stack<int> s;
    while (num > 0) {
        s.push(num % 2);
        num /= 2;
    }
    string binary = "";
    while (!s.empty()) {
        binary += to_string(s.top());
        s.pop();
    }
    return binary;
}

// Chuyển biểu thức sang hậu tố
int Precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string InfixToPostfix(string expr) {
    stack<char> s;
    string postfix = "";
    for (char ch : expr) {
        if (isdigit(ch)) postfix += ch;
        else if (ch == '(') s.push(ch);
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        }
        else {
            while (!s.empty() && Precedence(s.top()) >= Precedence(ch)) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

// Tính giá trị biểu thức hậu tố
int EvaluatePostfix(string postfix) {
    stack<int> s;
    for (char ch : postfix) {
        if (isdigit(ch)) s.push(ch - '0');
        else {
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            switch (ch) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }
    return s.top();
}

int main() {
    cout << "Dao so 12345: " << ReverseNumber(12345) << endl;
    cout << "Kiem tra xau 'radar': " << (IsPalindrome("radar") ? "Doi xung" : "Khong doi xung") << endl;
    cout << "Chuyen 25 sang nhi phan: " << DecimalToBinary(25) << endl;
    string expr = "3+(2*5)-8/4";
    string postfix = InfixToPostfix(expr);
    cout << "Hau to cua " << expr << " la: " << postfix << endl;
    cout << "Gia tri bieu thuc: " << EvaluatePostfix(postfix) << endl;
    return 0;
}
