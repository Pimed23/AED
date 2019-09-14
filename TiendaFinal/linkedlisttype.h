#ifndef LINKEDLISTTYPE_H
#define LINKEDLISTTYPE_H

#include <iostream>
#include <QDebug>

template < typename Type >
struct nodeType {
    Type info;
    nodeType<Type> *link;
};

template < typename Type >
class linkedListIterator;

template < typename Type >
class linkedListType
{
    public:
        linkedListType();
        linkedListType( const linkedListType<Type> &otherList );
        ~linkedListType();

        const linkedListType<Type> &operator=( const linkedListType<Type> & );
        void initializeList();
        bool isEmptyList() const;
        void print() const;
        int lenght() const;
        void destroyList();
        Type front() const;
        Type back() const;

        virtual bool search( const Type& searchItem ) const = 0;
        virtual void insertFirst( const Type &newItem ) = 0;
        virtual void insertLast( const Type &newItem ) = 0;
        virtual void deleteNode( const Type &deleteItem ) = 0;

        linkedListIterator<Type> begin();
        linkedListIterator<Type> end();

    protected:
        int count;
        nodeType<Type> *first;
        nodeType<Type> *last;

    private:
        void copyList( const linkedListType<Type> &otherList );
};


template < typename Type >
linkedListIterator<Type> linkedListType<Type>::begin() {
    linkedListIterator<Type> temp( first );
    return temp;
}

template < typename Type >
linkedListIterator<Type> linkedListType<Type>::end() {
    linkedListIterator<Type> temp( NULL );
    return temp;
}

template < typename Type >
linkedListType<Type>::linkedListType() {
    first = NULL;
    last = NULL;
    count = 0;
}

template < typename Type >
linkedListType<Type>::linkedListType( const linkedListType<Type> &otherList ) {
    first = NULL;
    copyList( otherList );
}

template < typename Type >
linkedListType<Type>::~linkedListType() {
    destroyList();
}

template < typename Type >
const linkedListType<Type>& linkedListType<Type>::operator=( const linkedListType<Type> &otherList ) {
    if( this != &otherList )
        copyList( otherList );
    return *this;
}

template < typename Type >
void linkedListType<Type>::initializeList() {
    destroyList();
}

template < typename Type >
bool linkedListType<Type>::isEmptyList() const {
    return ( first == NULL );
}

template < typename Type >
void linkedListType<Type>::print() const {
    nodeType<Type> *current = first;
    while( current != NULL ) {
        qDebug() << current -> info << " ";
        current = current -> link;
    }
}

template < typename Type >
int linkedListType<Type>::lenght() const {
    return count;
}

template < typename Type >
void linkedListType<Type>::destroyList() {
    nodeType<Type> *temp;
    while( first != NULL ) {
        temp = first;
        first = first -> link;
        delete temp;
    }
    last = NULL;
    count = 0;
}

template < typename Type >
Type linkedListType<Type>::front() const {
    assert( first != NULL );
    return first -> info;
}

template < typename Type >
Type linkedListType<Type>::back() const {
    assert( last != NULL );
    return last -> info;
}

template < typename Type >
void linkedListType<Type>::copyList( const linkedListType<Type> &otherList ) {
    nodeType<Type> *newNode;
    nodeType<Type> *current;

    if( first != NULL )
        destroyList();

    if( otherList.first == NULL ) {
        first = NULL;
        last = NULL;
        count = 0;
    } else {
        current = otherList.first;
        count = otherList.count;

        first = new nodeType<Type>;
        first -> info = current -> info;
        first -> link = NULL;
        last = first;
        current = current -> link;

        while( current != NULL ) {
            newNode = new nodeType<Type>;
            newNode -> info = current -> info;
            newNode -> link = NULL;
            last -> link = newNode;
            last = newNode;
            current = current -> link;
        }
    }
}

template < typename Type >
class linkedListIterator
{
public:
        linkedListIterator();
        linkedListIterator( nodeType<Type> *ptr );

        Type operator*();
        linkedListIterator<Type> operator++();
        bool operator==( const linkedListIterator<Type> &right ) const;
        bool operator!=( const linkedListIterator<Type> &right ) const;
private:
        nodeType<Type> *current;
};

template < typename Type >
linkedListIterator<Type>::linkedListIterator() {
    current = NULL;
}

template < typename Type >
linkedListIterator<Type>::linkedListIterator( nodeType<Type> *ptr ) {
    current = ptr;
}

template < typename Type >
Type linkedListIterator<Type>::operator*() {
    return current -> info;
}

template < typename Type >
linkedListIterator<Type> linkedListIterator<Type>::operator++() {
    current = current -> link;
    return *this;
}

template < typename Type >
bool linkedListIterator<Type>::operator==( const linkedListIterator<Type> &right ) const {
    return ( current == right.current );
}

template < typename Type >
bool linkedListIterator<Type>::operator!=( const linkedListIterator<Type> &right ) const {
    return ( current != right.current );
}



#endif // LINKEDLISTTYPE_H
