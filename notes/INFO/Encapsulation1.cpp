#include<iostream>
using namespace std;

class student{
    private:
    int roll;
    public:

    void setRoll(int r){
        roll = r;
   }

   int getRoll(){
    return roll;

   }
};

int main() {
    int n;
    student s;

    cout<<"Enter the roll number :";
    cin>>n;
    cout<<endl;

    s.setRoll(n);
    cout<<"This is your Roll Number :"<<s.getRoll();
    cout<<endl;
    
    return 0;
}