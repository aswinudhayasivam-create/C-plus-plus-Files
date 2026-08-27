#include<iostream>
using namespace std;

template <class X> void bubble(X *items , int count )
{
    register int a , b ;
    X t;

    for ( a = 1 ; a < count ; a++ )
        for ( b = count - 1 ; b >= a ; b-- )
            if ( items[b-1] > items[b] ) {
                t = items[b-1] ;
                items[b-1] = items[b] ;
                items[b] = t ;
            }
}

int main()
{
    int iarray[7] = { 64, 34, 25, 12, 22, 11, 90 } ;
    double darray[5] = { 64.5, 34.2, 25.1, 12.3, 22.4 } ;

    int i;
    cout << "Integer array before sorting: \n" ;
    for ( i = 0 ; i < 7 ; i++ )
        cout << iarray[i] << " " ;
    cout << endl ;  

    cout << "Double array before sorting: \n" ;
    for ( i = 0 ; i < 5 ; i++ )
        cout << darray[i] << " " ;
    cout << endl ;
    bubble(iarray, 7) ;
    bubble(darray, 5) ;
    cout << "Double array after sorting: \n" ;
    for ( i = 0 ; i < 5 ; i++ )
        cout << darray[i] << " " ;
    cout << endl ;
    cout << "Integer array after sorting: \n" ;
    for ( i = 0 ; i < 7 ; i++ )
        cout << iarray[i] << " " ;  
    cout << endl ;
    return 0 ;
    
}