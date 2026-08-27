#include<iostream>
using namespace std;
int main()
{
    int a[20][20],b[20][20],sum[20][20],r,c;
    cout<<"Enter the order of a matrix :\n";
    cin>>r>>c;
    
    cout<<"Enter elements of matrix a :\n";
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>a[i][j];
        }
    }

    cout<<"Enter elements of matrix b :\n";
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cin>>b[i][j];
        }
    }

    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            sum[i][j]=a[i][j]+b[i][j];

        }
    }
    cout<<"Sum of two Matrix is :\n";
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<sum[i][j]<<" ";
        }
            cout<<endl;
    }
    return 0;
    

}
