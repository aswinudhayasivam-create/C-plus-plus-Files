#include<iostream>
using namespace std;

class TIME
{
    int hours;
    int minutes;
    int seconds;
    
    public:

    TIME()
    {
        hours = 0;
        minutes = 0;
        seconds = 0;

    }

    TIME(int h,int m,int s)
    {
        hours = h;
        minutes = m;
        seconds = s;
    }

    TIME operator+(TIME t)
    {
        TIME temp;

        temp.seconds = seconds + t.seconds;
        temp.minutes = minutes + t.minutes ;
        temp.hours = hours + t.hours;

        if(temp.seconds >= 60)
        {
            temp.minutes++;
            temp.seconds -= 60;

        }
        if(temp.minutes >= 60)
        {
            temp.hours++;
            temp.minutes -= 60;
        }
        return temp;
    }

    friend ostream& operator<<(ostream &out, TIME t)
    {
        out<<t.hours<<" hours "<<t.minutes<<" minutes "<<t.seconds<<" seconds";
        return out;
    }
};

int main()
{
    TIME t1;
    TIME t2(2,45,50);
    TIME t3(1,20,30);

    TIME sum;

    cout<< " Default time: "<<t1<<endl;
    cout<<"TIME 1: "<<t2<<endl;
    cout<<"TIME 2: "<<t3<<endl;

    sum = t2 + t3;

    cout<<"Sum of TIME 1 and TIME 2: "<<sum<<endl;

    return 0;
    
}