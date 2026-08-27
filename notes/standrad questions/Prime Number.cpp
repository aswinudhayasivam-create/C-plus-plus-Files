#include<iostream>
using namespace std;

int main()
{
    int n,i,flag=0;
    cout<<"Enter a number:";
    cin>>n;

    for(i=2; i <=n/2 ;i++)
{
    if(n%i==0)
    {
        flag=1;
        break;
    }
}

if(flag==0 && n>1)
{
    cout<<"Prime number\n";
}
else
{
  cout<<"Not a prime number\n";  
}
return 0;


}