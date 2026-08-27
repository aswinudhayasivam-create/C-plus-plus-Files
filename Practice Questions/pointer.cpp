#include<iostream>
using namespace std;
void  copy(string &n)    
{
n = "Udhaya";      
}

void print (string &n)
{
    cout<<n<<endl;

}
int main()
{
    string n = "Aswin ";
    copy(n);
    print(n);

    return 0;

}