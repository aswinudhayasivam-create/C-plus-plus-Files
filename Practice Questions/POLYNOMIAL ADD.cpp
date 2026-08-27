#include<iostream>
using namespace std;

class Poly
{

    double a,b,c;
    public:
    Poly(){a=0;b=0;c=0;}

    Poly(double x, double y, double z)
    {
        a=x;
        b=y;
        c=z;

    }
    void display()
    {
        cout<<a<<"x^2 + "<<b<<"x + "<<c<<endl;

    }
    Poly operator + (Poly p)
    {
        Poly temp;
        temp.a = a + p.a;
        temp.b = b + p.b;
        temp.c = c + p.c;
        return temp;
    }
};

int main()

{
    Poly q1(3,4,-2);
    Poly q2(0,-4,10);
    Poly sum ;

    sum = q1+q2;
    
    cout<<"First Polynomial: ";
    q1.display();
    cout<<"Second Polynomial: ";
    q2.display();
    cout<<"Sum: ";
    sum.display();

    return 0;

}