#include<iostream>
using namespace std;

int main()
{
    int a,b,temp;
    int *p,*q;

    cout<<"Enter two values:\n";
    cin>>a>>b;

    cout<<"\nBefore Swapping:\n";
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    p = &a;
    q = &b;

    temp = *p;
    *p   = *q;
    *q   = temp;

    cout<<"\nAfter Swapping:\n";
    cout<<"a = "<<a<<endl;
    cout<<"b = "<<b<<endl;
    return 0;


}