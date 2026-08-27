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
    cout<<"\n\nThe Matrix is:\n";
    for(int i = 0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<a[i][j]<<" ";
        }
          cout<<endl;
           cout<<endl;
      
    }
cout<<"\n\nThe Diagonal Elements are:\n";
 for(int i = 0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {

            if(i==j)
            {
                cout<<a[i][j]<<" ";
            }


        }
    }
    cout<<endl;

    
    int sum = 0;
for(int i=0;i<r;i++)
{
 for(int j=0;j<c;j++)
  {
   if(i==j)
   {
     sum += a[i][j];
   }
  }

}
cout << "\n\nSum of the Diagonal Elements are:= " << sum;
cout<<endl;
    return 0;
    


}
