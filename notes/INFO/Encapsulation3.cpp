#include<iostream>
using namespace std;

class B{
    private :
    int y ;
    public:
    void set(int j){
        y = j;
    }

    friend void add(class A,B);

};

class A{
    private :
    int x;
    public:
    void set(int i){
        x = i;

    }
    friend void add(class A,B);

};

void add(A a,B b){
    cout<<"Sum :"<<a.x+b.y<<endl;
}

int main(){
    A a;
    B b;
    int x,y;
    cout<<"Enter the values of x & y:";
    cin>>x>>y;

    a.set(x);
    b.set(y);
    add(a,b);
    return 0;

}