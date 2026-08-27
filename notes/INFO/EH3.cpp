#include<iostream>
using namespace std;

void division(int n1 , int n2)
{
    try
    {
    
        if(n2==0)
        throw n2;
        else
        cout<<"n1/n2="<<(float)n1/n2<<endl;
    }
    catch(int )
    {
        cout<<"\nCaught an exception as first throwing "<<endl;
        throw;

    }
    
}

int main()
{
    int a,b;
    cout<<"\nEnter 2 numbers:";
    cin>>a>>b;
    try
    {
        division(a,b);
    }
    catch(int )
    {
        cout<<"\nCaught an exception in main as second throwing "<<endl;
    }
    return 0;

}