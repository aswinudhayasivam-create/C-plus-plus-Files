#include<iostream>
#include<cstring>
using namespace std;

class Account
{
    int accNo;
    char name[50];
    char type;
    int balance;
    char password[20];
    int history[10];
    int hCount;

public:
    Account()
    {
        accNo = 0;
        balance = 0;
        type = 'C';
        strcpy(name,"");
        strcpy(password,"");
        hCount = 0;
    }

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

        addHistory(balance);
    }

    void addHistory(int amt)
    {
        if(hCount < 10)
            history[hCount++] = amt;
        else
        {
            for(int i=0;i<9;i++)
                history[i] = history[i+1];
            history[9] = amt;
        }
    }

    int login(int n, char pass[])
    {
        if(accNo == n && strcmp(password,pass)==0)
            return 1;
        return 0;
    }

    void deposit(int amt)
    {
        balance += amt;
        addHistory(amt);
    }

    void withdraw(int amt)
    {
        if(balance >= amt)
        {
            balance -= amt;
            addHistory(-amt);
        }
        else
            cout<<"Insufficient balance\n";
    }

    void addInterest()
    {
        if(type=='S')
        {
            int interest = balance * 2 / 100;
            balance += interest;
            addHistory(interest);
            cout<<"Interest added\n";
        }
        else
            cout<<"Only for savings account\n";
    }

    void show()
    {
        cout<<"\nAcc No: "<<accNo;
        cout<<"\nName: "<<name;
        cout<<"\nType: "<<type;
        cout<<"\nBalance: "<<balance<<"\n";
    }

    void showHistory()
    {
        cout<<"Recent Transactions:\n";
        for(int i=0;i<hCount;i++)
            cout<<history[i]<<" ";
        cout<<"\n";
    }

    int getNo()
    {
        return accNo;
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
    }

    int adminLogin()
    {
        char u[20], p[20];
        cout<<"Admin Username: ";
        cin>>u;
        cout<<"Admin Password: ";
        cin>>p;

        if(strcmp(u,"admin")==0 && strcmp(p,"1234")==0)
            return 1;
        return 0;
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

    int userLogin()
    {
        int n;
        char pass[20];

        cout<<"Enter Account No: ";
        cin>>n;
        cout<<"Enter Password: ";
        cin>>pass;

        int i = search(n);

        if(i!=-1 && acc[i].login(n,pass))
            return i;

        return -1;
    }

    void userMenu(int i)
    {
        int ch, amt;

        do
        {
            cout<<"\n1.Deposit\n2.Withdraw\n3.View\n4.History\n5.Interest\n6.Exit\n";
            cin>>ch;

            if(ch==1)
            {
                cout<<"Amount: ";
                cin>>amt;
                acc[i].deposit(amt);
            }
            else if(ch==2)
            {
                cout<<"Amount: ";
                cin>>amt;
                acc[i].withdraw(amt);
            }
            else if(ch==3)
                acc[i].show();
            else if(ch==4)
                acc[i].showHistory();
            else if(ch==5)
                acc[i].addInterest();

        } while(ch>=1 && ch<=5);
    }

    void adminMenu()
    {
        int ch,n;

        do
        {
            cout<<"\n1.Create\n2.View One\n3.View All\n4.Delete\n5.Exit\n";
            cin>>ch;

            if(ch==1)
                addAccount();

            else if(ch==2)
            {
                cout<<"Enter Acc No: ";
                cin>>n;
                int i = search(n);
                if(i!=-1) acc[i].show();
                else cout<<"Not found\n";
            }

            else if(ch==3)
            {
                for(int i=0;i<count;i++)
                    acc[i].show();
            }

            else if(ch==4)
            {
                cout<<"Enter Acc No: ";
                cin>>n;
                int i = search(n);

                if(i==-1)
                {
                    cout<<"Not found\n";
                    continue;
                }

                for(int j=i;j<count-1;j++)
                    acc[j] = acc[j+1];

                count--;
                cout<<"Deleted\n";
            }

        } while(ch>=1 && ch<=4);
    }

    void start()
    {
        int ch;

        cout<<"\n1.Admin\n2.User\n";
        cin>>ch;

        if(ch==1)
        {
            if(adminLogin())
                adminMenu();
            else
                cout<<"Wrong login\n";
        }
        else if(ch==2)
        {
            int i = userLogin();
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