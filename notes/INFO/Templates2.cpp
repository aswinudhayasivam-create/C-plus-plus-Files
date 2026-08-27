#include<iostream>
using namespace std;

template <class T>
class Number{
    T val;
    public:
    Number(T v) : val(v) {}
    T getval() {
        return val;
    }
};

int main(){
    Number<int> n1(10);
    Number<double> n2(3.14);
    Number<char> n3('A');

    cout<<"Integer value: "<<n1.getval()<<endl;
    cout<<"Double value: "<<n2.getval()<<endl;
    cout<<"Character value: "<<n3.getval()<<endl;

    return 0;
}