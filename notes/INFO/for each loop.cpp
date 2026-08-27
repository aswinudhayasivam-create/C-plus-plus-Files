/*for (type variableName : arrayName) {
  // code block to be executed
}*/
#include <iostream>
using namespace std;

int main() {
  // Create an array of integers
  int myNumbers[5] = {10, 20, 30, 40, 50};
  
  // Loop through integers
  for (int num : myNumbers) {
    cout << num << "\n";
  }
  return 0;
}
