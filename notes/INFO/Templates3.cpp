#include<iostream>
using namespace std;

template <class T, class U, class V = char>
class ClassTemplate{
    T a;
    U b;
    V c;
    public:
    ClassTemplate(T x,U y, V z)
    {
        a = x;
        b = y;
        c = z;

    }

    void printVar()
    {
        cout<<"a: "<<a<<endl;
        cout<<"b: "<<b<<endl;
        cout<<"c: "<<c<<endl;
    }
};

int main()
{
    ClassTemplate<int, double> obj1(7,7.7,'C');
    cout<<"Object 1: "<<endl;
    obj1.printVar();

    ClassTemplate<double,char,bool>obj2(8.8,'A',false);
    cout<<"Object 2: "<<endl;
    obj2.printVar();
    return 0;   
    
}