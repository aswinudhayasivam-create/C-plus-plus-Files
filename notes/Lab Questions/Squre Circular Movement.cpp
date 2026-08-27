#include<iostream>
using namespace std;

class Square
{
    int size;
    int row ,col;
    public:
    Square(int s = 5)
    {
        size = s;
        row = 0;
        col = 0;

    }
    void moveUp()
    {
        row = (row -1 + size) % size;

    }
   
   

    void displayPosition()
    {
        cout << "Current Position: (" << row << ", " << col << ")\n";
    }
};

int main()
{
    Square s;

    s.displayPosition();
   
    
    
    s.moveUp();
    s.displayPosition();

    return 0;
}
