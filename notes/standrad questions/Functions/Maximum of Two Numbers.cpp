#include<iostream>
using namespace std;

int max(int a,int b)
{
    if(a>b)
    {
        cout<<a<<" is Maximun Number "<<endl;
        return a;

    }
    else if (b>a)
    {
        cout<<b<<" is Maximun Number "<<endl;
        return b;

    }
    else if(a==b)
    {
        cout<<"Both are Equal Numbers "<<endl;
        return a;
    }
    else{
        cout<<b<<" is Minimun Number "<<endl;
        return b;
         
    }
}
    int main()
    {
        int x,y;
        cout<< "Enter two numbers :\n";
        cin>>x>>y;
        max(x,y);
        return 0;

    }
