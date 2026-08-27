#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ofstream MyFile("filename.txt");

    MyFile<<"Files can be tricky,but it is fun enough!!"<<endl;
    MyFile.close();

    string myText;

    ifstream MyReadFile("filename.txt");

    while (getline(MyReadFile,myText))
    {
        cout<<myText<<endl; 

    }
    MyReadFile.close();
    return 0;
}


