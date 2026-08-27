#include<iostream>
using namespace std;

int main(){
    int n1,n2;
    float res;
    char ch;
    while(true)
    {
        cout<<"\nEnter 2 numbers:";
        cin>>n1>>n2;

        try{ 
            if(n2==0)
            throw 0;
            res = static_cast<float>(n1)/n2;
            cout<<"res="<<res;
            cout<<"\nDo you want to continue??(y/n)";
            cin>>ch;

            if(ch!='y')
            break;
        }
        catch(int exp)
        {
            cout<<"Error: cannot divide by zero!!";

        }
        
    }
}