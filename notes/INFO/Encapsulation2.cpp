#include<iostream>
#include<string>
using namespace std;

class STUDENT{
private:
    int roll;
    string name;
    char grade;

public:
    void setDetails(int r, string n, char g){
        roll = r;
        name = n;
        grade = g;
    }

    int getRoll(){
        return roll;
    }

    string getName(){
        return name;
    }

    char getGrade(){
        return grade;
    }
};

int main(){
    int x;
    cout << "Enter the number of students: ";
    cin >> x;

    STUDENT s[x];   // array of objects

    for(int i = 0; i < x; i++){
        int r;
        char g;
        string n;

        cout << "\nStudent " << i+1 << endl;
        cout << "Enter roll number: ";
        cin >> r;

        cout << "Enter name: ";
        cin >> n;

        cout << "Enter grade: ";
        cin >> g;

        s[i].setDetails(r, n, g);
    }

    cout << "\n Student Details \n";
    for(int i = 0; i < x; i++){
        cout << "\nStudent " << i+1 << endl;
        cout << "Roll  : " << s[i].getRoll() << endl;
        cout << "Name  : " << s[i].getName() << endl;
        cout << "Grade : " << s[i].getGrade() << endl;
    }

    return 0;
}
