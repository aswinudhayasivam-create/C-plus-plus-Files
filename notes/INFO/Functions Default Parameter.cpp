#include<iostream>
using namespace std;
void myFunction(string country="India")
{
    cout<<"He is from"<<country<<endl;
    cout<<endl;

}
void myfunction(int a,int b)
{
    int sum = a+b;
    cout<<"Sum is :"<<sum<<endl;

}

int main()
{
    
    myFunction("USA");
    myFunction("UK");
    myFunction();
    myFunction("Canada");

    int a,b;
    cout<<"Enter value for a:\n";
    cin>>a;
    cout<<"Enter value for b:\n";
    cin>>b;

    myfunction(a,b);
   // myfunction(b=20);

    return 0;
}