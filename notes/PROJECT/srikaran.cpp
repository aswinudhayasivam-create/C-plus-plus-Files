#include<iostream>
using namespace std;

class PERSON {
protected:
    int id;
    string name;
    string blood;
public:
    void input() {
        cout<<"Enter ID: ";
        cin>>id;
        cout<<"Enter Name: ";
        cin>>name;
        cout<<"Enter Blood Group: ";
        cin>>blood;
    }

    void display() {
        cout<<"\nID: "<<id;
        cout<<"\nName: "<<name;
        cout<<"\nBlood Group: "<<blood;
    }

    string getBlood() {
        return blood;
    }

    int getId() {
        return id;
    }
};

class Donor : public PERSON {
    int age;
public:
    void inputDonor() {
        input();
        cout<<"Enter Age: ";
        cin>>age;
    }

    void showDonor() {
        display();
        cout<<"\nAge: "<<age<<"\n";
    }
};

class Receiver : public PERSON {
    int units;
public:
    void inputReceiver() {
        input();
        cout<<"Units Needed: ";
        cin>>units;
    }

    void showReceiver() {
        display();
        cout<<"\nUnits Required: "<<units<<"\n";
    }

    int getUnits() {
        return units;
    }
};

class BLBANK {
    Donor d[50];
    Receiver r[50];
    int dCount, rCount;

    // simple compatibility check
    bool check(string dBlood, string rBlood) {
        if(dBlood == rBlood) return true;

        if(dBlood == "O-") return true;

        if(dBlood == "O+" && (rBlood=="O+" || rBlood=="A+" || rBlood=="B+" || rBlood=="AB+")) return true;

        if(dBlood == "A-" && (rBlood=="A-" || rBlood=="A+" || rBlood=="AB-" || rBlood=="AB+")) return true;

        if(dBlood == "A+" && (rBlood=="A+" || rBlood=="AB+")) return true;

        if(dBlood == "B-" && (rBlood=="B-" || rBlood=="B+" || rBlood=="AB-" || rBlood=="AB+")) return true;

        if(dBlood == "B+" && (rBlood=="B+" || rBlood=="AB+")) return true;

        if(dBlood == "AB-" && (rBlood=="AB-" || rBlood=="AB+")) return true;

        return false;
    }

public:
    BLBANK() {
        dCount = 0;
        rCount = 0;
    }

    void addDonor() {
        if(dCount < 50) {
            d[dCount].inputDonor();
            dCount++;
        } else {
            cout<<"\nDonor list full\n";
        }
    }

    void addReceiver() {
        if(rCount < 50) {
            r[rCount].inputReceiver();
            rCount++;
        } else {
            cout<<"\nReceiver list full\n";
        }
    }

    void showDonors() {
        if(dCount == 0) {
            cout<<"\nNo donors available\n";
            return;
        }
        for(int i=0;i<dCount;i++) {
            cout<<"\n--- Donor "<<i+1<<" ---";
            d[i].showDonor();
        }
    }

    void showReceivers() {
        if(rCount == 0) {
            cout<<"\nNo receivers available\n";
            return;
        }
        for(int i=0;i<rCount;i++) {
            cout<<"\n--- Receiver "<<i+1<<" ---";
            r[i].showReceiver();
        }
    }

    void searchBlood() {
        string bg;
        int found = 0;
        cout<<"Enter blood group to search: ";
        cin>>bg;

        for(int i=0;i<dCount;i++) {
            if(d[i].getBlood() == bg) {
                d[i].showDonor();
                found = 1;
            }
        }

        if(found == 0)
            cout<<"\nNo matching donors found\n";
    }

    void match() {

        for(int i=0;i<rCount;i++) {
            cout<<"\nMatching for Receiver ID "<<r[i].getId()<<":\n";
            int found = 0;

            for(int j=0;j<dCount;j++) {
                if(check(d[j].getBlood(), r[i].getBlood())) {
                    d[j].showDonor();
                    found = 1;
                }
            }

            if(found == 0)
                cout<<"No donor available\n";
        }
    }
};

template <class T>
void heading(T text) {
    cout<<"\n==== "<<text<<" ====\n";
}

int main() {
    BLBANK b;
    int ch;

    do {
        heading("BLOOD BANK");
        cout<<"\n1. Add Donor";
        cout<<"\n2. Add Receiver";
        cout<<"\n3. Show Donors";
        cout<<"\n4. Show Receivers";
        cout<<"\n5. Search Donor by Blood";
        cout<<"\n6. Match Donor & Receiver";
        cout<<"\n7. Exit";
        cout<<"\nEnter choice: ";
        cin>>ch;

        switch(ch) {
            case 1: b.addDonor(); break;
            case 2: b.addReceiver(); break;
            case 3: b.showDonors(); break;
            case 4: b.showReceivers(); break;
            case 5: b.searchBlood(); break;
            case 6: b.match(); break;
            case 7: cout<<"\nExiting...\n"; break;
            default: cout<<"\nInvalid choice\n";
        }

    } while(ch != 7);

    return 0;
}