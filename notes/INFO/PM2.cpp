#include<iostream>
using namespace std;

class A
{
    public:
    void show()
    {
        cout<<"Class A"<<endl;

    }
};

class B : public A{
    public:
    void show()
    {
        cout<<"Class B"<<endl;

    }
};

int main()
{
    A *ptr;
    B b;
    ptr = &b;
    ptr->show();
    return 0 ;
    
}