#include<iostream>
#include<string>
using namespace std;

class Car{
    public:
    string brand;
    string model;
    int year;

    Car(string x,string y,int z)
    {
        brand=x;
        model=y;
        year=z;
    }
};

int main()
{
    Car c1("Toyata","Corolla",2020);
    Car c2("Honda","Civic",2019);
    Car c3("BMW","X5",2021);
    cout<<c1.brand<<" "<<c1.model<<" "<<c1.year<<endl;
    cout<<c2.brand<<" "<<c2.model<<" "<<c2.year<<endl;
    cout<<c3.brand<<" "<<c3.model<<" "<<c3.year<<endl;
    return 0;
    
}