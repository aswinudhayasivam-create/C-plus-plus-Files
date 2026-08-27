#include<iostream>
using namespace std;
int reverse(int n)
{
    int rev =0;
    while (n>0)
    {
        rev = rev*10 + n%10;
        n = n/10;
    }
    return rev;
}
int palindrome(int n)
{
    int rev = reverse(n);
    if(rev==n)
    {
        cout<<endl<<n<<" is Palindrome Number "<<endl;

    }
    else{
        cout<<endl<<n<<" is Not a Palindrome Number "<<endl;

    }
    return rev;
}
int sum(int n)
{
    int s=0;
    while(n>0)
    {
        s = s + n%10;
        n = n/10;

    }
    return s;
}
int Armstrong(int n)
{
    int sum=0,temp;
    temp=n;

    for(;n>0;n=n/10)
    {
        int digit = n%10;
        sum = sum + digit * digit * digit;
    }
    
    if(temp==sum)
    {
        cout<<n<<" is Armstrong Number\n";
    }
    else{
        cout<<n<<" is Not an Armstrong Number\n";
    }
    return sum;
}
int factorial(int n)
{
    int fact = 1;
    for(int i =1 ;i<=n;i++)
    {
        fact *= i;
    }
    cout<<"factorial of "<<n<<" is "<<fact<<"\n";
    return fact;
}
int main()
{
    int n;
    cout<<"Enter digits:";
    cin>>n;
    cout<<"\nReversed digits:"<<reverse(n)<<endl;
    palindrome(n);
    cout<<endl;
    cout<<"Sum of digits:"<<sum(n)<<endl;
    Armstrong(n);
    factorial(n);

    return 0;

}