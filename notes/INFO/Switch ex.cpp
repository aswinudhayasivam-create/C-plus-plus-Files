#include<iostream>
using namespace std;
int main()
{
    int a,b,ch;
    cout<<"Enter Two values:\n";
    cin>>a>>b;
    cout<<"\nChoose the operation to be performed:\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n";
    cout<<"\nEnter your choice (1-4)\n";
    cin>>ch;

    switch(ch)
    {
        case 1:
        cout<<"\nAddition :"<<a+b<<"\n";
        break;  
        case 2:
        cout<<"\nSubtraction :"<<a-b<<"\n";
        break;      
        case 3:
        cout<<"\nMultiplication :"<<a*b<<"\n";
        break;
        case 4:
        cout<<"\nDivision :"<<a/b<<"\n";
        break;
        default:
        cout<<"\nInvalid Choice\n";

    }
    return 0;
}