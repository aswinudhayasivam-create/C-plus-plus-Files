#include <iostream>
using namespace std;

int square(int n) {
    return n * n;
}
void checkOdd(int n)
{
    if(n%2!=0)
    {
        cout << n<<" is Odd Number "<<endl;

    }
    else{
        cout<<n<<" is Even Number "<<endl;

    }

}

int main() {
    int num;
    cout<<"Enter a number :\n";
    cin>>num;
    checkOdd(num);
    cout << "\n\nSquare :"<<square(num)<<endl;
    return 0;
}

