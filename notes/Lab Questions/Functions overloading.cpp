#include<iostream>
#include<iomanip>

using namespace std;


int add(int a,int b)
{
    int c = a+b;
    return c;

}
double add(double a,double b)
{
    double c = a+b;
    return c;

}
int add(int a[],int b[],int n){
    cout<<"\nArray addition :";
    for(int i=0;i<n;i++)
    cout<<a[i]+b[i]<<" ";
    cout<<endl;
    
}
int main()
{
    int a,b;
    cout<<"Enter valuve for a and b :";
    cin>>a>>b;

    double c,d;
    cout<<"Enter valuve for c and d :";
    cin>>c>>d; 

    int x[50],y[50],n;
    cout<<"Enter the size of the array:";
    cin>>n;
    for(int i=0;i<n;i++){
    cout<<"Enter values for Array 1:";
    cin>>x[i];}
    for(int i=0;i<n;i++){
    cout<<"Enter values for Array 2:";
    cin>>y[i];
    }
    
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;
    cout<<d<<endl;
    cout<<x<<endl;
    cout<<y<<endl;

    cout<<"Integer addition : "<< add(a,b)<<endl;
    cout<<"Double addition : "<< add(c,d)<<endl;

    add(x,y,n);
    return 0;
}







