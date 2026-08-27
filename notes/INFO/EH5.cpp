#include<iostream>
using namespace std;
#include<exception>

class MyException : public exception {
public:
    const char* what() const noexcept override {
        return "My custom exception occurred!!";
    }
};

int Division(int a, int b)
{
    if (b == 0)
        throw 1;
    if (b == 1)
        throw MyException();

    return a / b;
}

int main()
{
    int x = 10, y = 1, z;

    try {
        z = Division(x, y);
        cout << "Result: " << z << endl;
    }
    catch (int x) {
        cout << "Error: Division by zero is not allowed!!" << endl;
    }
    catch (const MyException& ME) {
        cout << "Division by one Error" << endl;
        cout << "Error: " << ME.what() << endl;
    }

    cout << "End of the Program" << endl;
    return 0;
}