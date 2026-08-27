#include<iostream>
#include<fstream>
using namespace std;

int main() {

    int arr[5] = {1, 2, 3, 4, 5};

        ofstream fout("C:\\Users\\TEST\\data.bin", ios::binary);

        fout.write(reinterpret_cast<char*>(arr), sizeof(arr));

    fout.close();
    cout<<"Data written to binary file successfully!"<<endl;
    for(int i=0; i<5; i++) {
        cout<<arr[i]<<" ";
    }
        cout<<endl;
    system("pause"); // This forces Windows to keep the window open!
    return 0;
}
