#include <iostream>
using namespace std;

int main()
{
    int a[20][20], r, c;

    cout << "Enter rows and columns of matrix:\n";
    cin >> r >> c;

    cout << "Enter elements of matrix:\n";
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            cin >> a[i][j];
        }
    }

    cout << "The Matrix is:\n";
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    // Identity Matrix
    int flag = 1;

    if(r != c)
    {
        cout << "\nNot an Identity Matrix\n";
    }
    else
    {
        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++)
            {
                if(i == j && a[i][j] != 1) flag = 0;
                if(i != j && a[i][j] != 0) flag = 0;
            }
        }

        if(flag == 1)
            cout << "\nIdentity Matrix\n";
        else
            cout << "\nNot an Identity Matrix\n";
    }

    // Symmetric Matrix
    flag = 1;   // IMPORTANT RESET

    if(r != c)
    {
        cout << "\nNot a Symmetric Matrix\n";
    }
    else
    {
        for(int i = 0; i < r; i++)
        {
            for(int j = i + 1; j < c; j++)
            {
                if(a[i][j] != a[j][i])
                    flag = 0;
            }
        }

        if(flag == 1)
            cout << "\nSymmetric Matrix\n";
        else
            cout << "\nNot a Symmetric Matrix\n";
    }

    return 0;
}
