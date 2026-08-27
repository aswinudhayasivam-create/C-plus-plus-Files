/*do {
  // code block to be executed
}
while (condition);*/

#include <iostream>
using namespace std;

int main() {
  int number;
  do {
    cout << "Enter a positive number: ";
    cin >> number;
  } while (number > 0);

  return 0;
}