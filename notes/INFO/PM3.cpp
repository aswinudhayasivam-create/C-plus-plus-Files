#include<iostream>
using namespace std;

class father
{
protected:
    int age;

public:
    father(int x)
    {
        age = x;
    }

    virtual void iam()
    {
        cout<<"I AM THE FATHER, my age is "<<age<<endl;
    }
};

class son : public father
{
public:
    son(int x) : father(x)
    {
    }

    void iam()
    {
        cout<<"I AM THE SON, my age is "<<age<<endl;
    }
};

class daughter : public father
{
public:
    daughter(int x) : father(x)
    {
    }

    void iam()
    {
        cout<<"I AM THE DAUGHTER, my age is "<<age<<endl;
    }
};

int main()
{
    father *ptr;

    son s(20);
    daughter d(18);

    ptr = &s;
    ptr->iam();

    ptr = &d;
    ptr->iam();

    return 0;
}