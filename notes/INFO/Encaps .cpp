#include<iostream>
using namespace std;

class Student{
    private:
    int roll;
    string name;

    public:

    Student(int r ,string n){
        roll = r;
        name = n;

    }

    void display(){
        cout<<"Roll : "<<roll<<endl;
        cout<<"Name : "<<name<<endl;

    }
};

int main(){
    Student s1(101,"john");
    Student s2(102,"doe");
    cout<<"Student 1 : "<<endl;
    s1.display();
    cout<<"\nStudent 2 : "<<endl;
    s2.display();
}