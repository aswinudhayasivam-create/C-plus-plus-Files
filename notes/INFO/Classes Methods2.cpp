#include<iostream>
#include<string>
using namespace std;
class Book{
    public:
    string title;
    string author;
    float price;
    int year;

    void getDetails();
    void displayDetails();

};



void Book::getDetails(){
     cin.ignore(); 
    cout<<"Enter book title:";
    getline(cin,title);
    cout<<"Enter book author :";
    getline(cin,author);
    cout<<"Enter book price :";
    cin>>price;
    cout<<"Enter book year :";
    cin>>year;
}
void Book::displayDetails(){
    cout<<"Book Title: "<<title<<endl;
    cout<<"Book Author: "<<author<<endl;
    cout<<"Book Price: "<<price<<endl;
    cout<<"Book Year: "<<year<<endl;
}
int main()
{
    int n;
    cout<<"Enter number of books:";
    cin>>n;
  
    Book* books = new Book[n];
    for(int i=0;i<n;i++){
        cout<<"Enter details for book "<<i+1<<":"<<endl;
        books[i].getDetails();
        
        books[i].displayDetails();
    }
    if(n>0){
        cout<<"Details of first book entered:"<<endl;
        books[0].displayDetails();
    }
    delete[] books;
    return 0;

}
