#ifndef BINHEAP_H
#define BINHEAP_H

#include <iostream>
#include <vector>
#include <utility>

template < typename Type >
class BinHeap {     
    public:
        int getSize(); 
        bool empty();        
        void insert( Type elem );
        void deleteMax();
        Type maxElement();

    private:
        std::vector<int> heap;
        int getParent( int ind );
        int getLeft( int ind );
        int getRight( int ind );
        void heapifyDown( int ind );
        void heapifyUp( int ind );
};

template < typename Type >
int BinHeap<Type>::getSize() {
    return heap.size();
}

template < typename Type >
bool BinHeap<Type>::empty() {
    return ( heap.size() == 0 );
}

template < typename Type >
void BinHeap<Type>::insert( Type elem ) {
    heap.push_back( elem );
    heapifyUp( heap.size() - 1 );
}

template < typename Type >
void BinHeap<Type>::deleteMax() {
    if( heap.size() == 0 )
        std::cout << "The heap is empty!!! ( Underflow )" << std::endl;
    
    else {
        heap[ 0 ] = heap.back();
        heap.pop_back();
        heapifyDown( 0 ); 
    }
}

template < typename Type >
Type BinHeap<Type>::maxElement() {
    if( heap.size() == 0 )
        std::cout << "The heap is empty!!!" << std::endl;
    
    else
        return heap[ 0 ];
}

template < typename Type >
int BinHeap<Type>::getParent( int ind ) { 
    return ( ind - 1 ) / 2; 
}

template < typename Type >
int BinHeap<Type>::getLeft( int ind ) {
    int left = 2 * ind + 1;
    if( left < heap.size())
        return left;
    else
        return -1;
}

template < typename Type >
int BinHeap<Type>::getRight( int ind ) { 
    int right = 2 * ind + 2;
    if( right < heap.size())
        return right;
    else
        return -1;
}

template < typename Type >
void BinHeap<Type>::heapifyDown( int ind ) {
    int left = getLeft( ind );
    int right = getRight( ind );
    int largest = ind;

    if( left >= 0 && heap[ left ] > heap[ ind ])
        largest = left;

    if( right >= 0 && heap[ right ] > heap[ largest ])
        largest = right;

    if( largest != ind ) {
        std::swap( heap[ ind ], heap[ largest ]);
        heapifyDown( largest );
    }
}

template < typename Type >
void BinHeap<Type>::heapifyUp( int ind ) {
    if( ind && heap[ getParent( ind )] < heap[ ind ]) {
        std::swap( heap[ ind ], heap[ getParent( ind )]);
        heapifyUp( getParent( ind ));
    }
}

#endif