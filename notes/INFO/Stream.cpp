#include<iostream>
using namespace std;

class Number {

    public:
    int n1 ,n2;

    friend void operator>>(istream& mycin,Number& n)

    {
        cout<<"Enter 2 numbers: ";
        mycin>>n.n1>>n.n2;
    }
};

int main(){
    Number nobj;
    cout<<"Enter 2 numbers: ";
    cin>>nobj;
    cout<<"You entered: "<<nobj.n1<<" and "<<nobj.n2<<endl;
    return 0;
    
}