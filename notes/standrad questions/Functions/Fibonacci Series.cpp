#include<iostream>
using namespace std;
int fib(int n)
{
   /* if(n<=1)
    {
        return n;
    }
    else{
        return fib(n-1) + fib(n-2);

    }
    }*/
   int a=0,b=1,c;
    
   cout<<"Fibonacci Series:"<<a<<" "<<b<<" ";
   for(int i=2;i<n;i++)
   {
    c = a + b;
    cout<<c<<" ";
    a = b;
    b = c;
   }
}

int main()
{
    int n;
    cout<<"Enter number of terms in Fibonacci Series:\n";
    cin>>n;
    fib(n);
    return 0;

}