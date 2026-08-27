#include<iostream>
using namespace std;
int main()
{
    int n,sum=0;
    cout<<"Enter the digits:";
    cin>>n;
    for(;n>0;n=n/10)
    {
        int digit = n%10;
        sum = sum + digit;
    }
    cout<<"Sum of the Digits is "<<sum<<"\n";
    return 0;

}