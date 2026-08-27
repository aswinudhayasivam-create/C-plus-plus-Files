#include <iostream>
using namespace std;

class Base{
public:

virtual void vfunc(){
    cout<<"This is Base vfunc\n"<<endl;
}
};

class Derived1 : public Base {
    public:

    void vfunc() {
        cout<<"This is derived 1\n"<<endl;
    }
};

class Derived2 : public Derived1 {

    public:
    void vfunc() {
        cout<<"This is derived 2\n"<<endl;

    }
};

int main(){

    Base *p,b;
    Derived1 d1;
    Derived2 d2;

    p =&b;
    p->vfunc();

    p = &d1;
    p->vfunc();

    p = &d2;
    p->vfunc();




    return 0;

}