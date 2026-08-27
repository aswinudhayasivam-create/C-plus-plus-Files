#include<iostream>
using namespace std;

class Parent{
    protected:
    int age = 50;
    string name = "John Doe";

    Parent(){
        cout<<"Some Content in parent class:";
        
    }

    void displayParent(){
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
    }

};

class Child: public Parent{
    public:
    void displayChild(){
        cout<<name<<endl;
        cout<<age<<endl;
        cout<<"Some content in child class"<<endl;
    }

};

int main(){
    Child c;
    c.displayChild();
    return 0;   
}