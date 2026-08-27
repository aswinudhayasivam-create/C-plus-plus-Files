#include<iostream>
using namespace std;

class Ticket
{
    int row;
    int seat;
    bool sold;

public:

    Ticket ()
    {
        row = 0;
        seat = 0;
        sold = false;
    }

    Ticket(int r, int s)
    {
        row = r;
        seat = s;
        sold = false;
    }

    bool isSold()
    {
        return sold;
    }

    void updateStatus()
    {
        char choice;
        cout << "Is the ticket sold? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y')
            sold = true;
        else
            sold = false;
    }

    void display ()
    {
        cout << "Row: " << row
            << " Seat: " << seat
            << " Sold: " << (sold ? "Yes" : "No")
            << endl;
    }

    friend int countTickets(Ticket[], int);

    ~Ticket() {}
};


int countTickets(Ticket t[], int size)
{
    int count = 0;

    for (int i = 0; i < size; i++)
    {
        if (t[i].isSold())
            count++;
    }

    return count;
}

int main()
{
    int n;

    cout << "Enter the number of tickets: ";
    cin >> n;

    Ticket *t = new Ticket[n];

    int r, s;

    for(int i = 0; i < n; i++)
    {
        cout << "Enter row and seat for ticket " << i + 1 << ": ";
        cin >> r >> s;
        t[i] = Ticket(r, s);
    }

    cout << "\nBooking Tickets:\n";

    for(int i = 0; i < n; i++)
    {
        t[i].updateStatus();
    }

    cout << "\nTicket Details:\n";

    for(int i = 0; i < n; i++)
    {
        t[i].display();
    }

    int total = countTickets(t, n);

    cout << "\nTotal Sold Tickets: " << total << endl;

    delete[] t;

    return 0;
}