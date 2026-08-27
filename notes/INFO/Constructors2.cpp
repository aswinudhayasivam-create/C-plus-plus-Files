#include<iostream>
#include<string>
using namespace std;

class Employee{
    public:
    int id;
    string name;
    double salary;
    string department;

    void getDetails();
    void displayDetails();

    Employee(){
        cout<<"\nWork Hard!!\n";
    }


};

void Employee::getDetails(){
   cin.ignore();

   cout<<"Enter Name:";
   getline(cin,name);
    
   cout<<"Enter department:";
   
   getline(cin,department);
   
   cout<<"Enter ID:";
   cin>>id;

   cout<<"Enter Salary:";
   cin>>salary;

   

}           
void Employee::displayDetails() {

    cout<<"ID        :"<<id<<endl;
    cout<<"Name      :"<<name<<endl;
    cout<<"Salary    :"<<salary<<endl;
    cout<<"Department:"<<department<<endl;

}  

int main() 
{
    int n;
    cout<<"Enter number of Employees:";
    cin>>n;

    Employee* EMP = new Employee[n];

    cout<<"\nEnter Employee Details\n";
    for(int i=0;i<n;i++){
    cout<<"\nEmployee "<<i+1<<":"<<endl;
    EMP[i].getDetails();
    }
   cout<<"\nEmployee Details\n";
    for(int i=0;i<n;i++){
    cout<<"\nEmployee "<<i+1<<":"<<endl;
    EMP[i].displayDetails(); 

}

delete[] EMP;
return 0;


}