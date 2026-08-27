#include<iostream>
using namespace std;

int indexOfSmallestElements(int array [],int n)
{
    int minIndex = 0;

    for(int i = 1; i < n; i++)
    {
        if(array[i] < array[minIndex])
        {
            minIndex = i;
        }
    }

    return minIndex;    
}
int main(){


int n;
cout<<"Enter the number of elements: ";
cin>>n;

int arr[n];
for(int i = 0; i < n; i++)  
{

    cin>>arr[i];

}

int index = indexOfSmallestElements(arr, n);
cout << "Index of the smallest element: " << index << endl; 
cout<< "Smallest element: " << arr[index] << endl;
return 0;

}