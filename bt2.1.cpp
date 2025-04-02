#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

// =================== CẤU TRÚC HÀNG ĐỢI DÙNG MẢNG ===================
#define MAX 100

class QueueInt {
private:
    int arr[MAX];
    int front, rear;
public:
    QueueInt() { front = rear = -1; }

    bool isEmpty() { return front == -1; }
    bool isFull() { return rear == MAX - 1; }

    void enqueue(int x) {
        if (isFull()) { cout << "Queue is full\n"; return; }
        if (front == -1) front = 0;
        arr[++rear] = x;
    }

    int dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return -1; }
        int data = arr[front];
        if (front >= rear) front = rear = -1;
        else front++;
        return data;
    }

    void display() {
        if (isEmpty()) { cout << "Queue is empty\n"; return; }
        for (int i = front; i <= rear; i++) cout << arr[i] << " ";
        cout << endl;
    }
};

// =================== CẤU TRÚC HÀNG ĐỢI DÙNG DANH SÁCH LIÊN KẾT ===================
struct Node {
    int data;
    Node* next;
};

class LinkedQueueInt {
private:
    Node* front;
    Node* rear;
public:
    LinkedQueueInt() { front = rear = nullptr; }

    bool isEmpty() { return front == nullptr; }

    void enqueue(int x) {
        Node* temp = new Node();
        temp->data = x;
        temp->next = nullptr;
        if (rear == nullptr) { front = rear = temp; return; }
        rear->next = temp;
        rear = temp;
    }

    int dequeue() {
        if (isEmpty()) { cout << "Queue is empty\n"; return -1; }
        int data = front->data;
        Node* temp = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
        return data;
    }

    void display() {
        if (isEmpty()) { cout << "Queue is empty\n"; return; }
        Node* temp = front;
        while (temp) { cout << temp->data << " "; temp = temp->next; }
        cout << endl;
    }
};

// CẤU TRÚC HÀNG ĐỢI DÙNG CHO CẶP MÚA 
struct Dancer {
    char Name[100];
    char Sex[10];
};

void FormLines(queue<Dancer> &male, queue<Dancer> &female) {
    Dancer d;
    const char *dancers[] = {"F Trang", "M Truc", "M Thien", "M Bao", "F Thu", "M Tien", "F Thuy", "M Nghia", "F Thao", "M Phuoc", "M Hung", "F Vy"};
    int n = 12;
    for (int i = 0; i < n; i++) {
        strncpy(d.Sex, dancers[i], 1);
        d.Sex[1] = '\0';
        strcpy(d.Name, dancers[i] + 2);
        if (strcmp(d.Sex, "M") == 0) {
            male.push(d);
        } else {
            female.push(d);
        }
    }
}

void StartDancing(queue<Dancer> &male, queue<Dancer> &female) {
    printf("Cac cap dien vien:\n");
    while (!male.empty() && !female.empty()) {
        Dancer m = male.front(); male.pop();
        Dancer w = female.front(); female.pop();
        printf("%s\t%s\n", m.Name, w.Name);
    }
}

// HÀM RADIX SORT 
int getMax(int arr[], int n) {
    int maxVal = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxVal)
            maxVal = arr[i];
    return maxVal;
}

void radixSort(int arr[], int n) {
    queue<int> bucket[10]; // 10 buckets for digits 0-9
    int maxVal = getMax(arr, n);
    int exp = 1; // 1, 10, 100, ...

    while (maxVal / exp > 0) {
        for (int i = 0; i < n; i++) {
            int digit = (arr[i] / exp) % 10;
            bucket[digit].push(arr[i]);
        }

        int index = 0;
        for (int i = 0; i < 10; i++) {
            while (!bucket[i].empty()) {
                arr[index++] = bucket[i].front();
                bucket[i].pop();
            }
        }
        exp *= 10; // Move to next digit
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    //  1. Kiểm thử QueueInt (hàng đợi dùng mảng) 
    cout << "QueueInt Test:\n";
    QueueInt q1;
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    q1.display();
    cout << "Dequeued: " << q1.dequeue() << endl;
    q1.display();
    cout << "\n";

    // 2. Kiểm thử LinkedQueueInt (hàng đợi dùng danh sách liên kết) 
    cout << "LinkedQueueInt Test:\n";
    LinkedQueueInt q2;
    q2.enqueue(40);
    q2.enqueue(50);
    q2.enqueue(60);
    q2.display();
    cout << "Dequeued: " << q2.dequeue() << endl;
    q2.display();
    cout << "\n";

    // === 3. Ứng dụng hàng đợi để xếp cặp múa 
    queue<Dancer> males, females;
    FormLines(males, females);
    cout << "Danh sach dien vien nam:\n";
    StartDancing(males, females);
    cout << "\n";

    // === 4. Ứng dụng hàng đợi trong Radix Sort ===
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Mang ban dau: ";
    printArray(arr, n);

    radixSort(arr, n);

    cout << "Mang sau khi sap xep: ";
    printArray(arr, n);

    return 0;
}
