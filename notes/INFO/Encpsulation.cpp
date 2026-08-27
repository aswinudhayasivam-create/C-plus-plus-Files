
#include<iostream>
using namespace std;

class EMP
{
    private:
    int salary;

    public:
    void setSalary(int s){
        salary = s;
    }
    int getSalary(){
        return salary;
    }
    
};
int main(){
    double n;
    EMP e;

    cout<<"Enter Salary:"<<endl;
    cin>>n;

    e.setSalary(n);
    cout<<"YOUR SALARY IS:"<<e.getSalary();
    return 0;

}