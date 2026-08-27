#include<iostream>
using namespace std ;

class Father{

    protected:
    int age;
    public:
    Father(int a){
        age = a;

    }
    virtual void iam(){
        cout<<"I am the father."<<endl;
        cout<<"My age is: "<<age<<endl;

    }
};
    class Son : public Father{
        public:
        Son(int a) : Father(a) {}
        void iam(){
            cout<<"I am the son."<<endl;
            cout<<"My age is: "<<age<<endl;

        }

    };

    class Daughter : public Father{
        public:
        Daughter(int a) : Father(a) {}
        void iam(){
            cout<<"I am the daughter."<<endl;
            cout<<"My age is: "<<age<<endl;

        }
    };

int main(){
    Father *fptr;
    Son s(30);
    Daughter d(25);

    se
}