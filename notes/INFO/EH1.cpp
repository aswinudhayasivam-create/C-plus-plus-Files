#include<iostream>
#include<cstring>
using namespace std;

class MyExcepetion{
    public:

    char str_what[80];
    int what;

    MyExcepetion() {
        *str_what = 0 ; 
        what = 0;
    }

    MyExcepetion(char *s, int e) {
        strcpy(str_what, s);
        what = e;

    }
};

int main(){
    int i;

    try{
        cout<<"Enter a positive integer: ";
        cin>>i;
        if(i < 0){
            throw MyExcepetion("Negative number entered", i);
        }
    }
    catch(MyExcepetion e){
        cout<<"Exception caught: "<<e.str_what<<endl;
        cout<<"Error code: "<<e.what<<endl;
    }
    return 0;
}