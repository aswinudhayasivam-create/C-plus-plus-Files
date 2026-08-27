#include<iostream>
using namespace std;

class Sound{
    public:
    void makeSound(){
        cout<<"Animal makes sound"<<endl;

    }
};

class Dog : public Sound {
    public:
    void makeSound(){
        cout<<"Dog Barks"<<endl;

    }
};

class Cat : public Sound{
    public:
    void makeSound(){
        cout<<"Cat Meows"<<endl;

    }
};

int main(){
    Sound s;
    Dog d;
    Cat c;

    s.makeSound();
    d.makeSound();
    c.makeSound();
    return 0;
    
}
