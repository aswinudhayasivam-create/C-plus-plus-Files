#include<iostream>
#include<string.h>
using namespace std;

class MyString
{
    char *p;
    int len;

public:
    MyString(){len = 0; p = NULL;}

    MyString(const char *s)
    {
        len = strlen(s);
        p = new char[len + 1];
        strcpy(p, s);
    }

    MyString(const MyString &s)
    {
        len = s.len;
        p = new char[len + 1];
        strcpy(p, s.p);
    }

    ~MyString()
    {
        delete[] p;
    }

    friend MyString operator+(const MyString &s, const MyString &t);
    friend int operator<=(const MyString &s, const MyString &t);
    friend void show(const MyString &s);
};

MyString operator+(const MyString &s, const MyString &t)
{
    MyString temp;
    temp.len = s.len + t.len;
    temp.p = new char[temp.len + 1];

    strcpy(temp.p, s.p);
    strcat(temp.p, t.p);

    return temp;
}

int operator<=(const MyString &s, const MyString &t)
{
    if(strlen(s.p) <= strlen(t.p))
        return 1;
    else
        return 0;
}

void show(const MyString &s)
{
    cout << s.p << endl;
}

int main()
{
    MyString s1 = "New ";
    MyString s2 = "York";
    MyString s3 = "Delhi";

    MyString string1, string2, string3;

    string1 = s1;
    string2 = s2;
    string3 = s1 + s3;

    cout << "String 1 : "; show(string1);
    cout << "String 2 : "; show(string2);
    cout << endl;

    cout << "String 3 : "; show(string3);
    cout << endl;

    if(string1 <= string3)
        cout << "String 1 is smaller than or equal to String 3\n";
    else
        cout << "String 1 is greater than String 3\n";

    cout << endl;

    if(string2 <= string3)
        cout << "String 2 is smaller than or equal to String 3\n";
    else
        cout << "String 2 is greater than String 3\n";

    cout << endl;

    if(string3 <= string1)
        cout << "String 3 is smaller than or equal to String 1\n";
    else
        cout << "String 3 is greater than String 1\n";

    cout << endl;

    if(string3 <= string2)
        cout << "String 3 is smaller than or equal to String 2\n";
    else
        cout << "String 3 is greater than String 2\n";

    return 0;
}