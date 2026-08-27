#include<fstream>
#include<iostream>
using namespace std;

int main()
{

    ifstream myfile("FruitsList.txt");
    if(myfile.is_open())
    
    {
        char ch;
        while(myfile.good())
        {
            ch=myfile.get();
            cout<<ch;

        }
    }
    else
    {
        cout<<"Unable to open file."<<endl;
    }

    return 0;
}
