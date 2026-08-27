#include<iostream>
#include<string>

using namespace std;
int main()
{
    int n,i;
    cout<<"Enter the sizeof the array:";
    cin>>n;
    string cars[n];
    cout<<"Enter the cars names:\n";
    for(i=0;i<n;i++)
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