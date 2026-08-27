#include<iostream>
using namespace std;    

class M {
protected:
    int m;
public:
    void getM(int);
};

class N {
protected:
    int n;
public:
    void getN(int); 
};

class P : public M, public N {
public:
    void display();   // only declaration here
};  

void M::getM(int x){
    m = x;
}   

void N::getN(int y){
    n = y;
}

void P::display(){
    cout << "Value of m: " << m << endl;
    cout << "Value of n: " << n << endl;
}

int main(){
    P obj;
    obj.getM(10);
    obj.getN(20);
    obj.display();
    return 0;
}