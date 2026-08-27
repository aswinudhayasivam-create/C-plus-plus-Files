#include <iostream>
using namespace std;

int main() {
  
  int numbers ;
  cout<<"Enter numbers to be reversed:" ;
  cin>>numbers;

  
  int revNumbers = 0;

  
  while (numbers) {
    
    revNumbers = revNumbers * 10 + numbers % 10;
   
    numbers /= 10;
  }

  cout << "Reversed numbers: " << revNumbers << "\n";

  return 0;
}