#include<iostream>
#include<string>
using namespace std;

class Book{
    public:
    string title;
    string author;
    float price;
    int year;
};

int main()
{
    Book book1,book2;

    book1.title = "Matilda";
    book1.author = "Roald Dahl";
    book1.price = 10.99;
    book1.year = 1988;

    book2.title = "The Giving Tree";
    book2.author = "Shel Silverstein";
    book2.price = 8.99;
    book2.year = 1964;

    cout<<"Book Details:\n";
    cout<<"Title  : "<<book1.title<<"\n";
    cout<<"Author : "<<book1.author<<"\n";  
    cout<<"Price  : "<<book1.price<<"\n";
    cout<<"Year   : "<<book1.year<<"\n";
    
    cout<<"\nBook Details:\n";
    cout<<"Title  : "<<book2.title<<"\n";
    cout<<"Author : "<<book2.author<<"\n";  
    cout<<"Price  : "<<book2.price<<"\n";           
    cout<<"Year   : "<<book2.year<<"\n";
    return 0;
}
