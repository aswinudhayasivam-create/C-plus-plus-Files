#include<iostream>
using namespace std;

class Swap {
private:
    int a;
    int b;

public:
    void set(int x, int y)
    {
        a = x;
        b = y;
    }

    void display()
    {
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;
    }

    friend void swapValues(Swap &s);
};

void swapValues(Swap &s)
{
    int temp = s.a;
    s.a = s.b;
    s.b = temp;
}

int main()
{
    int x, y;
    Swap s;

    cout << "Enter values of x & y: ";
    cin >> x >> y;

    s.set(x, y);

    cout << "\nBefore Swap:" << endl;
    s.display();

    swapValues(s);

    cout << "\nAfter Swap:" << endl;
    s.display();

    return 0;
}