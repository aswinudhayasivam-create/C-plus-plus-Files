#include<iostream>
#include<string>
using namespace std;

class Dog {
public:
    string name;
    string breed;
    int age;

    void getDetails();
    void displayDetails();
    void bark();
};

void Dog::getDetails() {
    cin.ignore();   // clear leftover newline

    cout << "Enter dog's Name: ";
    getline(cin, name);

    cout << "Enter dog's Breed: ";
    getline(cin, breed);

    cout << "Enter dog's Age: ";
    cin >> age;
}

void Dog::displayDetails() {
    cout << "Dog's Name  : " << name << endl;
    cout << "Dog's Breed : " << breed << endl;
    cout << "Dog's Age   : " << age << endl;
}

void Dog::bark() {
    cout << name << " says Woof Woof!" << endl;
}

int main() {
    int n;
    cout << "Enter number of dogs: ";
    cin >> n;

    Dog* dogs = new Dog[n];

   
    cout << "\n Enter Dog Details \n";
    for(int i = 0; i < n; i++) {
        cout << "\nDog " << i + 1 << ":" << endl;
        dogs[i].getDetails();
    }

    
    cout << "\n Dog Details \n";
    for(int i = 0; i < n; i++) {
        cout << "\nDog " << i + 1 << ":" << endl;
        dogs[i].displayDetails();
        dogs[i].bark();
    }

    delete[] dogs;
    return 0;
}
