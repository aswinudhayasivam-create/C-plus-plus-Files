#include<iostream>
using namespace std;

class Matrix
{
    int rows, cols;
    int mat[10][10];

public:

    Matrix(int r,int c)
    {
        rows = r;
        cols = c;
    }

    void inp()
    {
        cout<<"Enter matrix elements:\n";

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                cin>>mat[i][j];
            }
        }
    }

    void display()
    {
        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                cout<<mat[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    Matrix operator+(const Matrix &m)
    {
        Matrix add(rows,cols);

        if(rows!=m.rows || cols!=m.cols)
        {
            cout<<"Addition not possible\n";
            return add;
        }

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                add.mat[i][j]=mat[i][j]+m.mat[i][j];
            }
        }

        return add;
    }

    Matrix operator-(const Matrix &m)
    {
        Matrix sub(rows,cols);

        if(rows!=m.rows || cols!=m.cols)
        {
            cout<<"Subtraction not possible\n";
            return sub;
        }

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
            {
                sub.mat[i][j]=mat[i][j]-m.mat[i][j];
            }
        }

        return sub;
    }

    Matrix operator*(const Matrix &m)
    {
        Matrix mul(rows,m.cols);

        if(cols!=m.rows)
        {
            cout<<"Multiplication not possible\n";
            return mul;
        }

        for(int i=0;i<rows;i++)
        {
            for(int j=0;j<m.cols;j++)
            {
                mul.mat[i][j]=0;

                for(int k=0;k<cols;k++)
                {
                    mul.mat[i][j]+=mat[i][k]*m.mat[k][j];
                }
            }
        }

        return mul;
    }
    void boundary()
    {
    for(int i=0;i<cols;i++)
    {
        cout<<mat[0][i]<<" ";
    }
    cout<<endl;
    for(int i=1;i<rows-1;i++)
    {
        cout<<mat[i][0]<<" ";
        cout<<mat[i][cols-1]<<" ";
        cout<<endl;
    }
    for(int i=0;i<cols;i++)
    {
        cout<<mat[rows-1][i]<<" ";
    }
};

int main()
{
    int r1,c1,r2,c2;

    cout<<"Enter rows and cols of first matrix: ";
    cin>>r1>>c1;

    cout<<"Enter rows and cols of second matrix: ";
    cin>>r2>>c2;

    Matrix m1(r1,c1);
    Matrix m2(r2,c2);

    m1.inp();
    m2.inp();

    Matrix sum = m1 + m2;
    Matrix diff = m1 - m2;
    Matrix prod = m1 * m2;

    cout<<"Sum:\n";
    sum.display();

    cout<<"Difference:\n";
    diff.display();

    cout<<"Product:\n";
    prod.display();

    cout<<"Boundary elements of first matrix:\n";
    m1.boundary();

    cout<<"Boundary elements of second matrix:\n";
    m2.boundary();
    

    return 0;
}