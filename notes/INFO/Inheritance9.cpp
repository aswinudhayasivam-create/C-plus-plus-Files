#include<iostream>
using namespace std;

class Mammals

{
    public:
    void display()
    {
        cout<<" I am a mammal "<<endl;  
    }
};

class MarineAnimals
{
    public:
    void display()
    {
        cout<<" I am a marine animal "<<endl;  
    }
};

class BlueWhale : public Mammals, public MarineAnimals
{
    public:
    void display()
    {
        Mammals::display();
        MarineAnimals::display();
        cout<<" I am a blue whale "<<endl;  
    }
};

int main()
{
    BlueWhale bw;
    bw.display();
    return 0;
}