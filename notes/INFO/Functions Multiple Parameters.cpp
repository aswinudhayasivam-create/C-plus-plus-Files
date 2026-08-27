#include <iostream>
#include <string>
using namespace std;

void myFunction(string fname, int age) {
  cout << fname << " " << age << " years old. \n";
}

int main() {
    string name;
    int age;
cout<<"Enter name: \n";
getline(cin,name);

cout<<"Enter age:\n";
cin>>age;
myFunction(name,age);


  return 0;
}