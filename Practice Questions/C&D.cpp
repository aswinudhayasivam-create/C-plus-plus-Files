#include<iostream>
#include<string>

using namespace std;
class Employee{
    
    private:
    string fname;
    string lname;
    float msalary;

    public:

    Employee(string f, string l,float m){
        fname = f;
        lname = l;
        msalary = m;

        if(m > 0)
        {

            msalary = m;
        }
        else {
            msalary = 0;
        }
    }

    void setFirstName(string f) {
        fname = f;
    }
    void setLastName(string l) {
        lname = l;
    }
    void setMonthlySalary(float m) {
        if(m > 0) {
            msalary = m;
        } else {
            msalary = 0;
        }
    }

    string getFirstName() {
        return fname;
    }
    string getLastName() {
        return lname;
    }
    float getMonthlySalary() {
        return msalary;
    }

};
int main(){


Employee emp1("Rahul", "Sharma", 25000);
Employee emp2("Anita", "Verma", 30000);

cout<< "YEARLY SALARY BEFORE INCREMENT" << endl;
cout<< "--------------------------------" << endl;

cout<< emp1.getFirstName() << " "
<< emp1.getLastName()
<< " : Rs. "
<< emp1.getMonthlySalary() * 12 << endl;

cout<< emp2.getFirstName() << " "
<< emp2.getLastName()
<< " : Rs. "
<< emp2.getMonthlySalary() * 12 << endl;
emp1.setMonthlySalary(
        emp1.getMonthlySalary() +
        (emp1.getMonthlySalary() * 0.10)
    );
emp2.setMonthlySalary(
        emp2.getMonthlySalary() +
        (emp2.getMonthlySalary() * 0.10)
    );
cout << "\nYEARLY SALARY AFTER 10% INCREMENT" << endl;
    cout << "-----------------------------------" << endl;

    cout << emp1.getFirstName() << " "
         << emp1.getLastName()
         << " : Rs. "
         << emp1.getMonthlySalary() * 12 << endl;

    cout << emp2.getFirstName() << " "
         << emp2.getLastName()
         << " : Rs. "
         << emp2.getMonthlySalary() * 12 << endl;

    return 0;
}