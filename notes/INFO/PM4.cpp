#include<iostream>
using namespace std;

class Player
{
    string name;
    string nationality;

    public:

    virtual void getData()
    {
        cout<<"Enter name of player: ";
        cin>>name;
        cout<<"Enter nationality of player: ";
        cin>>nationality;
    }

    virtual void displayData()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Nationality: "<<nationality<<endl;
    }
};

class Event : public Player

{
    string eventType;
    string eventName;
    public:
    void getData()
    {
        Player::getData();
        cout<<"Enter event type: ";
        cin>>eventType;
        cout<<"Enter event name: ";
        cin>>eventName;
    }

    void displayData()
    {
        Player::displayData();
        cout<<"Event Type: "<<eventType<<endl;
        cout<<"Event Name: "<<eventName<<endl;
    }

};

class Personal : public Player
{
    int age;
    string gender;
    public:
    void getData()
    {
        Player::getData();
        cout<<"Enter age of player: ";
        cin>>age;
        cout<<"Enter gender of player: ";
        cin>>gender;
    }

    void displayData()
    {
        Player::displayData();
        cout<<"Age: "<<age<<endl;
        cout<<"Gender: "<<gender<<endl;
    }

};

int main()
{
    choice:
    int ch;
    cout<<"Enter 1 for Event data, 2 for Personal data: ";
    cin>>ch;
    if(ch == 1)
    {
        Event e;
        e.getData();
        e.displayData();
    }
    else if(ch == 2)
    {
        Personal p;
        p.getData();
        p.displayData();
    }
    else
    {
        cout<<"Invalid choice, try again."<<endl;
        goto choice;
    }

    return 0;
}