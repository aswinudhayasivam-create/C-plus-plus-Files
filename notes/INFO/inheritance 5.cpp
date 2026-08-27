#include<iostream>
using namespace std; 
class B{

    int a;
    public:
    int b;
    void getab();
    int geta(void);
    void showa(void);

};

class D :private B{

    int c;
    public:
    void mul (void);
    void display(void); 
};

void B::getab(){
    cout<<"Enter the value of a and b: ";
    cin>>a>>b;
}
int B::geta(void){
    return a;
}
void B::showa(void){
    cout<<"The value of a is: "<<a<<endl;
}
void D::mul(void){
    c = geta() * b;
}   
void D::display(void){
    showa();
    cout<<"The value of b is: "<<b<<endl;
    cout<<"The value of c is: "<<c<<endl;
}

int main(){
    D d;
   //     d.getab();
    d.mul();
   // d.showa();
    d.display();
   // d.b = 20; // Accessing public member of class B through class D
    d.mul();
    d.display();
    return 0;
}   