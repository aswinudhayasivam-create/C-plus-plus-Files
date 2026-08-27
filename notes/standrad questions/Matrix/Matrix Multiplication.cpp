//Matrix Multiplication
//Columns of A = Rows of B

#include <iostream>

using namespace std;

int main() 
{
    int a[20][20],b[20][20],mul[20][20];
    int r1,c1,r2,c2;
    cout<<"Enter the order for matrix a:\n";
    cin>>r1>>c1;

    cout<<"Enter the order for matrix b:\n";
    cin>>r2>>c2;

    if(c1 != r2)
    {
        cout<<"Matrix multiplication not possible\n";
        return 0;
    
    }
    cout<<"Enter elements of matrix a:\n";
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c1;j++)
        {
            cin>>a[i][j];
        }
    }

    cout<<"Enter elements of matrix b:\n";
    for(int i=0;i<r2;i++)
    {
        for(int j=0;j<c2;j++)
        {
            cin>>b[i][j];
        }
    }

     for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            mul[i][j]=0;
            for(int k=0;k<c1;k++)
            {
                mul[i][j] += a[i][k]*b[k][j];
            }
        }
    }

    cout<<"Result:\n";
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            cout<<mul[i][j]<<" ";
        }
            cout<<endl;
    }
    return 0;

}