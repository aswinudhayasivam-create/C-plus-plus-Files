#include<iostream>
#include<string>
using namespace std;

struct Employee
{
    int id;
    string name;
    float salary;
    string department;
};

void getDetails(Employee &emp)
{
    cout << "Enter Employee ID: ";
    cin >> emp.id;

    cout << "Enter Employee Name: ";
    cin >> emp.name;

    cout << "Enter Employee Salary: ";
    cin >> emp.salary;

    cout << "Enter Employee Department: ";
    cin >> emp.department;
}
void getNumber(int &num)
{
    cout << "Enter a number of Employees: ";
    cin >> num;
    
}

void printDetails(Employee emp)
{
    cout << "\nEmployee Details:\n";
    cout << "ID         : " << emp.id << "\n";
    cout << "Name       : " << emp.name << "\n";
    cout << "Salary     : " << emp.salary << "\n";
    cout << "Department : " << emp.department << "\n";
}


int compareSalary(Employee emp1, Employee emp2)
{
    if (emp1.salary > emp2.salary)
        return 1;
    else if (emp2.salary > emp1.salary)
        return -1;
    else
        return 0;
}


int main()
{
    Employee emp1, emp2;

    cout << "Enter details for Employee 1:\n";
    getDetails(emp1);       
    cout << "\nEnter details for Employee 2:\n";
    getDetails(emp2);
    

    printDetails(emp1);
    printDetails(emp2);

    int result = compareSalary(emp1, emp2);

    if (result == 1)
        cout << "\n" << emp1.name << " has a higher salary than " << emp2.name << "\n";
    else if (result == -1)
        cout << "\n" << emp2.name << " has a higher salary than " << emp1.name << "\n";
    else
        cout << "\nBoth employees have equal salaries.\n";

    return 0;
}
