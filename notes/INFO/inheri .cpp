#include<iostream>
using namespace std;

class Father{
    int age;
    string name;
public:
Father(int a,string n){
    age = 55;
    name = "Smith";
}
void display(){
    cout<<"Father;s Name : "<<name<<endl;
    cout<<"Father's Age : "<<age<<endl;


}

};

class Mother{

    int age ;
    string name;
    public:
    Mother(int a,string n){
        age = 50;
        name = "jane";

    }

    void display(){
        cout<<"Mother's Name : "<<name<<endl;
        cout<<"Mother's Age : "<<age<<endl;
    }
};

class Son : public Father , public Mother{
    int age;
    string name;

    public:
    Son(int a ,string n):Father(a,n),Mother(a,n){
        age = 25;
        name = "john";
    }
    void display(){
        Father::display();
        Mother::display();
        cout<<"Son's Name : "<<name<<endl;
        cout<<"Son's Age : "<<age<<endl;
    }

};

int main (){
    Son s(25,"john");
    s.display();
    return 0;

}