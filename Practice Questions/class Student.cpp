#include<iostream>
using namespace std;

class Student{
    public:
    int roll[5];
    string name[5];

    void display () {
        cout<<"\n Students Details:\n ";
        for(int i=0;i<5;i++){
        cout<<"Student:"<<i+1<<endl;
        cout<<"Roll: "<<roll[i]<<endl;
        cout<<"Name:"<<name[i]<<endl;
        }


    }
};

int main(){
    Student s;


    for(int i=0;i<5;i++){

    cout << "\nEnter details for student " << i + 1 << endl;
    cout<<"Enter sutdent Name:";
    cin>>s.name[i];
    cout<<"Enter the roll no :";
    cin>>s.roll[i];}
   s.display();
   return 0;

}