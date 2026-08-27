#include<iostream>
using namespace std;

class Three
{
    int a,b,c;
    public:
    Three(int x,int y,int z)
    {
        a=x;
        b=y;
        c=z;
}
void display()
{
    cout<<"The three numbers are: "<<a<<" "<<b<<" "<<c<<endl;
}

friend void big(Three t);
friend void mean(Three t);

};

void big(Three t)
{
    if(t.a>t.b && t.a>t.c)
    {
        cout<<"The biggest number is: "<<t.a<<endl;
    }
    else if(t.b>t.a && t.b>t.c)
    {
        cout<<"The biggest number is: "<<t.b<<endl;
    }
    else
    {
        cout<<"The biggest number is: "<<t.c<<endl;
    }

}

void mean(Three t)
{
    float mean = (t.a + t.b + t.c) / 3.0;
    cout<<"The mean of the three numbers is: "<<mean<<endl;
}

int main()
{
    int x,y,z;
    cout<<"Enter three numbers: ";
    cin>>x>>y>>z;

    Three t(x,y,z);
    t.display();
    big(t);
    mean(t);

    return 0;
}