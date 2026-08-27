#include<iostream>
#include<conio.h>
using namespace std;
  class test 
  {
    public:
    int num;
    test (int  j)
    {
        num = j;

    }
    test* operator ->(void )
    {
        return this;
    }
  };

  int main()
  {
    test T(5);
    test *ptr = &T;
    cout<<"T.num = "<<T.num<<endl;
    cout<<"ptr->num = "<<ptr->num<<endl;
    cout<<"T->num = "<<T->num<<endl;

    getch ();
    return 0;

  }