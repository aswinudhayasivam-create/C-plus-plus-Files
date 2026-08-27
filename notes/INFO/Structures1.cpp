#include<iostream>
#include<string>
using namespace std;

struct student{
    string name;
    int age;
    char grade;
};
int main()
{
    student s1;
    cout<<"Enter student name,age and grade:\n";
    cin>>s1.name>>s1.age>>s1.grade;
    cout<<"\nStudent Details:\n";
    cout<<"Name :"<<s1.name<<endl;
    cout<<"Age  :"<<s1.age<<endl;
    cout<<"Grade:"<<s1.grade<<endl;
    return 0;
}