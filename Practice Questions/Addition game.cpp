#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
    int num1,num2,answer,userAnswer;
    int correct = 0,wrong = 0;
    char choice;

    srand(time(0));

    do
    {
    
        num1 = rand()%100;
        num2 = rand()%100;
        answer = num1 + num2;   

        cout<<"\nWhat is the sum of"<<num1<<"+"<<num2<<"?";
        cin>>userAnswer;

        if(userAnswer == answer)
        {
            cout<<"Congratulations! That's correct.";
            correct++;
        }
        else
        {
            cout<<"Sorry, that's incorrect. The correct answer is "<<answer<<".";
            wrong++;
        }
        cout << "\nDo you want to try another question? (y/n): ";
        cin >> choice;
    }
    while(choice == 'y' || choice == 'Y');

    cout << "\nGame Over!" << endl;
    cout << "Correct answers: " << correct << endl;
    cout << "Wrong answers: " << wrong << endl;

    return 0;
    

}