#include<iostream>
using namespace std;

int main()
{
    int choice;

    cout<<"Enter choice : ";
    cin>>choice;

    try {
        if (choice == 1)
        throw 100;

        else if (choice == 2)
        throw 10.5;

        else if (choice == 3)
        throw 'A';

        else
        cout<<"No exception thrown."<<endl; 

    }
    catch(int x)
    {
        cout<<"Caught an integer exception: "<<x<<endl;
    }
    catch(double y)
    {
        cout<<"Caught a double exception: "<<y<<endl;
    }
    catch(char z)
    {
        cout<<"Caught a character exception: "<<z<<endl;
    }

    return 0;

}