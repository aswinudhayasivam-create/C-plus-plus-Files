#include<iostream>
using namespace std;

void getString(string &str)
{
    cout<<"Enter a string: ";
    getline(cin,str);

}
void getlength(string &str,int &length)
{
    length = str.length();

}
void printString(string &str)
{
    cout<<"The String is :"<<str<<endl;

}
void printLength(int &length)
{
    cout<<"The Length of the sting is :"<<length<<endl;

}

int main()
{
    string myString;
    int strLength;

    getString(myString);
    getlength(myString,strLength);

    printString(myString);
    printLength(strLength);
    return 0;
    
}