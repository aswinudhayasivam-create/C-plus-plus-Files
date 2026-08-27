#include<iostream>
using namespace std;

class Matrix
{
protected:
    int a[3][3];

public:

    void getData()
    {
        cout<<"Enter 9 elements:"<<endl;

        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                cin>>a[i][j];
            }
        }
    }

    void displayData()
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};

class MatrixA : public Matrix
{
public:

    void displayData()
    {
        cout<<"Matrix A:"<<endl;
        Matrix::displayData();
    }
};

class MatrixB : public MatrixA
{
public:

    void displayData()
    {
        cout<<"Matrix B:"<<endl;
        Matrix::displayData();
    }
};

int main()
{
    Matrix m;
    MatrixA a;
    MatrixB b;

    cout<<"Base Matrix:"<<endl;
    m.getData();

    cout<<"Matrix A:"<<endl;
    a.getData();

    cout<<"Matrix B:"<<endl;
    b.getData();

    cout<<"\nDisplaying matrices:\n";

    cout<<"Base Matrix:"<<endl;
    m.displayData();

    a.displayData();
    b.displayData();

    return 0;
}