#include <iostream>
#include <string>
using namespace std;

int main() {
  int numGuests;
  cout << "How many guests? ";
  cin >> numGuests;

  // Check for invalid input
  if (numGuests <= 0) {
    cout << "Number of guests must be at least 1.\n";
    return 0;
  }

  // Create memory space for up to 10 guests
  string* guests = new string[numGuests];

  // Ignore the leftover newline character after reading numGuests
  //cout<<endl;
  cin.ignore();


  // Enter guest names
  for (int i = 0; i < numGuests; i++) {
    cout << "Enter name for guest " << (i + 1) << ": ";
    getline(cin, guests[i]);  // Read the full name (including spaces)
  }

  // Show all guests
  cout << "\nGuests checked in:\n";
  for (int i = 0; i < numGuests; i++) {
    cout << guests[i] << "\n";
  }

  delete[] guests; // Clean up memory
  return 0;
}
