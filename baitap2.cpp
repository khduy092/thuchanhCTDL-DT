#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

struct SinhVien {
    string hoTen;      
    string diaChi;     
    string lop;        
    int khoa;          
    SinhVien* next;    
};

class ListSV {
private:
    SinhVien* head;
    
public:
    // Constructor
    ListSV() {
        head = NULL;
    }
    
    // Destructor
    ~ListSV() {
        SinhVien* current = head;
        while (current != NULL) {
            SinhVien* temp = current;
            current = current->next;
            delete temp;
        }
    }
    
    // Them sinh vien vao list
    void themSinhVien(string hoTen, string diaChi, string lop, int khoa) {
        SinhVien* newStudent = new SinhVien;
        newStudent->hoTen = hoTen;
        newStudent->diaChi = diaChi;
        newStudent->lop = lop;
        newStudent->khoa = khoa;
        newStudent->next = NULL;
        
        if (head == NULL) {
            head = newStudent;
        } else {
            SinhVien* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newStudent;
        }
        
        cout << "Them sinh vien thanh cong!" << endl;
    }
    
    // Xoa sinh vien
    bool xoaTheoTen(string hoTen) {
        if (head == NULL)
            return false;
        
        if (head->hoTen == hoTen) {
            SinhVien* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        
        SinhVien* current = head;
        while (current->next != NULL && current->next->hoTen != hoTen) {
            current = current->next;
        }
        
        if (current->next == NULL)
            return false;
        
        SinhVien* temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }
    
    // Xoa sinh vien theo dia chi
    bool xoaTheoDiaChi(string diaChi) {
        if (head == NULL)
            return false;
        
        if (head->diaChi == diaChi) {
            SinhVien* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        
        SinhVien* current = head;
        while (current->next != NULL && current->next->diaChi != diaChi) {
            current = current->next;
        }
        
        if (current->next == NULL)
            return false;
        
        SinhVien* temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }
    
    // In sinh vien theo list
    void inDanhSach() {
        if (head == NULL) {
            cout << "Danh sach sinh vien!" << endl;
            return;
        }
        cout << "\n====== Danh sach sinh vien ======" << endl;
        cout << left << setw(30) << "Ho Ten" << setw(40) << "Dia chi" << setw(15) << "Lop" << "Khoa" << endl;
        cout << string(100, '-') << endl;
        
        SinhVien* current = head;
        while (current != NULL) {
            cout << left << setw(30) << current->hoTen 
                 << setw(40) << current->diaChi 
                 << setw(15) << current->lop 
                 << current->khoa << endl;
            current = current->next;
        }
        cout << string(100, '-') << endl;
    }
    
    // Selection Sort
    void sapXepTheoTen() {
        if (head == NULL || head->next == NULL)
            return;
        
        SinhVien* current = head;
        while (current != NULL) {
            SinhVien* min = current;
            SinhVien* r = current->next;
            
            while (r != NULL) {
                if (r->hoTen < min->hoTen)
                    min = r;
                r = r->next;
            }
            
            //Doi vi tri du lieu
            if (min != current) {
                swap(current->hoTen, min->hoTen);
                swap(current->diaChi, min->diaChi);
                swap(current->lop, min->lop);
                swap(current->khoa, min->khoa);
            }
            
            current = current->next;
        }
        
        cout << "Danh sach duoc sap xep!" << endl;
    }
};

int main() {
    ListSV studentList;
    int choice;
    
    // Them 10 sinh vien vao danh sach
    studentList.themSinhVien("Nguyen Van A", "123 Street, City", "CSE01", 2023);
    studentList.themSinhVien("Le Thi H", "456 Avenue, Town", "IT02", 2022);
    studentList.themSinhVien("Tran Van C", "789 Road, Village", "CSE03", 2023);
    studentList.themSinhVien("Pham Thi D", "101 Boulevard, District", "IT01", 2024);
    studentList.themSinhVien("Nguyen Van Teo", "202 Lane, Province", "CSE02", 2022);
    studentList.themSinhVien("Hoang Van E", "303 Path, County", "IT03", 2021);
    studentList.themSinhVien("Vu Thi F", "404 Nguyen Van Cu", "CSE01", 2024);
    studentList.themSinhVien("Do Van G", "505 Highway, Region", "IT02", 2023);
    studentList.themSinhVien("Nguyen Van", "606 Avenue, Country", "CSE03", 2022);
    studentList.themSinhVien("Tran Van B", "707 Street, Town", "IT01", 2021);
    
    // In danh sach ban dau
    cout << "\n=== Danh Sach ban dau ===" << endl;
    studentList.inDanhSach();
    
    // Xoa sinh vien "Nguyen Van Teo"
    cout << "\n=== Xoa sinh vien 'Nguyen Van Teo' ===" << endl;
    if (studentList.xoaTheoTen("Nguyen Van Teo"))
        cout << "Sinh vien 'Nguyen Van Teo' Duoc xoa thanh cong!" << endl;
    else
        cout << "Sinh vien 'Nguyen Van Teo' khong duoc tim thay!" << endl;
    studentList.inDanhSach();
    
    // Xoa dia chi "Nguyen Van Cu"
    cout << "\n=== Xoa sinh vien dia chi 'Nguyen Van Cu' ===" << endl;
    if (studentList.xoaTheoDiaChi("404 Nguyen Van Cu"))
        cout << "Sinh vien voi dia chi '404 Nguyen Van Cu' xoa thanh cong!" << endl;
    else
        cout << "Sinh vien voi dia chi '404 Nguyen Van Cu' khong duoc tim thay!" << endl;
    studentList.inDanhSach();
    
    // Them sinh vien "Tran Thi Mo" voi dia chi "25 Hong Bang", Lop "TT0901", Khoa 2009
    cout << "\n=== Them sinh vien 'Tran Thi Mo' ===" << endl;
    studentList.themSinhVien("Tran Thi Mo", "25 Hong Bang", "TT0901", 2009);
    studentList.inDanhSach();
    
    // Sap xep theo ten va In
    cout << "\n=== Danh sach sap xep theo ten (Selection Sort) ===" << endl;
    studentList.sapXepTheoTen();
    studentList.inDanhSach();
    
    return 0;
}