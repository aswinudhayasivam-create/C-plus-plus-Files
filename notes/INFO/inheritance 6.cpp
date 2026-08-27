#include<iostream>
using namespace std;
class student
{
    protected:
    int rollno;
    public:
    void getrollno(int );
    void showrollno(void);
};

void student::getrollno(int r){
    rollno = r;
}
void student::showrollno(void){
    cout<<"The roll number is: "<<rollno<<endl;
}

class test : public student
{
    protected:
    float marks1, marks2;
    public:
    void getmarks(float, float);
    void showmarks(void);
};
void test::getmarks(float m1, float m2){
    marks1 = m1;
    marks2 = m2;
}
void test::showmarks(void){
    cout<<"Marks1: "<<marks1<<endl;
    cout<<"Marks2: "<<marks2<<endl;
}

class result : public test
{
    float percentage;
    public:
    void display(void);
};
void result::display(void){
    percentage = (marks1 + marks2) / 2;
    showrollno();
    showmarks();
    cout<<"Percentage: "<<percentage<<"%"<<endl;
}
int main(){
    result res;
    res.getrollno(101);
    res.getmarks(85.5, 90.0);
    res.display();
    return 0;
}
