#include<iostream>
using namespace std;
int main()
{
    int a[20][20],r,c;

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

    int max,min;
    max = a[0][0];
    min = a[0][0];

    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(a[i][j] > max)
                max = a[i][j];
            if(a[i][j] < min)
                min = a[i][j];
        }
    }

    cout << "Maximum element = " << max << endl;
    cout << "Minimum element = " << min << endl;
    cout<< endl;
    return 0;
    
}



