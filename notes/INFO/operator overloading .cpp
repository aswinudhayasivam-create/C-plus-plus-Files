#include<iostream>
using namespace std;

class Complex
{
    public:

    int real,imag;
 
    Complex(int r,int i)
    {
        real = r;
        imag = i;

    }

    Complex operator+(Complex c){
        return Complex(real + c.real , imag + c.imag);

    }

    void display(){

        cout<< real<<" + "<<imag<<" i "<<endl;

    }


};
int main()
{
    Complex c1(2,3),c2(4,5);
    Complex c3 = c1 + c2;
    c3.display();

    return 0;



}