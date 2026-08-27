#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
using namespace std;

class Bank
{
    int accNo;
    char name[50];
    int balance;
    char type;

public:
    void create()
    {
        cout<<"Enter Account No: ";
        cin>>accNo;
        cin.ignore();

        cout<<"Enter Name: ";
        cin.getline(name,50);

        cout<<"Enter Type (C/S): ";
        cin>>type;

        cout<<"Enter Balance: ";
        cin>>balance;
    }

    void show()
    {
        cout<<"\nAcc No: "<<accNo;
        cout<<"\nName: "<<name;
        cout<<"\nType: "<<type;
        cout<<"\nBalance: "<<balance<<"\n";
    }

    void report()
    {
        cout<<accNo<<"\t"<<name<<"\t"<<type<<"\t"<<balance<<endl;
    }

    int getNo() { return accNo; }
    int getBal() { return balance; }

    void deposit(int amt) { balance += amt; }

    void withdraw(int amt)
    {
        if(balance >= amt)
            balance -= amt;
        else
            cout<<"Insufficient balance\n";
    }
};

void addAcc()
{
    Bank b;
    ofstream f("data.dat", ios::binary|ios::app);

    b.create();
    f.write((char*)&b, sizeof(b));

    f.close();
}

void displayOne(int n)
{
    Bank b;
    ifstream f("data.dat", ios::binary);

    while(f.read((char*)&b, sizeof(b)))
    {
        if(b.getNo()==n)
        {
            b.show();
            f.close();
            return;
        }
    }

    cout<<"Account not found\n";
    f.close();
}

void displayAll()
{
    Bank b;
    ifstream f("data.dat", ios::binary);

    cout<<"\nAccNo\tName\tType\tBalance\n";

    while(f.read((char*)&b, sizeof(b)))
        b.report();

    f.close();
}

void depositWithdraw(int n,int ch)
{
    Bank b;
    fstream f("data.dat", ios::binary|ios::in|ios::out);

    while(f.read((char*)&b, sizeof(b)))
    {
        if(b.getNo()==n)
        {
            int amt;
            b.show();

            cout<<"Enter amount: ";
            cin>>amt;

            if(ch==1) b.deposit(amt);
            else b.withdraw(amt);

            int pos = -1*sizeof(b);
            f.seekp(pos, ios::cur);
            f.write((char*)&b, sizeof(b));

            cout<<"Updated\n";
            f.close();
            return;
        }
    }

    cout<<"Account not found\n";
    f.close();
}

void deleteAcc(int n)
{
    Bank b;
    ifstream in("data.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);

    while(in.read((char*)&b, sizeof(b)))
    {
        if(b.getNo()!=n)
            out.write((char*)&b, sizeof(b));
    }

    in.close();
    out.close();

    remove("data.dat");
    rename("temp.dat","data.dat");

    cout<<"Deleted\n";
}

int login()
{
    char user[20], pass[20];

    cout<<"Username: ";
    cin>>user;
    cout<<"Password: ";
    cin>>pass;

    if(strcmp(user,"admin")==0 && strcmp(pass,"1234")==0)
        return 1;

    return 0;
}

int main()
{
    if(!login())
    {
        cout<<"Invalid Login\n";
        return 0;
    }

    int ch, num;

    do
    {
        cout<<"\n1.Create\n2.Deposit\n3.Withdraw\n4.View One\n5.View All\n6.Delete\n7.Exit\n";
        cin>>ch;

        switch(ch)
        {
            case 1: addAcc(); break;

            case 2:
                cout<<"Enter Acc No: ";
                cin>>num;
                depositWithdraw(num,1);
                break;

            case 3:
                cout<<"Enter Acc No: ";
                cin>>num;
                depositWithdraw(num,2);
                break;

            case 4:
                cout<<"Enter Acc No: ";
                cin>>num;
                displayOne(num);
                break;

            case 5:
                displayAll();
                break;

            case 6:
                cout<<"Enter Acc No: ";
                cin>>num;
                deleteAcc(num);
                break;

        }

    }while(ch!=7);

    return 0;
}