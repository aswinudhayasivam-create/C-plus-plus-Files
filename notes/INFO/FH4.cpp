#include<fstream>
#include<iostream>
using namespace std;

int main()
{
    ofstream fout("emp.txt");

    fout<<"Name: John Doe"<<endl;
    fout<<"Age: 30"<<endl;
    fout<<"Position: Software Engineer"<<endl;
    fout<<"Department: IT"<<endl;
    fout<<"Salary: $80000"<<endl;

    fout.close();

    ifstream fin("emp.txt");

    string line;

    while(getline(fin,line))
    {
        cout<<line<<endl;

    }
    fin.close();
    return 0;
}