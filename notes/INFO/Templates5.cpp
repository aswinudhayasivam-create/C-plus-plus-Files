#include<iostream>
using namespace std;
template < class t>

class Marks
{
    t mark1,mark2;

    public:
    Marks(t x,t y)
    {
        mark1 = x;
        mark2 = y;

    }

    void total()
    {
        cout<<"Total marks: "<<mark1+mark2<<endl;
    }
    
};

int main()
{
    Marks<double> student1(85.3,90.8);
    student1.total();

    Marks<double> student2(78.5,88.9);
    student2.total();

    return 0;
}
