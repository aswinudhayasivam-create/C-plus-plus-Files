#include <iostream>
using namespace std;

class Complex
{
    float x;
    float y;
    public:
    Complex(){ }
    Complex(float real,float imag)
    {
        x = real; y= imag;}
        Complex operator + (Complex);
        void display (void);
};

Complex Complex :: operator + (Complex C)
{
    Complex temp;
    temp.x = x + C.x;
    temp.y = y + C.y;
    return (temp);

}

void Complex :: display (void){
    cout<<x<<" + j"<<y<<endl;

}
int main()
{
    Complex c1 ,c2 ,c3;
    c1 = Complex(2.5,3.5);
    c2 = Complex(1.6,2.7);
    c3 = c1 + c2;
    cout<<"C1 = ";c1.display();
    cout<<"C2 = ";c2.display();
    cout<<"C3 = ";c3.display();

    return 0;

}