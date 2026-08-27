#include<iostream>
using namespace std;
int main()
{
    int n,a=0,b=1,c;
    int  sum = 0;
    
    cout<<"Enter the number of terms ";
    cin>>n;
    cout<<"\nFibonacci Series:\n";

    cout << a << " " << b << " ";
    if (n >= 1)
        sum = a;     

    if (n >= 2)
        sum = a + b;

    for(int i=3;i<=n;i++)
    {
        c=a+b;
        cout<<c<<" ";
        sum+=c;
        a=b;
        b=c;
    }
   
   
    cout<<"\n\nSum of the Digits is "<<sum<<"\n";

    return 0;

}