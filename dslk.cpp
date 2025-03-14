#include <iostream>
using namespace std;

// Định nghĩa cấu trúc Node
struct Node {
    int info;       // Dữ liệu của node
    Node* next;     // Con trỏ trỏ tới node tiếp theo
};

// Khởi tạo danh sách liên kết
void Init(Node*& pHead) {
    pHead = nullptr;
}

// Tạo một node mới
Node* CreateNode(int X) {
    Node* p = new Node;
    p->info = X;
    p->next = nullptr;
    return p;
}

// Kiểm tra danh sách rỗng
bool IsEmpty(Node* pHead) {
    return (pHead == nullptr);
}

// Thêm một phần tử vào đầu danh sách
void InsertFirst(Node*& pHead, int x) {
    Node* p = CreateNode(x);
    p->next = pHead;
    pHead = p;
}

// Thêm một phần tử sau một node cụ thể
void InsertAfter(Node* p, int x) {
    if (p != nullptr) {
        Node* q = CreateNode(x);
        q->next = p->next; // (1)
        p->next = q;       // (2)
    }
}

// Thêm một phần tử vào danh sách theo thứ tự tăng dần
void InsertOrder(Node*& pHead, int x) {
    Node* tp = nullptr;
    Node* p = pHead;
    bool cont = true;
    while ((p != nullptr) && cont) {
        if (p->info < x) {
            tp = p;
            p = p->next;
        } else {
            cont = false;
        }
    }
    // Xen nút q vào giữa nút p và nút tp
    if (p == pHead) {
        InsertFirst(pHead, x);
    } else {
        InsertAfter(tp, x);
    }
}

// Loại bỏ phần tử đầu tiên của danh sách
void DeleteFirst(Node*& pHead) {
    if (IsEmpty(pHead)) {
        cout << "List is empty!\n";
    } else {
        Node* p = pHead;
        pHead = pHead->next;
        delete p;
    }
}

// Loại bỏ phần tử sau một node cụ thể
void DeleteAfter(Node* p) {
    if (p == nullptr || p->next == nullptr) {
        cout << "Khong the xoa nut nay!\n";
    } else {
        Node* q = p->next;
        p->next = q->next;
        delete q;
    }
}

// Tìm và bỏ x trong danh sách chưa có thứ tự
Node* Remove(Node*& pHead, int x) {
    Node* tp = nullptr;
    Node* p = pHead;
    bool found = false;
    while ((p != nullptr) && !found) {
        if (p->info != x) {
            tp = p;
            p = p->next;
        } else {
            found = true;
        }
    }
    if (found) {
        if (p == pHead) { // Loại bỏ phần tử đầu tiên
            pHead = p->next;
        } else {
            tp->next = p->next;
        }
        delete p;
    }
    return pHead;
}

// Tìm và bỏ x trong danh sách đã có thứ tự
Node* RemoveOrder(Node*& pHead, int x) {
    Node* tp = nullptr;
    Node* p = pHead;
    bool found = false;
    while ((p != nullptr) && !found) {
        if (p->info < x) {
            tp = p;
            p = p->next;
        } else if (p->info == x) {
            found = true;
        } else {
            p = nullptr;
        }
    }
    if (found) {
        if (p == pHead) { // Loại bỏ phần tử đầu tiên
            pHead = p->next;
        } else {
            tp->next = p->next;
        }
        delete p;
    }
    return pHead;
}

// Duyệt danh sách và in ra các phần tử
void ShowList(Node* pHead) {
    Node* p = pHead;
    if (p == nullptr)
        cout << "\n Danh sach rong";
    else {
        while (p != nullptr) {
            cout << p->info << "\t";
            p = p->next;
        }
    }
    cout << endl;
}

// Xóa toàn bộ danh sách
void ClearList(Node*& pHead) {
    Node* p;
    while (pHead != nullptr) {
        p = pHead;
        pHead = pHead->next;
        delete p;
    }
}

// Sắp xếp danh sách tăng dần bằng Selection Sort
void SelectionSort(Node*& pHead) {
    Node *p, *q, *pmin;
    int vmin;
    for (p = pHead; p->next != nullptr; p = p->next) {
        vmin = p->info;
        pmin = p;
        for (q = p->next; q != nullptr; q = q->next) {
            if (q->info < vmin) {
                vmin = q->info;
                pmin = q;
            } // hết if
        } // hết for q
        pmin->info = p->info;
        p->info = vmin;
    } // hết for p
} // hết Sort

//Tìm kiếm tuần tự phần tử có nội dung là x
Node* Find(Node* pHead, int x) {
    bool found = false;
    Node* p = pHead;
    while ((p != nullptr) && (!found)) {
        if (p->info == x)
            found = true;
        else
            p = p->next;
    }
    if (!found)
        p = nullptr;
    return p;
}

//Tìm kiếm phần tử có nội dung là x trong danh sách đã có thứ tự
Node* FindOrder(Node* pHead, int x) {
    bool found = false;
    Node* p = pHead;
    while ((p != nullptr) && (!found)) {
        if (p->info == x)
            found = true;
        else if (p->info < x)
            p = p->next;
        else
            p = nullptr;
    }
    if (!found)
        p = nullptr;
    return p;
}

int main() {
    Node* pHead;
    Init(pHead);

    //Thêm các phần tử vào danh sách
    InsertFirst(pHead, 10);
    InsertFirst(pHead, 5);
    InsertFirst(pHead, 20);
    InsertOrder(pHead, 15);
    InsertOrder(pHead, 25);

    //Hiển thị danh sách
    cout << "Danh sach ban dau: ";
    ShowList(pHead);

    //Tìm kiếm phần tử
    //int x = 15;
    //Node* foundNode = Find(pHead, x);
    //if (foundNode != nullptr) {
     //   cout << "Tim thay phan tu " << x << " trong danh sach.\n";
    //} else {
     //   cout << "Khong tim thay phan tu " << x << " trong danh sach.\n";
   // }

    //Xóa phần tử có giá trị 15 trong danh sách chưa có thứ tự
   // Remove(pHead, 15);
    //cout << "Danh sach sau khi xoa phan tu 15 (Remove): ";
   // ShowList(pHead);

    //Sắp xếp danh sách
    //SelectionSort(pHead);
    //cout << "Danh sach sau khi sap xep: ";
    //ShowList(pHead);

    //Tìm kiếm phần tử trong danh sách đã có thứ tự
    //int x = 20;
    //foundNode = FindOrder(pHead, x);
    //if (foundNode != nullptr) {
      //  cout << "Tim thay phan tu " << x << " trong danh sach da sap xep.\n";
    //} else {
      //  cout << "Khong tim thay phan tu " << x << " trong danh sach da sap xep.\n";
    //}

    //Xóa toàn bộ danh sách
    ClearList(pHead);
    cout << "Danh sach sau khi huy bo: ";
    ShowList(pHead);

    return 0;
}