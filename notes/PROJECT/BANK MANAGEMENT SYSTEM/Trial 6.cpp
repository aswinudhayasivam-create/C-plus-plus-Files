#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class Account
{
    int accNo;
    char name[50];
    char type;
    int balance;
    char password[20];

public:
    void create()
    {
        cout<<"Enter Account No: ";
        cin>>accNo;
        cin.ignore();

        cout<<"Enter Name: ";
        cin.getline(name,50);

        cout<<"Set Password: ";
        cin>>password;

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

    int getNo()
    {
        return accNo;
    }

    int check(int n, char pass[])
    {
        if(accNo==n && strcmp(password,pass)==0)
            return 1;
        return 0;
    }

    void deposit(int amt)
    {
        balance += amt;
    }

    void withdraw(int amt)
    {
        if(balance>=amt)
            balance -= amt;
        else
            cout<<"Insufficient balance\n";
    }

    void write(ofstream &f)
    {
        f<<accNo<<" "<<name<<" "<<password<<" "<<type<<" "<<balance<<"\n";
    }

    void read(ifstream &f)
    {
        f>>accNo>>name>>password>>type>>balance;
    }
};

class Accounts
{
    Account acc[100];
    int count;

public:
    Accounts()
    {
        count = 0;
        load();
    }

    void load()
    {
        ifstream f("data.txt");

        while(f)
        {
            acc[count].read(f);
            if(f)
                count++;
        }

        f.close();
    }

    void save()
    {
        ofstream f("data.txt");

        for(int i=0;i<count;i++)
            acc[i].write(f);

        f.close();
    }

    int search(int n)
    {
        for(int i=0;i<count;i++)
        {
            if(acc[i].getNo()==n)
                return i;
        }
        return -1;
    }

    void addAccount()
    {
        if(count>=100)
        {
            cout<<"Limit reached\n";
            return;
        }

        acc[count].create();
        count++;
        save();
    }

    int loginUser()
    {
        int n;
        char pass[20];

        cout<<"Enter Account No: ";
        cin>>n;
        cout<<"Password: ";
        cin>>pass;

        int i = search(n);

        if(i!=-1 && acc[i].check(n,pass))
            return i;

        return -1;
    }

    void userMenu(int i)
    {
        int ch, amt;

        do
        {
            cout<<"\n1.Deposit\n2.Withdraw\n3.View\n4.Exit\n";
            cin>>ch;

            if(ch==1)
            {
                cout<<"Amount: ";
                cin>>amt;
                acc[i].deposit(amt);
                save();
            }
            else if(ch==2)
            {
                cout<<"Amount: ";
                cin>>amt;
                acc[i].withdraw(amt);
                save();
            }
            else if(ch==3)
                acc[i].show();

        } while(ch>=1 && ch<=3);
    }

    void start()
    {
        int ch;

        cout<<"\n1.Create Account\n2.Login\n3.Exit\n";
        cin>>ch;

        if(ch==1)
            addAccount();

        else if(ch==2)
        {
            int i = loginUser();

            if(i!=-1)
                userMenu(i);
            else
                cout<<"Invalid account\n";
        }
    }
};

int main()
{
    Accounts system;
    system.start();
    return 0;
}