#include<iostream>
using namespace std;
int main()
{
    int n,fact = 1;
    cout<<"Enter numdr to find factorial:";
    cin>>n;
    for(int i =1 ;i<=n;i++)
    {
        fact *= i;
    }
    cout<<"factorial of "<<n<<" is "<<fact<<"\n";
    return 0;

}