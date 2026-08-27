#include<fstream>
#include<iostream>
using namespace std;

int main()
{
    ofstream fout("FruitsList.txt");

    fout<<"Apple"<<endl;
    fout<<"Banana"<<endl;
    fout<<"Orange"<<endl;

    fout.close();

    ifstream fin("FruitsList.txt");

    string line;

    while(getline(fin,line))
    {
        cout<<line<<endl;
    }
    fin.close();
    return 0;
    
}