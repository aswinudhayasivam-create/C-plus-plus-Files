#include <iostream>
using namespace std;

int main() {
    int a[10][10];
    int r, c;

    cout << "Enter number of rows and columns: ";
    cin >> r >> c;

    cout << "Enter matrix elements:\n";
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cin >> a[i][j];
        }
    }
    cout<<"\nThe Matrix is:\n";
    for(int i = 0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<a[i][j]<<" ";
        }
          cout<<endl;
      
    }

    // Sum of each row
    cout << "\nSum of each row:\n";
    for(int i = 0; i < r; i++) {
        int sum = 0;
        for(int j = 0; j < c; j++) {
            sum = sum + a[i][j];
        }
        cout << "Row " << i + 1 << " sum = " << sum << endl;
    }

    // Sum of each column
    cout << "\nSum of each column:\n";
    for(int j = 0; j < c; j++) {
        int sum = 0;
        for(int i = 0; i < r; i++) {
            sum = sum + a[i][j];
        }
        cout << "Column " << j + 1 << " sum = " << sum << endl;
    }

    return 0;
}
