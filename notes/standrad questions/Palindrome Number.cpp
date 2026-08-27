#include<iostream>
using namespace std;
int main()
{
    int n, rev = 0;
    cout<<"Enter the numbers:";
    cin>>n;

    int temp = n;
    while(n>0)
    {
        rev = rev *10 + (n%10);
        n=n/10;
    }
   
    if (temp == rev)
    {
        cout<<"Palindrome Number\n";
    }
    else
    {
        cout<<"Not a Palindrome Number\n";
    }
    
    return 0;
}  
