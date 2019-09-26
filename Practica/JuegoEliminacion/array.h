#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array {
    public:
        Array();
        Array( int *, int );
        Array( Array & );
        ~Array();        

        void pushBack( int );
        void remove( int );
        void print();

    private:
        int *arr;
        int size;
        void resize( int );
};

Array::Array() {
    this -> size = 0;
    this -> arr = new int[ size ];
}

Array::Array( int *arr, int size ) {
    this -> size = size;
    this -> arr = new int[ size ];

    for( int i = 0; i < size; ++i )
        this -> arr[ i ] = arr[ i ]; 

}

Array::Array( Array &A ) {
    this -> size = A.size;
    this -> arr = new int[ size ];

    for( int i = 0; i < size; ++i )
        this -> arr[ i ] = A.arr[ i ];
}

Array::~Array() {
    delete[] arr;
}

void Array::resize( int new_size ) {
    int *temp = new int[ new_size ];
    int minsize = ( size > new_size ) ? new_size : size;

    for( int i = 0; i < minsize; ++i )
        temp[ i ] = arr[ i ];
    
    delete[] arr;
    arr = temp;
    size = new_size;
}

void Array::pushBack( int data ) {
    resize( size + 1 );
    arr[ size - 1 ] = data; 
}

void Array::remove( int pos ) {
    for( int i = pos; i < size; ++i )
        arr[ i ] = arr[ i + 1 ];
    resize( size - 1 );
}

void Array::print() {
    for( int i = 0; i < size; ++i )
        std::cout << arr[ i ] << " ";
    std::cout << std::endl;
}


#endif 