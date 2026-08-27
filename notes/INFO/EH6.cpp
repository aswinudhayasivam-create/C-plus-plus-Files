#include<iostream>
using namespace std;

int main()
{
    int a,b,c;

    cout<<"Enter two numbers: "<<endl;
    cin>>a>>b;

    try
    {
        if(b == 0)
        {
        throw b;   
        }
        c= a/b;
        cout<<"Result: "<<c<<endl;
    }
    catch(int x)
    {
        cout<<"Error: Division by zero is not allowed. You entered: "<<x<<endl;
    }
    
    return 0;
    
}