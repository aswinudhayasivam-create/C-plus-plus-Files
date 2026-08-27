#include<iostream>
using namespace std;

void getMatrix(int a[20][20],int r,int c)
{
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<"Enter element at position ["<<i<<"]["<<j<<"] : ";
            cin>>a[i][j];
        }
    }
}
void printMatrix(int a[20][20], int r,int c)
{
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<a[i][j]<<" "; 
        }
        cout<<endl;

    }
}

void addMatrix(int a[20][20],int b[20][20],int r ,int c)
{
    int sum[20][20];
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            sum[i][j] = a[i][j] + b[i][j];
        }
    }
    cout<<"Sum of two Matrix is : \n";
    printMatrix(sum,r,c);
}
void multiplyMatrix(int a[20][20],int b[20][20],int r1,int c1,int r2,int c2)
{
    int product[20][20];
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c2;j++)
        {
            product[i][j]=0;
            for(int k=0;k<c1;k++)
            {
                product[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    cout<<"Product of two Matrix is : \n";
    printMatrix(product,r1,c2);
}
int main()
{
    int r1,c1,r2,c2;
    int matrix1[20][20],matrix2[20][20];

    cout<<"Enter rows and columns for first matrix: ";
    cin>>r1>>c1;
    getMatrix(matrix1,r1,c1);

    cout<<"Enter rows and columns for second matrix: ";
    cin>>r2>>c2;
    getMatrix(matrix2,r2,c2);

    cout<<"First Matrix is : \n";
    printMatrix(matrix1,r1,c1);

    cout<<"Second Matrix is : \n";
    printMatrix(matrix2,r2,c2);

    if(r1==r2 && c1==c2)
    {
        addMatrix(matrix1,matrix2,r1,c1);
    }
    else{
        cout<<"Matrix addition not possible as dimensions do not match.\n";
    }

    if(c1==r2)
    {
        multiplyMatrix(matrix1,matrix2,r1,c1,r2,c2);
    }
    else{
        cout<<"Matrix multiplication not possible as dimensions do not match.\n";
    }

    return 0;
}