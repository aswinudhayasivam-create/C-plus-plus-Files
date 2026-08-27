#include<iostream>
using namespace std;

int main(){
    cout<<"Start"<<endl;
    try {
        cout<<"Inside try block"<<endl;
        throw 100;
        cout<<"This will not be printed"<<endl;
    
    }
    catch(int i){
        cout<<"Caught an exception: "<<i<<endl;

    }

    cout<<"End"<<endl;
    return 0;


}