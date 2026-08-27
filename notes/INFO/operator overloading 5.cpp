#include<iostream>
using namespace std;
class Number 
{
    int x;
    public:
    Number (){}
    Number(int a)
    {
        x = a;

    }
    Number operator+(Number n)
    {           
        Number newNumber;
        newNumber.x = x + n.x;
        return newNumber;
    }
void display()
    {
        cout << x;
    }
};

int main()
{
    Number a(5),b(10);
    Number c = a + b;
    c.display();


    return 0;

}