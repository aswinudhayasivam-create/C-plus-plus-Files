#include<iostream>
using namespace std;

template <class X>
void mySwap(X &a, X &b){
    X temp;
    temp = a;
    a = b;
    b = temp;
}

int main(){
    int a = 10, b = 20;
    double x = 1.5, y = 2.5;
    char c1 = 'A', c2 = 'B';

    cout<<"Before swapping : "<<a<<" "<<b<<endl;
    mySwap(a,b);
    cout<<"After swapping : "<<a<<" "<<b<<endl;

    cout<<"Before swapping : "<<x<<" "<<y<<endl;
    mySwap(x,y);
    cout<<"After swapping : "<<x<<" "<<y<<endl;

    cout<<"Before swapping : "<<c1<<" "<<c2<<endl;
    mySwap(c1,c2);
    cout<<"After swapping : "<<c1<<" "<<c2<<endl;

    return 0;
}