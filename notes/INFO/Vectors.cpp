#include<iostream>
#include<vector>

using namespace std;
int main()
{
/*vector<int> num;
num.push_back(1);
num.push_back(2);
num.push_back(3);
num.push_back(4);
num.push_back(5);
num.push_back(6);
num.push_back(7);
num.push_back(8);
num.push_back(9);
for(int i=0;i<num.size();i++)
{
    cout<<num[i]<<endl;
}*/
vector<string>cars; //= {"Volvo", "BMW", "Ford"};
  
  
  cars.push_back("Tesla");

  
  for (string car : cars) {
    cout << car << "\n";
  }


return 0;


}
