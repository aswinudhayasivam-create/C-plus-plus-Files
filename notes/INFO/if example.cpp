#include <iostream>

using namespace std;
int main() {
    int myAge;
    bool isCitizen = true;
    cout<<"\nEnter your age:";
    cin>>myAge;

    if(myAge>=18){
        cout<<"\nu can vote \n";
        {
            if(isCitizen){
                cout<<"\n U r eligible to vote \n";
            }
            else{
                cout<<"\n U r not eligible to vote \n";
            }
            }
        }
        else{
            cout<<"\n u cannot vote \n";
        }
    
        int temperature ;
        cout<<"\ntemperature:";
    cin>>temperature; 

if (temperature < 0) {
  cout << "It's freezing!\n";
} else if (temperature < 20) {
  cout << "It's cool.\n";
} else {
  cout << "It's warm.\n";
}
    return 0;

}