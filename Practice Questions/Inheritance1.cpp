#include<iostream>
using namespace std;

class Employee
{

    public:

    string name;
    float salary;

    void getData()
    {
        cout<<"Enter name of employee: ";
        cin>>name;
        cout<<"Enter salary of employee: ";
        cin>>salary;
    }

};

class Manager : public Employee{
    public:
    string department;

    void getData()
    {
        Employee::getData();
        cout<<"Enter department of manager: ";
        cin>>department;    
    }

    void displayManager()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Salary: "<<salary<<endl;
        cout<<"Department: "<<department<<endl;
    }

};

class Executive : public Employee{
    public:

    void displayExecutive()
    {
        cout<<"Executive \n"<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Salary: "<<salary<<endl;
        

    }


};

int main()
{
    Executive e1;
    e1.getData();
    e1.displayExecutive();

    Manager m1;
    m1.getData();
    m1.displayManager();
    return 0;
}