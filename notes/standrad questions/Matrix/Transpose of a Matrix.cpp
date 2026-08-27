#include<iostream>
using namespace std;
int main()
{
    int a[20][20],t[20][20],r,c;

    cout<<"Enter rows and colunms of a matrix:\n";
    cin>>r>>c;

    cout<<"Enter elements of matrix:\n";
    for(int i = 0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>a[i][j];
        }
      
    }
    cout<<"The Matrix is:\n";
    for(int i = 0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<a[i][j]<<" ";
        }
          cout<<endl;
      
    }

    for(int i = 0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            t[j][i]=a[i][j];
        }
    }

    cout<<"The Transpose of the  Matrix is:\n";
    for(int i = 0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<t[i][j]<<" ";
        }
          cout<<endl;
      
    }
    return 0;
    
}