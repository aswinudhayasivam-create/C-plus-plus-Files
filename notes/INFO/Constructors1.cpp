
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    int rollno;
    string name;
    int age;
    char grade;

    
    Student() {}

    
    Student(int r, string n, int a, char g) {
        rollno = r;
        name = n;
        age = a;
        grade = g;
    }

    void displayDetails() {
        cout << "Roll No : " << rollno << endl;
        cout << "Name    : " << name << endl;
        cout << "Age     : " << age << endl;
        cout << "Grade   : " << grade << endl;
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student* s = new Student[n];

   
    for (int i = 0; i < n; i++) {
        int r, a;
        string nm;
        char g;

        cout << "\nEnter student " << i + 1
             << " rollno, name, age and grade:\n";
        cin >> r >> nm >> a >> g;

        s[i] = Student(r, nm, a, g);
    }

    
    cout << "\n--- Student Details ---\n\n";
    for (int i = 0; i < n; i++) {
        s[i].displayDetails();
    }

    delete[] s;
    return 0;
}
