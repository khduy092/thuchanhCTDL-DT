#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// QueueInt dung mang
class QueueInt {
private:
    int* data;
    int front;
    int rear;
    int capacity;
    int size;

public:
    // Tao hang doi
    QueueInt(int cap = 100) {
        capacity = cap;
        data = new int[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    ~QueueInt() {
        delete[] data;
    }

    // Kiem tra hang doi rong
    bool IsEmpty() {
        return size == 0;
    }

    // Kiem tra hang doi day
    bool IsFull() {
        return size == capacity;
    }

    // Them gia tri vao hang doi
    void Enqueue(int value) {
        if (IsFull()) {
            cout << "Hang doi dang day!" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
    }

    // Xoa gia tri trong hang doi
    int Dequeue() {
        if (IsEmpty()) {
            cout << "Hang doi dang rong!" << endl;
            return -1;
        }
        int value = data[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }

    // Lay gia tri dau tien trong hang doi
    int Peek() {
        if (IsEmpty()) {
            cout << "Hang doi dang rong!" << endl;
            return -1;
        }
        return data[front];
    }

    // Lam sach hang doi
    void Clear() {
        front = 0;
        rear = -1;
        size = 0;
    }

    // Hien cac gia tri trong Hang doi
    void Display() {
        if (IsEmpty()) {
            cout << "Hang doi dang rong!" << endl;
            return;
        }
        cout << "Gia tri trong hang doi: ";
        int count = 0;
        int i = front;
        while (count < size) {
            cout << data[i] << " ";
            i = (i + 1) % capacity;
            count++;
        }
        cout << endl;
    }
};

// Node cho LinkedQueueInt
struct Node {
    int data;
    Node* next;
    
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// LinkedQueueInt su dung linked list
class LinkedQueueInt {
private:
    Node* frontNode;
    Node* rearNode;
    int size;

public:
    // Tao hang doi
    LinkedQueueInt() {
        frontNode = nullptr;
        rearNode = nullptr;
        size = 0;
    }

    ~LinkedQueueInt() {
        Clear();
    }

    // Kiem tra hang doi rong
    bool IsEmpty() {
        return frontNode == nullptr;
    }

    // kiem tra hang doi day
    bool IsFull() {
        return false;
    }

    // Them gia tri vao hang doi
    void Enqueue(int value) {
        Node* newNode = new Node(value);
        if (IsEmpty()) {
            frontNode = newNode;
            rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        size++;
    }

    // Xoa gia tri tu hang doi
    int Dequeue() {
        if (IsEmpty()) {
            cout << "Hang doi dang rong!" << endl;
            return -1;
        }
        Node* temp = frontNode;
        int value = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            rearNode = nullptr;
        }
        delete temp;
        size--;
        return value;
    }

    // Lay gia tri dau tien cua hang doi
    int Peek() {
        if (IsEmpty()) {
            cout << "Hang doi dang rong!" << endl;
            return -1;
        }
        return frontNode->data;
    }

    // Don hang doi
    void Clear() {
        while (!IsEmpty()) {
            Dequeue();
        }
    }

    // Hien hang doi
    void Display() {
        if (IsEmpty()) {
            cout << "Hang doi dang rong!" << endl;
            return;
        }
        cout << "Gia tri trong hang doi: ";
        Node* current = frontNode;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};


// RadixSort
void radixSort(vector<int>& arr) {
    // Tim gia tri lon nhat
    int max = *max_element(arr.begin(), arr.end());
    
    // Sap xep cho tung gia tri
    for (int exp = 1; max / exp > 0; exp *= 10) {
        QueueInt buckets[10];
        
        // Dat cac gia tri
        for (int i = 0; i < arr.size(); i++) {
            int digit = (arr[i] / exp) % 10;
            buckets[digit].Enqueue(arr[i]);
        }
        
        // Lay cac gia tri
        int index = 0;
        for (int i = 0; i < 10; i++) {
            while (!buckets[i].IsEmpty()) {
                arr[index++] = buckets[i].Dequeue();
            }
        }
    }
}

// RadixSort
void testRadixSort() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};
    
    cout << "Mang ban dau: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    radixSort(arr);
    cout << "Mang sau sap xep: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    cout << "QueueInt :" << endl;
    QueueInt q;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    q.Display();
    cout << "Bo mot gia tri cua hang doi : " << q.Dequeue() << endl;
    q.Display();
    cout << "Gia tri dau tien hang doi : " << q.Peek() << endl;
    cout << endl;
    
    cout << "LinkedQueueInt :" << endl;
    LinkedQueueInt lq;
    lq.Enqueue(100);
    lq.Enqueue(200);
    lq.Enqueue(300);
    lq.Display();
    cout << "Bo mot gia tri cua hang doi : " << lq.Dequeue() << endl;
    lq.Display();
    cout << "Gia tri dau tien hang doi : " << lq.Peek() << endl;
    cout << endl;
    

    cout << "RadixSort:" << endl;
    testRadixSort();
    
    return 0;
}