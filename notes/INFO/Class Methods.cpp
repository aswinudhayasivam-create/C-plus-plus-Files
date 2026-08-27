#include<iostream>
#include<string>
using namespace std;

class MyClass{
    public:
    void displayMessage(){
        cout<<"Hello from MyClass!"<<endl;

    }
};
int main()
{
    MyClass obj;
    obj.displayMessage();
    return 0;
}