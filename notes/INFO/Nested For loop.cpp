#include<iostream>
using namespace std;
int main()
{
    int i,j;
    int n = 5;
    int m = 5;
    for(i=0;i<n;i++)
    {
        cout<<"Row:"<<i+1<<"\n";
        for(j=0;j<m;j++)
        {
            cout<<"  Column:"<<j+1;

        }
        cout<<"\n\n";
    }
    return 0;
}