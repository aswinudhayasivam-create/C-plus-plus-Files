#include<iostream>
using namespace std;
class Matrix
{
    int a[2][2];

    public:
    void getData() {
        for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
        {
            cout<<"Enter element ["<<i<<"]["<<j<<"] : ";
            cin>>a[i][j];
        }


    }
    void display (){
        for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
        cout<< a[i][j]<<" ";
    }
    friend Matrix operator*(Matrix m1, Matrix m2);


};

Matrix operator*(Matrix m1,Matrix m2){
    Matrix temp;

    for(int i=0;i<2;i++)
    for(int j=0;j<2;j++)
    temp.a[i][j] = 0
}