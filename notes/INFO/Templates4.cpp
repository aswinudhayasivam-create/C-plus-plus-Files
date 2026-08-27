#include<iostream>
using namespace std;

template < typename T>
void swapNum(T &a,T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;

}

int main()
{
    int x=10,y=20;
    cout<<"Before swapping: "<<x<<" "<<y<<endl;
    swapNum(x,y);
    cout<<"After swapping: "<<x<<" "<<y<<endl;

    double a=1.5,b=2.5;
    cout<<"Before swapping: "<<a<<" "<<b<<endl;
    swapNum(a,b);
    cout<<"After swapping: "<<a<<" "<<b<<endl;

    return 0;
    
}