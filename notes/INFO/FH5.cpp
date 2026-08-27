#include<fstream>
#include<iostream>
using namespace std;

int main()
{
    ofstream myfile("File.txt");
    if(myfile.is_open())
    {
        myfile<<"Hello, this is a test file."<<endl;
        myfile<<"This file is created using C++."<<endl;
        myfile<<"File handling is important for data storage."<<endl;
        myfile.close();
    }
    else
    {
        cout<<"Unable to open file."<<endl;
    }
}