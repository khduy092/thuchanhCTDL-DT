#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;


struct Student {
    int id;                
    string fullName;        
    string firstName;       
    int birthDay, birthMonth, birthYear; 
    string gender;          
    float gpa;
};


void inputStudents(vector<Student>& students);
bool validateStudent(const Student& student, const vector<Student>& students);
void saveToFile(const vector<Student>& students, const string& filename);
void createIndexFiles(const vector<Student>& students);
void displayStudentsByIndex(const string& dataFile, const string& indexFile);
void displayStudent(const Student& student);

int main() {
    vector<Student> students;
    
    // Nhập thông tin sinh viên và lưu thành file
    inputStudents(students);
    saveToFile(students, "SINHVIEN.DAT");
    
    // Tạo cái file index
    createIndexFiles(students);
    
    // Hiện các sinh viên theo file index
    cout << "\n-- Danh sach sinh vien sap xep theo Ma sinh viên tang dan --\n";
    displayStudentsByIndex("SINHVIEN.DAT", "SVMASO.IDX");
    
    cout << "\n-- Danh sach sinh vien sap xep theo ten sinh vien (A → Z) --\n";
    displayStudentsByIndex("SINHVIEN.DAT", "SVTEN.IDX");
    
    cout << "\n-- Danh sach sinh vien sap xep theo Diem trung bình giam dan --\n";
    displayStudentsByIndex("SINHVIEN.DAT", "SVDTB.IDX");
    
    return 0;
}

void inputStudents(vector<Student>& students) {
    cout << "Nhap thong tin sinh vien (Toi thieu 10 sinh vien):\n";
    
    int count = 0;
    while (count < 10 || (count >= 10 && getchar() == 'y')) {
        Student student;
        
        cout << "\nSinh vien #" << count + 1 << ":\n";
        
        cout << "Ma so: ";
        cin >> student.id;
        
        cin.ignore();
        cout << "Ho va dem (Toi da 40 ky tu): ";
        getline(cin, student.fullName);
        
        cout << "Ten sinh vien (Toi da 20 ky tu): ";
        getline(cin, student.firstName);
        
        cout << "Ngay sinh: ";
        cin >> student.birthDay;
        
        cout << "Thang sinh: ";
        cin >> student.birthMonth;
        
        cout << "Nam sinh: ";
        cin >> student.birthYear;
        
        cin.ignore();
        cout << "Phai (Nam/Nu): ";
        getline(cin, student.gender);
        
        cout << "Diem GPA (0.00 den 10.00): ";
        cin >> student.gpa;
        
        if (validateStudent(student, students)) {
            students.push_back(student);
            count++;
            
            if (count >= 10) {
                cout << "\nDa dat so luong yeu cau. Ban co muon tiep tuc? (y/n): ";
                cin.ignore();
            }
        } else {
            cout << "Thong tin khong hop le. Vui lòng nhập lại.\n";
        }
    }
    
    cout << "Da nhap " << students.size() << " sinh vien.\n";
}

bool validateStudent(const Student& student, const vector<Student>& students) {
    // Kiểm tra ID
    if (student.id <= 0) {
        cout << "Loi: Ma sinh vien phai nguyen dong.\n";
        return false;
    }
    
    for (const auto& s : students) {
        if (s.id == student.id) {
            cout << "Loi: Ma sinh vien da ton tai .\n";
            return false;
        }
    }
    
    // Kiểm tra họ và đệm
    if (student.fullName.length() > 40) {
        cout << "Loi: Ho va dem khong duoc dai qua 40 ky tu.\n";
        return false;
    }
    
    if (student.firstName.length() > 20) {
        cout << "Loi: Ten khong duoc dai qua 20 ky tu.\n";
        return false;
    }

    // Kiểm tra ngày tháng năm
    if (student.birthDay < 1 || student.birthDay > 31 || 
        student.birthMonth < 1 || student.birthMonth > 12 ||
        student.birthYear < 1900 || student.birthYear > 2024) {
        cout << "Loi: Ngay thang nam sinh khong hop le.\n";
        return false;
    }
    
    // Kiểm tra giới tính
    if (student.gender != "Nam" && student.gender != "Nu") {
        cout << "Loi: Gioi tinh  \"Nam\" hoac \"Nu\".\n";
        return false;
    }
    
    // Kiểm tra GPA
    if (student.gpa < 0.0 || student.gpa > 10.0) {
        cout << "Loi: Diem trung binh phai tu  0.00 den 10.00.\n";
        return false;
    }
    
    return true;
}

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename, ios::binary);
    
    if (!outFile) {
        cerr << "Khong the mo tep " << filename << " de ghi.\n";
        return;
    }
    
    // Ghi số lượng sinh viên
    int size = students.size();
    outFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
    
    // Ghi từng dữ liệu sinh viên
    for (const auto& student : students) {
        // ID
        outFile.write(reinterpret_cast<const char*>(&student.id), sizeof(student.id));
        
        // Họ và Lót
        int fullNameLength = student.fullName.length();
        outFile.write(reinterpret_cast<const char*>(&fullNameLength), sizeof(fullNameLength));
        outFile.write(student.fullName.c_str(), fullNameLength);
        
        // Tên
        int firstNameLength = student.firstName.length();
        outFile.write(reinterpret_cast<const char*>(&firstNameLength), sizeof(firstNameLength));
        outFile.write(student.firstName.c_str(), firstNameLength);
        
        // Ngày tháng năm
        outFile.write(reinterpret_cast<const char*>(&student.birthDay), sizeof(student.birthDay));
        outFile.write(reinterpret_cast<const char*>(&student.birthMonth), sizeof(student.birthMonth));
        outFile.write(reinterpret_cast<const char*>(&student.birthYear), sizeof(student.birthYear));
        
        // Giới tính
        int genderLength = student.gender.length();
        outFile.write(reinterpret_cast<const char*>(&genderLength), sizeof(genderLength));
        outFile.write(student.gender.c_str(), genderLength);
        
        // GPA
        outFile.write(reinterpret_cast<const char*>(&student.gpa), sizeof(student.gpa));
    }
    
    outFile.close();
    cout << "Da luu du lieu vao tep " << filename << " thanh cong.\n";
}

