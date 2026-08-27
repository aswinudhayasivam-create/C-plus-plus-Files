#include<iostream>

using namespace std;

class Rational{
    int numerator;
    int denominator;

    int gcd(int a, int b)
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    } 

    void reduce(){
        int divisor = gcd(numerator, denominator);
        denominator = denominator / divisor;

        if(denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
    public:
    Rational (int num = 0,int den = 1)
    {
        numerator = num;

        if(den == 0){
            denominator = 1;
        }
        else {
            denominator = den;
        }
        reduce();
    }

    Rational add(Rational r)
    {
        int num = (numerator * r.denominator) + (r.numerator * denominator);
        int den = denominator * r.denominator;
        return Rational(num,den);

    }

    Rational subtract(Rational r)
    {
        int num = (numerator * r.denominator) - (r.numerator * denominator);
        int den = denominator * r.denominator;
        return Rational(num,den);

    }

    Rational multiply(Rational r)
    {
        int num = numerator * r.numerator;
        int den = denominator * r.denominator;
        return Rational(num,den);

    }

    Rational divide(Rational r)
    {
        int num = numerator * r.denominator;
        int den = denominator * r.numerator;
        return Rational(num,den);

    }
    void display() {
        cout<<numerator<<"/"<<denominator<<endl;
    }
};

int main()
{
    Rational r1(2, 7);
    Rational r2(3, 5);

    cout<<"R1: ";
    r1.display();
    cout<<"R2: ";
    r2.display();

    Rational sum = r1.add(r2);
    Rational diff = r1.subtract(r2);
    Rational prod = r1.multiply(r2);    
    Rational quot = r1.divide(r2);

    cout<<"Sum: ";
    sum.display();
    cout<<"Difference: ";
    diff.display();
    cout<<"Product: ";
    prod.display();
    cout<<"Quotient: ";
    quot.display();

}
