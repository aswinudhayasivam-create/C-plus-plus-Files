#include<iostream>
using namespace std;

class IndexException {
    public:
    void message() {
        cout<<"Error: Index out of range!"<<endl;

    }
};

class Matrix {
    int rows, cols;
    int **arr;

    public:

    Matrix(int r,int c){
        rows = r;
        cols = c;

        try {
            arr = new int*[rows];
            for(int i=0; i<rows;i++){
                arr[i] = new int[cols];

            }
        }
        catch(bad_alloc) {
            cout<<"Memory allocation failed!"<<endl;
            
        }   
    }
    void input() {
        cout<<"Enter the elements of the matrix:"<<endl;
        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                cin>>arr[i][j];
            }
        }
    }
    void boundaryElements(){
        cout<<"Boundary elements of the matrix are:"<<endl;
        for(int i=0; i<rows; i++) {
            for(int j=0; j<cols; j++) {
                if(i==0 || i==rows-1 || j==0 || j==cols-1) {
                    cout<<arr[i][j]<<" ";
                }
            }
            cout<<endl;
        }
    }

    void accessElement(int r, int c) {
        try {
            if(r<0 || r>=rows || c<0 || c>=cols) {
                throw IndexException();
            }
            cout<<"Element at ("<<r<<","<<c<<") is: "<<arr[r][c]<<endl;
        }
        catch(IndexException e) {
            e.message();
        }
    }

    ~Matrix() {
        for(int i=0; i<rows; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
};

int main() {
    int r, c;
    cout<<"Enter the number of rows and columns: ";
    cin>>r>>c;

    Matrix mat(r,c);
    mat.input();
    mat.boundaryElements();

    int accessRow, accessCol;
    cout<<"Enter the row and column to access an element: ";
    cin>>accessRow>>accessCol;
    mat.accessElement(accessRow, accessCol);

    return 0;
}

