#include <iostream>

using namespace std;
int main() {
  int myAge ;
  int votingAge =18;
  cout<<"]\nEnter your age:";
  cin>>myAge;
if (myAge >= votingAge) {
    cout << "\n";
    cout << "Old enough to vote!";
    cout << "\n";
  } else {
    cout << "\n";
    cout << "Not old enough to vote.";
    cout << "\n";
  }

  int time;
    cout<<"Enter time (0-24): ";
    cin>>time;
if (time < 18) {
  cout << "Good day.";
  cout << "\n";
} else {
  cout << "Good evening.";
  cout << "\n";
}


if (time < 10) {
  cout << "Good morning.";
  cout << "\n";
} else if (time < 20) {
  cout << "Good day.";
  cout << "\n";
} else {
  cout << "Good evening.";
  cout << "\n";
}
cout << ((time < 20) ? "Good day." : "Good evening.");
cout << "\n";

int x = 15;
int y = 25;

if (x > 10) {
  cout << "x is greater \n";

  if (y > 20) {
    cout << "y is also greater \n";
  }
}
  return 0;

 
}