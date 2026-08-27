#include <iostream>
using namespace std;

int main() {
  bool isCodingFun = true;
  bool isFishTasty = false;

  cout << boolalpha; // enable printing "true"/"false"

  cout << isCodingFun << "\n";   
  cout << isFishTasty << "\n"; 
  
  bool isCodingsFun = true;


cout << isCodingsFun << "\n";  // Outputs true
//out << noboolalpha; // reset to 1/0
cout << isCodingFun << "\n";  // Outputs 1
cout << isCodingFun << "\n";   
  cout << isFishTasty << "\n";

  int x = 10;
int y = 9;
cout << (x > y);
cout << "\n";
cout << (10 == 15);
cout << "\n";
cout << (x == 10);
cout << "\n";

int myAge = 25;
int votingAge = 18;

cout << (myAge >= votingAge);
cout << "\n";

  return 0;
}
