#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

double power(int a, int b = 2)
{
    return pow(a, b);
}

double power(double a, int b = 2)
{
    return pow(a, b);
}

int main()
{
    cout << fixed << setprecision(2);

    cout << "Test 1: " << power(2,3) << endl;
    cout << "Test 2: " << power(5) << endl;
    cout << "Test 3: " << power(2.5,2) << endl;
    cout << "Test 4: " << power(3.3,3) << endl;
    cout << scientific << "Test 5: " << power(10,5) << endl;

    return 0;
}