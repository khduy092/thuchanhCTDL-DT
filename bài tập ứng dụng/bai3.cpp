#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct PhongThi {
    int soPhong;
    char nha;
    int khaNangChua;
};

// Hàm nhập danh sách phòng thi
void nhapDanhSach(vector<PhongThi> &ds, int n) {
    for (int i = 0; i < n; i++) {
        PhongThi p;
        cout << "Nhap so phong, nha, kha nang chua: ";
        cin >> p.soPhong >> p.nha >> p.khaNangChua;
        ds.push_back(p);
    }
}

// Hàm in danh sách phòng thi
void inDanhSach(const vector<PhongThi> &ds) {
    for (const auto &p : ds) {
        cout << "So phong: " << p.soPhong << ", Nha: " << p.nha << ", Kha nang chua: " << p.khaNangChua << endl;
    }
    cout << "-------------------------" << endl;
}

// Sắp xếp giảm dần theo Khả năng chứa
bool cmpKhaNangChua(const PhongThi &a, const PhongThi &b) {
    return a.khaNangChua > b.khaNangChua;
}

// Sắp xếp tăng dần theo Nhà, nếu cùng Nhà thì tăng dần theo Số phòng
bool cmpNhaSoPhong(const PhongThi &a, const PhongThi &b) {
    if (a.nha == b.nha)
        return a.soPhong < b.soPhong;
    return a.nha < b.nha;
}

// Sắp xếp tăng dần theo Nhà, nếu cùng Nhà thì giảm dần theo Khả năng chứa
bool cmpNhaKhaNangChua(const PhongThi &a, const PhongThi &b) {
    if (a.nha == b.nha)
        return a.khaNangChua > b.khaNangChua;
    return a.nha < b.nha;
}

int main() {
    int n;
    cout << "Nhap so luong phong thi: ";
    cin >> n;

    vector<PhongThi> danhSach;
    nhapDanhSach(danhSach, n);

    // Sắp xếp giảm dần theo Khả năng chứa
    sort(danhSach.begin(), danhSach.end(), cmpKhaNangChua);
    cout << "Danh sach phong thi theo kha nang chua giam dan:" << endl;
    inDanhSach(danhSach);

    // Sắp xếp tăng dần theo Nhà, cùng Nhà thì tăng dần theo Số phòng
    sort(danhSach.begin(), danhSach.end(), cmpNhaSoPhong);
    cout << "Danh sach phong thi theo nha (A-Z) va so phong tang dan:" << endl;
    inDanhSach(danhSach);

    // Sắp xếp tăng dần theo Nhà, cùng Nhà thì giảm dần theo Khả năng chứa
    sort(danhSach.begin(), danhSach.end(), cmpNhaKhaNangChua);
    cout << "Danh sach phong thi theo nha (A-Z) va kha nang chua giam dan:" << endl;
    inDanhSach(danhSach);

    return 0;
}
