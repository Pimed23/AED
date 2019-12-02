#ifndef BINHEAP_H
#define BINHEAP_H

#include <iostream>
#include <vector>
#include <utility>
#include <QDebug>

template < typename Type >
class BinHeap {
    public:
        int getSize();
        bool empty();
        void insert( Type elem );
        void deleteMax();
        Type maxElement();
        void convert();
        void clear();
        std::vector<Type>& getHeapArray();

    private:
        std::vector<int> heap;
        bool control = false;
        int getParent( int ind );
        int getLeft( int ind );
        int getRight( int ind );
        void heapifyDownMax( size_t ind );
        void heapifyDownMin( size_t ind );
        void heapifyUpMax( size_t ind );
        void heapifyUpMin( size_t ind );
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
    if( control == false ) {
        heap.push_back( elem );
        heapifyUpMax( heap.size() - 1 );
    } else {
        heap.push_back( elem );
        heapifyUpMin( heap.size() - 1 );
    }
}

template < typename Type >
void BinHeap<Type>::deleteMax() {
    if( heap.size() == 0 )
        std::cout << "The heap is empty!!! ( Underflow )" << std::endl;

    else {
        if( control == false ) {
            heap[ 0 ] = heap.back();
            heap.pop_back();
            heapifyDownMax( 0 );
        } else {
            heap[ 0 ] = heap.back();
            heap.pop_back();
            heapifyDownMin( 0 );
        }
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
void BinHeap<Type>::heapifyDownMax( size_t ind ) {
    int left = getLeft( ind );
    int right = getRight( ind );
    int largest = ind;

    if( left >= 0 && heap[ left ] > heap[ ind ])
        largest = left;

    if( right >= 0 && heap[ right ] > heap[ largest ])
        largest = right;

    if( largest != ind ) {
        std::swap( heap[ ind ], heap[ largest ]);
        heapifyDownMax( largest );
    }
}


template < typename Type >
void BinHeap<Type>::heapifyDownMin( size_t ind ) {
    int left = getLeft( ind );
    int right = getRight( ind );
    int smallest = ind;

    if( left < heap.size() && heap[ left ] < heap[ ind ])
        smallest = left;

    if( right < heap.size() && heap[ right ] < heap[ smallest ])
        smallest = right;

    if( smallest != ind ) {
        std::swap( heap[ ind ], heap[ smallest ]);
        heapifyDownMin( smallest );
    }
}

template < typename Type >
void BinHeap<Type>::heapifyUpMax( size_t ind ) {
    if( ind && heap[ getParent( ind )] < heap[ ind ]) {
        std::swap( heap[ ind ], heap[ getParent( ind )]);
        heapifyUpMax( getParent( ind ));
    }
}

template < typename Type >
void BinHeap<Type>::heapifyUpMin( size_t ind ) {
    if( ind && heap[ getParent( ind )] > heap[ ind ]) {
        std::swap( heap[ ind ], heap[ getParent( ind )]);
        heapifyUpMin( getParent( ind ));
    }
}

template < typename Type >
std::vector<Type>& BinHeap<Type>::getHeapArray() {
    return heap;
}

template < typename Type >
void BinHeap<Type>::convert() {
    if( control == false ) {
        int i = ( heap.size() - 1 ) / 2;
        while( i >= 0 ) {
            heapifyDownMin( i-- );
        }
        control = true;
        qDebug() << "Entro To Min";
    } else {
        int i = ( heap.size() - 1 ) / 2;
        while( i >= 0 ) {
            heapifyDownMax( i-- );
        }
        control = false;
        qDebug() << "Entro To Max";
    }

}

template < typename Type >
void BinHeap<Type>::clear() {
    heap.clear();
}



#endif // BINHEAP_H
