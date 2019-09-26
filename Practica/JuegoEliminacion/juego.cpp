#include "array.h"
#include <iostream>
using namespace std;

int main() {
    Array A;
    int M, N;
    cout << "M: ";
    cin >> M;
    cout << "N: ";
    cin >> N;

    for( int i = 0; i < N; ++i )
        A.pushBack( i + 1 );
    
    A.print();
    int ind = M, ant = 0, mod;

    if( M >= N ) {
        while( N > 1 ) {
            mod = M % N;
            ind = mod + ant;
            ant = mod;
            if( ind >= N )
                ind = ind - N;
            A.remove( ind );
            A.print();
            --N;
        }
    } else {
        A.remove( ind );
        A.print();
        --N;
        while( N > 1 ) {
            ind = ind + M;
            if( ind >= N )
                ind = ind - N;
            A.remove( ind );
            A.print();
            --N;
        }
    }

    return 0;
}