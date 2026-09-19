#include<iostream>
#include<string>
#include<vector>

using namespace std;
int main()
{
    int n;
    cout<<"Enter the sizeof the array:";
    cin>>n;
    if (n < 0) {
        cout << "Array size cannot be negative.\n";
        return 1;
    }
    vector<string> cars(n);
    cout<<"Enter the cars names:\n";
    for(int i=0;i<n;i++)
    {
        cin>>cars[i];
    }
    cout<<"The car names are:\n";

    //cars[n] = {"Volvo","BMW","Benz","Audi","Ferrari"};
    for(string i : cars)
    {
        cout<<i<<endl;

    }
    return 0;

}
