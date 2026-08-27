#include <iostream>
using namespace std;

const int m = 50;

class ITEMS
{
    int itemCode[m];
    float itemPrice[m];
    int count;

public:
    void CNT();             
    void getItem();
    void displaySum();
    void remove();
    void displayItems();
};

// initialize count
void ITEMS::CNT()
{
    count = 0;
}

void ITEMS::getItem()
{
    cout << "Enter item code: ";
    cin >> itemCode[count];

    cout << "Enter item price: ";
    cin >> itemPrice[count];

    count++;
}

void ITEMS::displaySum()
{
    float sum = 0;
    for (int i = 0; i < count; i++)
        sum += itemPrice[i];

    cout << "\nTotal Value: " << sum << endl;
}

void ITEMS::remove()
{
    int a;
    cout << "Enter item code to remove: ";
    cin >> a;

    for (int i = 0; i < count; i++)
    {
        if (itemCode[i] == a)
            itemPrice[i] = 0;
    }
}

void ITEMS::displayItems()
{
    cout << "\nCode   Price\n";
    for (int i = 0; i < count; i++)
    {
        cout << itemCode[i] << "    " << itemPrice[i] << endl;
    }
}

int main()
{
    ITEMS order;
    order.CNT();

    int x;
    do
    {
        cout << "\nYou can do the following:";
        cout << "\n1 : Add an item";
        cout << "\n2 : Display total value";
        cout << "\n3 : Delete an item";
        cout << "\n4 : Display all items";
        cout << "\n5 : Quit";
        cout << "\nEnter your choice: ";

        cin >> x;

        switch (x)
        {
        case 1:
            order.getItem();
            break;

        case 2:
            order.displaySum();
            break;

        case 3:
            order.remove();
            break;

        case 4:
            order.displayItems();
            break;

        case 5:
            break;

        default:
            cout << "Invalid input, try again!\n";
        }

    } while (x != 5);

    return 0;
}
