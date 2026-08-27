#include<iostream>
using namespace std;

int main()
{
    try{
        try{
            throw 20;
        }
        catch(int n)
        {
            cout<<"Handle Partially\n";
            throw;
        }
    }
    catch(int n)
    {
        cout<<"Handle Remaining\n";

    }
    return 0;
    
}