void createIndexFiles(const vector<Student>& students) {
    // Tạo dữ liệu cho các kiểu sắp xếp
    vector<Student> studentsById = students;
    vector<Student> studentsByName = students;
    vector<Student> studentsByGPA = students;
    
    // ID tăng dần
    sort(studentsById.begin(), studentsById.end(), 
         [](const Student& a, const Student& b) { return a.id < b.id; });
    
    // Sắp xếp (A -> Z)
    sort(studentsByName.begin(), studentsByName.end(), 
         [](const Student& a, const Student& b) {
             if (a.firstName == b.firstName) {
                 return a.fullName < b.fullName;
             }
             return a.firstName < b.firstName;
         });
    
    // GPA tăng dần
    sort(studentsByGPA.begin(), studentsByGPA.end(), 
         [](const Student& a, const Student& b) { return a.gpa > b.gpa; });
    
    // SVMASO.IDX 
    ofstream idxById("SVMASO.IDX");
    for (const auto& student : studentsById) {
        idxById << student.id << endl;
    }
    idxById.close();
    
    // SVTEN.IDX 
    ofstream idxByName("SVTEN.IDX");
    for (const auto& student : studentsByName) {
        idxByName << student.id << endl;
    }
    idxByName.close();
    
    // SVDTB.IDX 
    ofstream idxByGPA("SVDTB.IDX");
    for (const auto& student : studentsByGPA) {
        idxByGPA << student.id << endl;
    }
    idxByGPA.close();
    
    cout << "Da tao cac tep chi muc thanh cong.\n";
}

void displayStudentsByIndex(const string& dataFile, const string& indexFile) {
    vector<int> indices;
    vector<Student> students;
    
    // Đọc file
    ifstream idxFile(indexFile);
    if (!idxFile) {
        cerr << "Khong the mo tep chi dinh " << indexFile << ".\n";
        return;
    }
    
    int studentId;
    while (idxFile >> studentId) {
        indices.push_back(studentId);
    }
    idxFile.close();
    
    // Đọc file
    ifstream dataInputStream(dataFile, ios::binary);
    if (!dataInputStream) {
        cerr << "Khong the mo tep chi dinh " << dataFile << ".\n";
        return;
    }
    
    // Số lượng sinh viên
    int size;
    dataInputStream.read(reinterpret_cast<char*>(&size), sizeof(size));
    
    // Tất cả sinh viên
    for (int i = 0; i < size; i++) {
        Student student;
        
        // ID
        dataInputStream.read(reinterpret_cast<char*>(&student.id), sizeof(student.id));
        
        // Họ Lót
        int fullNameLength;
        dataInputStream.read(reinterpret_cast<char*>(&fullNameLength), sizeof(fullNameLength));
        char* fullNameBuffer = new char[fullNameLength + 1];
        dataInputStream.read(fullNameBuffer, fullNameLength);
        fullNameBuffer[fullNameLength] = '\0';
        student.fullName = fullNameBuffer;
        delete[] fullNameBuffer;
        
        // Tên
        int firstNameLength;
        dataInputStream.read(reinterpret_cast<char*>(&firstNameLength), sizeof(firstNameLength));
        char* firstNameBuffer = new char[firstNameLength + 1];
        dataInputStream.read(firstNameBuffer, firstNameLength);
        firstNameBuffer[firstNameLength] = '\0';
        student.firstName = firstNameBuffer;
        delete[] firstNameBuffer;
        
        // Ngày tháng năm
        dataInputStream.read(reinterpret_cast<char*>(&student.birthDay), sizeof(student.birthDay));
        dataInputStream.read(reinterpret_cast<char*>(&student.birthMonth), sizeof(student.birthMonth));
        dataInputStream.read(reinterpret_cast<char*>(&student.birthYear), sizeof(student.birthYear));
        
        // Giới tính
        int genderLength;
        dataInputStream.read(reinterpret_cast<char*>(&genderLength), sizeof(genderLength));
        char* genderBuffer = new char[genderLength + 1];
        dataInputStream.read(genderBuffer, genderLength);
        genderBuffer[genderLength] = '\0';
        student.gender = genderBuffer;
        delete[] genderBuffer;
        
        // GPA
        dataInputStream.read(reinterpret_cast<char*>(&student.gpa), sizeof(student.gpa));
        
        students.push_back(student);
    }
    
    dataInputStream.close();
    
    // Hiện sinh viên theo các cách sắp xếp
    cout << left << setw(10) << "Ma so" 
         << setw(22) << "Ho va Dem" 
         << setw(42) << "Ten" 
         << setw(15) << "Ngay sinh" 
         << setw(6) << "Phai" 
         << "Diem TB" << endl;
    cout << string(105, '-') << endl;
    
    for (int id : indices) {
        for (const auto& student : students) {
            if (student.id == id) {
                displayStudent(student);
                break;
            }
        }
    }
}

void displayStudent(const Student& student) {
    cout << left << setw(10) << student.id
         << setw(22) << student.fullName
         << setw(42) << student.firstName
         << right << setw(2) << student.birthDay << "/" 
         << setw(2) << setfill('0') << student.birthMonth << "/" 
         << setw(4) << student.birthYear << setfill(' ') << "   "
         << left << setw(6) << student.gender
         << fixed << setprecision(2) << student.gpa << endl;
}