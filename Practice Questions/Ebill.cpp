#include<iostream>
using namespace std;

class Ebill
{

    private :
    string Cname;
    long Cnumber;
    int No_of_units;
    float Amount ;


    void Calc_Amount()
    {
        if(No_of_units <= 50)
        {
            Amount = 0;
        }
        else if(No_of_units <= 150)
        {
            Amount = (No_of_units - 50) * 0.85;
        }
        else if(No_of_units <= 350)
        {
            Amount = (100*0.80) + (No_of_units - 150) * 1.00;
        }
        else{
            Amount = (100*0.80) + (200*1.00) + (No_of_units - 350) * 1.20;

        }
    }
    public:

    void Accept()
    {
        cout << "Enter customer name: ";
        cin >> Cname;
        cout << "Enter customer number: ";
        cin >> Cnumber;
        cout << "Enter number of units: ";
        cin >> No_of_units;

        Calc_Amount();

    }

    void Display()
    {
        cout << "Customer Name: " << Cname << endl;
        cout << "Customer Number: " << Cnumber << endl;
        cout << "Number of Units: " << No_of_units << endl;
        cout << "Amount: " << Amount << endl;
    }
};

int main()
{
    Ebill e;

    e.Accept();
    e.Display();

    return 0;
}