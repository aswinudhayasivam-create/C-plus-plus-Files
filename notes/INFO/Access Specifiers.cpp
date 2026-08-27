/*public - members are accessible from outside the class
private - members cannot be accessed (or viewed) from outside the class
protected - members cannot be accessed from outside the class, however, they can be accessed in inherited classes.*/


#include<iostream>
using namespace std;

class specifers
{
    private:
    int x=5;
    public:
    int y;


};

int main(){
    specifers t;
    //t.x=5;
    t.y=25;
    cout<<endl<<t.y<<endl;

 
    return 0;

}