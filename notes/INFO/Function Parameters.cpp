/*
void functionName(parameter1, parameter2, parameter3) {
  // code to be executed
}
  */
 #include<iostream>
 using namespace std;
 void myFunctions(int a ,int b)
 {
    int sum = a + b;
    cout<<"sum is : "<<sum<<endl;

 }
 int main()
 {
    int x,y;
    cout<<"Enter two numbers :\n";
    cin>>x>>y;
    myFunctions(x,y);
    return 0;
    
 }