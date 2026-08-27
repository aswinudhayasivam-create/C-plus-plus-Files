//unary operator overloading
#include<iostream>
using namespace std;

class Space
{
    int x;
    int y;
    int z;
    public:
    void getdata(int a,int b,int c);
    void display(void);
    void operator -();

};

void Space :: getdata (int a,int b, int c)
{
    x = a;
    y = b;
    z = c;
}
void Space :: display(void)
{
    cout<<"X = "<<x<<" ";
    cout<<"Y = "<<y<<" ";
    cout<<"Z = "<<z<<" \n";

}
void Space :: operator-()
{
    x = -x;
    y = -y;
    z = -z;

}
int main()
{
    Space s;
    s.getdata(10,-20,30);
    cout<< "S  :  ";
    s.display();

    -s;
    cout<< "-S : ";
    s.display();

    return 0;

}
