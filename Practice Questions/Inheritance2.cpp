#include<iostream>
using namespace std;

class X
{
    public:

    string x[5];

  
    void getData()
    {
        cout<<"Enter 5 strings: "<<endl;
        for(int i=0;i<5;i++)
        {
            cin>>x[i];
        }
    }


};

class Y :public X{

    public:
    string y[5];

   
    void getData()
    {
        X::getData();
        cout<<"Enter 5 more strings: "<<endl;
        for(int i=0;i<5;i++)
        {
            cin>>y[i];
        }
    }

};

class Z : public Y{
    public:
    string z[5 ];

   
    void getData()
    {
        Y::getData();
        cout<<"Enter 5 more strings: "<<endl;
        for(int i=0;i<5;i++)
        {
            cin>>z[i];
        }
    }

    void printData()
    {
        cout<<"Strings in class X: "<<endl;
        for(int i=0;i<5;i++)
        {
            cout<<x[i]<<endl;
        }
        cout<<"Strings in class Y: "<<endl;
        for(int i=0;i<5;i++)
        {
            cout<<y[i]<<endl;
        }
        cout<<"Strings in class Z: "<<endl;
        for(int i=0;i<5;i++)
        {
            cout<<z[i]<<endl;
        }
    }
};

int main()
{
    Z z1;
    z1.getData();
    z1.printData();
    return 0;
}