#include<fstream>
#include<iostream>
using namespace std;
int main()
{
    string name;
    int quantity;

    cout<<"Enter the number of fruits :  "<<endl;
    cin>>quantity;

    ofstream myfile("FruitsList.txt");
    if(myfile.is_open())
    {
        for(int i=0;i<quantity;i++)
        {
            cout<<"Enter fruit name: "<<endl;
            cin>>name;
            myfile<<name<<endl;
        }
        myfile.close();
    }
    else
    {
        cout<<"Unable to open file."<<endl;
    }
}
