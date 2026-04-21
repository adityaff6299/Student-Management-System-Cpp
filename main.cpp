#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    float marks;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nMarks: " << marks << endl;
    }
};

// Add student
void addStudent() {
    ofstream file("students.dat", ios::binary | ios::app);
    Student s;
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student added successfully!\n";
}

// Display all students
void displayStudents() {
    ifstream file("students.dat", ios::binary);
    Student s;
    while (file.read((char*)&s, sizeof(s))) {
        s.display();
        cout << "-------------------";
    }
    file.close();
}

// Search student
void searchStudent() {
    ifstream file("students.dat", ios::binary);
    Student s;
    int searchId, found = 0;

    cout << "Enter ID to search: ";
    cin >> searchId;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == searchId) {
            cout << "\nStudent Found:";
            s.display();
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Student not found!\n";

    file.close();
}

// Update student
void updateStudent() {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    Student s;
    int searchId, found = 0;

    cout << "Enter ID to update: ";
    cin >> searchId;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == searchId) {
            cout << "Enter new details:\n";
            s.input();

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Record updated!\n";
            found = 1;
            break;
        }
    }

    if (!found)
        cout << "Student not found!\n";

    file.close();
}

// Delete student
void deleteStudent() {
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    Student s;
    int searchId, found = 0;

    cout << "Enter ID to delete: ";
    cin >> searchId;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != searchId) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = 1;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

// Menu
int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
