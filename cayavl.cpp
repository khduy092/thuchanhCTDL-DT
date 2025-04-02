#include <iostream>
#include <algorithm>  // Cho std::max
using namespace std;

// Định nghĩa một nút trong cây AVL
class Node {
public:
    int value;
    Node* left;
    Node* right;
    int height;

    Node(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
};

// Lớp AVLTree cài đặt cây AVL
class AVLTree {
public:
    Node* root;

    AVLTree() : root(nullptr) {}

    // Hàm tính chiều cao của cây
    int height(Node* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    // Hàm tính độ cân bằng của cây
    int getBalance(Node* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    // Xoay cây sang trái
    Node* rotateLeft(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;

        // Thực hiện xoay
        y->left = z;
        z->right = T2;

        // Cập nhật chiều cao
        z->height = max(height(z->left), height(z->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        // Trả về nút mới
        return y;
    }

    // Xoay cây sang phải
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Thực hiện xoay
        x->right = y;
        y->left = T2;

        // Cập nhật chiều cao
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        // Trả về nút mới
        return x;
    }

    // Chèn một giá trị vào cây
    Node* insert(Node* node, int value) {
        // 1. Thực hiện chèn giống như trong cây nhị phân tìm kiếm
        if (node == nullptr)
            return new Node(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        else  // Tránh trùng lặp giá trị
            return node;

        // 2. Cập nhật chiều cao của nút hiện tại
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. Kiểm tra độ cân bằng của nút hiện tại và thực hiện xoay nếu cần
        int balance = getBalance(node);

        // Nếu cây mất cân bằng, có 4 trường hợp

        // Trường hợp Left-Left (Xoay phải)
        if (balance > 1 && value < node->left->value)
            return rotateRight(node);

        // Trường hợp Right-Right (Xoay trái)
        if (balance < -1 && value > node->right->value)
            return rotateLeft(node);

        // Trường hợp Left-Right (Xoay trái rồi phải)
        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Trường hợp Right-Left (Xoay phải rồi trái)
        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        // Trả về con trỏ của cây đã được cân bằng
        return node;
    }

    // Hàm chèn giá trị vào cây AVL
    void insert(int value) {
        root = insert(root, value);
    }

    // Hàm tìm kiếm một giá trị trong cây
    Node* search(Node* node, int value) {
        if (node == nullptr || node->value == value)
            return node;

        if (value < node->value)
            return search(node->left, value);

        return search(node->right, value);
    }

    // Hàm tìm kiếm giá trị trong cây AVL
    bool search(int value) {
        Node* result = search(root, value);
        return result != nullptr;
    }

    // Hàm tìm node có giá trị nhỏ nhất (dùng trong việc xóa node)
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    // Hàm xóa một giá trị khỏi cây
    Node* deleteNode(Node* root, int value) {
        // 1. Thực hiện xóa như trong cây nhị phân tìm kiếm
        if (root == nullptr)
            return root;

        if (value < root->value)
            root->left = deleteNode(root->left, value);
        else if (value > root->value)
            root->right = deleteNode(root->right, value);
        else {
            // Nút cần xóa là nút hiện tại
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            // Nếu nút có hai con, lấy nút có giá trị nhỏ nhất ở cây con phải
            Node* temp = minValueNode(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
        }

        // 2. Cập nhật chiều cao của nút hiện tại
        root->height = 1 + max(height(root->left), height(root->right));

        // 3. Kiểm tra độ cân bằng và xoay nếu cần
        int balance = getBalance(root);

        // Trường hợp Left-Left (Xoay phải)
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Trường hợp Right-Right (Xoay trái)
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Trường hợp Left-Right (Xoay trái rồi phải)
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Trường hợp Right-Left (Xoay phải rồi trái)
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // Hàm xóa giá trị khỏi cây AVL
    void deleteNode(int value) {
        root = deleteNode(root, value);
    }

    // Hàm duyệt cây theo thứ tự inorder
    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->value << " ";
            inorder(node->right);
        }
    }

    // Hàm in cây theo thứ tự inorder
    void inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree tree;

    // Chèn các giá trị vào cây AVL
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);

    cout << "Cay AVL sau khi chuyen sang thu tu inorder: ";
    tree.inorder();  // In cây theo thứ tự inorder

    // Tìm kiếm giá trị trong cây
    cout << "Tim kiem 15: " << (tree.search(15) ? "Co" : "Khong co") << endl;
    cout << "Tim kiem 100: " << (tree.search(100) ? "Co" : "Khong co") << endl;

    // Xóa một giá trị khỏi cây
    tree.deleteNode(20);
    cout << "Cay AVL sau khi xoa 20: ";
    tree.inorder();

    return 0;
}
