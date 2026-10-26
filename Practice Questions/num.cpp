#include<iostream>
#include<new>
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
if(!(cin >> n) || n <= 0) {
    cout << "Number of elements must be positive." << endl;
    return 1;
}

int* arr = new (nothrow) int[n];
if(arr == nullptr) {
    cout << "Not enough memory." << endl;
    return 1;
}
for(int i = 0; i < n; i++)  
{

    if(!(cin >> arr[i])) {
        cout << "Invalid element." << endl;
        delete[] arr;
        return 1;
    }

}

int index = indexOfSmallestElements(arr, n);
cout << "Index of the smallest element: " << index << endl; 
cout<< "Smallest element: " << arr[index] << endl;
delete[] arr;
return 0;

}
