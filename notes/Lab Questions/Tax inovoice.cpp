#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main()
{
    const int ITEM = 5;
    float qty[ITEM], pr[ITEM];
    string item[ITEM];
    float gstRate = 18.0;

    float Amt = 0, GST = 0;

    cout << fixed << setprecision(2);

    // Input
    for (int i = 0; i < ITEM; i++)
    {
        cout << "\nItem " << i + 1 << " Name: ";
        cin >> item[i];

        cout << "Quantity: ";
        cin >> qty[i];

        cout << "Price: ";
        cin >> pr[i];
    }

    // Table Header
    cout << "\n\n";
    cout << setw(5) << "SNo"
         << setw(12) << "Item"
         << setw(8) << "Qty"
         << setw(10) << "Price"
         << setw(10) << "GST"
         << setw(12) << "Amount\n";

    cout << string(57, '-') << endl;

    // Calculation and Output
    for (int i = 0; i < ITEM; i++)
    {
        float amount = qty[i] * pr[i];
        float gst = amount * gstRate / 100;

        Amt += amount;
        GST += gst;

        cout << setw(5) << i + 1
             << setw(12) << item[i]
             << setw(8) << qty[i]
             << setw(10) << pr[i]
             << setw(10) << gst
             << setw(12) << amount + gst << endl;
    }

    cout << string(57, '-') << endl;
    cout << setw(45) << "Total GST: " << GST << endl;
    cout << setw(45) << "Total Amount: " << Amt + GST << endl;

    return 0;
}