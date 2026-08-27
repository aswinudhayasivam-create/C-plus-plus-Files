#include<iostream>
using namespace std;
int main()
{
    int n ,sum=0,temp;
    cout<<"Enter the digits:";
    cin>>n;
    temp=n;

    for(;n>0;n=n/10)
    {
        int digit = n%10;
        sum = sum + digit * digit * digit;
    }
    
    if(temp==sum)
    {
        cout<<"Armstrong Number\n";
    }
    else{
        cout<<"Not an Armstrong Number\n";
    }
    
    return 0;

}
