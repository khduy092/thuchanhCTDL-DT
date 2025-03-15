#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class ListInt {
private:
    Node* head;
    
public:
    // Constructor
    ListInt() {
        head = nullptr;
    }
    
    // Destructor để giải phóng bộ nhớ
    ~ListInt() {
        clear();
    }
    
    // Thêm phần tử vào cuối danh sách
    void append(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = newNode;
            return;
        }
        
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        
        current->next = newNode;
    }
    
    // Thêm phần tử vào đầu danh sách
    void prepend(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }
    
    // Xóa phần tử với giá trị được chỉ định
    bool remove(int value) {
        if (head == nullptr) {
            return false;
        }
        
        // Nếu phần tử cần xóa là đầu danh sách
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        
        // Tìm phần tử cần xóa
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        
        // Nếu tìm thấy
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return true;
        }
        
        return false;
    }
    
    // In danh sách
    void print() {
        Node* current = head;
        
        cout << "Danh sach: ";
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    // Thêm một danh sách khác vào danh sách hiện tại
    void addList(ListInt& otherList) {
        if (otherList.head == nullptr) {
            return;
        }
        
        if (head == nullptr) {
            // Tạo deep copy của danh sách khác
            Node* current = otherList.head;
            while (current != nullptr) {
                append(current->data);
                current = current->next;
            }
            return;
        }
        
        // Đi đến cuối danh sách hiện tại
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        
        // Thêm các phần tử từ danh sách khác
        Node* otherCurrent = otherList.head;
        while (otherCurrent != nullptr) {
            append(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }
    
    // Xóa toàn bộ danh sách
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    ListInt list;
    
    // Nhập 10 số nguyên vào danh sách
    cout << "Nhap 10 so nguyen:" << endl;
    for (int i = 0; i < 10; i++) {
        int num;
        cin >> num;
        list.append(num);
    }
    
    // In danh sách ra màn hình
    list.print();
    
    // Nhập một số k và xóa số k trong danh sách
    int k;
    cout << "Nhap so K can xoa: ";
    cin >> k;
    if (list.remove(k)) {
        cout << "Da xoa so " << k << " tu danh sach." << endl;
    } else {
        cout << "Khong tim thay so " << k << " trong danh sach." << endl;
    }
    
    // In danh sách sau khi xóa phần tử
    cout << "Danh sach sau khi xoa:" << endl;
    list.print();
    
    // Nhập 5 số nguyên vào một danh sách thứ hai
    ListInt secondList;
    cout << "Nhap 5 so nguyen cho danh sach thu hai:" << endl;
    for (int i = 0; i < 5; i++) {
        int num;
        cin >> num;
        secondList.append(num);
    }
    
    // Thêm danh sách thứ hai vào danh sách thứ nhất
    list.addList(secondList);
    
    // In danh sách thứ nhất ra màn hình
    cout << "Danh sach sau khi them danh sach thu hai:" << endl;
    list.print();
    
    return 0;
}