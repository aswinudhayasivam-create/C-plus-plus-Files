#include<iostream>
#include<string>
using namespace std;

struct student{
    int rollno;
    string name;
    int age;
    char grade;
};
int main()
{
    int n,i;
    cout<<"Enter number of students:\n";
    cin>>n;
    student s[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Enter student "<<i+1<<" rollno,name,age and grade:\n";
        cin>>s[i].rollno>>s[i].name>>s[i].age>>s[i].grade;

    }
    cout<<"\nStudent Details: \n"<<endl;
    for(int i=0;i<n;i++)
    {

        
        cout<<"Roll No: "<<s[i].rollno<<endl;
        cout<<"Name: "<<s[i].name<<endl;
        cout<<"Age: "<<s[i].age<<endl;
        cout<<"Grade: "<<s[i].grade<<endl;
        cout<<endl;
    }
    return 0;

}