/*switch(expression) {
  case x:
    // code block
    break;
  case y:
    // code block
    break;
  default:
    // code block
}*/
#include <iostream>
using namespace std;

int main() {
  int day;
  cout<<"\nday:";
    cin>>day; 

  switch (day) {
  case 1:
    cout << "Monday\n";
    break;
  case 2:
    cout << "Tuesday\n";
    break;
  case 3:
    cout << "Wednesday\n";
    break;
  case 4:
    cout << "Thursday\n";
    break;
  case 5:
    cout << "Friday\n";
    break;
  case 6:
    cout << "Saturday\n";
    break;
  case 7:
    cout << "Sunday\n";
    break;
    default:
    cout << "Looking forward to the Weekend";
  }
  return 0;
}