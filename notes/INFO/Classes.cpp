#include<iostream>
#include<string>
using namespace std;

class Car{
    public:
    string brand;
    string model;
    int year;
};
int main()
{
    Car car1,car2;

    car1.brand = "BMW";
    car1.model = "X5";
    car1.year = 2020;

    car2.brand = "Audi";
    car2.model = "A4";
    car2.year = 2019;


    cout<<"Car Details:\n";
    cout<<"Brand : "<<car1.brand<<"\n";
    cout<<"Model : "<<car1.model<<"\n";
    cout<<"Year  : "<<car1.year<<"\n";

    cout<<"\nCar Details:\n";
    cout<<"Brand : "<<car2.brand<<"\n";
    cout<<"Model : "<<car2.model<<"\n";
    cout<<"Year  : "<<car2.year<<"\n";  
    return 0;
}
