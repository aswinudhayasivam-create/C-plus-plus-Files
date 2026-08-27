#include<iostream>
using namespace std;

int main()
{
    int age;

    cout<<"enter ur age :"<<endl;
    cin>>age;

    try
    {
        if(age<18)
        {
            throw age;
        } 
        cout<<"Your age is: "<<age<<", you are eligible to vote"<<endl;

    }
    catch(int x)
    {
        cout<<"Error: Age must be at least 18 to vote. You entered: "<<x<<endl;
    }

    return 0;

    
}