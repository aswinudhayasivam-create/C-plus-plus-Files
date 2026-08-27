#include<iostream>
using namespace std;

class Number {

    protected :
    int val;
    public:
    void setval(int i) {val = i;}

    virtual void show() = 0;

};

class Hextype : public Number{

    public:
    void show(){
        cout<<hex<<val<<endl;

    }
};

class Dectype : public Number{

    public:
    void show(){
        cout<<dec<<val<<endl;

    }
};

class Octtype : public Number{

    public:
    void show(){
        cout<<oct<<val<<endl;

    }
};


int main(){
    Dectype d;
    Hextype h;
    Octtype o;

    d.setval(20);
    d.show();

    h.setval(20);
    h.show();

    o.setval(20);
    o.show();   

    return 0;
    
}