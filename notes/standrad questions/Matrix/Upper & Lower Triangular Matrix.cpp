#include<iostream>
using namespace std;
int main()
{
int a[20][20],n;
int upper = 1,lower = 1;

    cout<<"Enter order of square matrix:\n";
    cin>>n;

    cout<<"Enter elements of matrix:\n";
    for(int i = 0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>a[i][j];
        }

    }

    for(int i = 0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i>j && a[i][j] != 0)
            {
                upper = 0;
            }
            if(i<j && a[i][j] != 0)
            {
                lower = 0;
            }
        }

    }

    if(upper == 1)
    {
        cout<<"\n\nUpper Triangular Matrix\n\n";
    }
    else
    {
        cout<<"\n\nNot an Upper Triangular Matrix\n\n";
    }

    if(lower == 1)
    {
        cout<<"\n\nLower Triangular Matrix\n\n";
    }
    else
    {
        cout<<"\n\nNot a Lower Triangular Matrix\n\n";
    }

    return 0;
}