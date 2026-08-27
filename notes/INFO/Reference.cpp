#include <iostream>
using namespace std;

int main()
{
    int a = 10;
    int &ref = a;   // ref is a reference to a

    cout << "a = " << a << endl;
    cout << "ref = " << ref << endl;

    ref = 20;   // changing ref changes a

    cout << "After change:" << endl;
    cout << "a = " << a << endl;
    cout << "ref = " << ref << endl;

     int x = 5;
    int &y = x;

    cout << "Address of x: " << &x << endl;
    cout << "Address of y: " << &y << endl;

     cout << "Value  of x: " << x << endl;
    cout << "Value of y: " << y << endl;

    
    return 0;
}
