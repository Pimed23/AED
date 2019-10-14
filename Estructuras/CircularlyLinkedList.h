#ifndef CIRCULARLYLINKEDLIST_H
#define CIRCULARLYLINKEDLIST_H

#include <iostream>

////////////////////////////////////////////////////////////////////
////////          CLASS CIRCULARLY LINKED LIST           ///////////
////////////////////////////////////////////////////////////////////

template < typename Type >
class CircularlyLinkedList {
    private:
        struct Node { 
            Type data;
            Node* next;
            Node* prev;
            
            Node();
            Node( const Type &data, Node *n = NULL, Node *p = NULL );
            Node( Type &&data, Node *n = NULL, Node *p = NULL );
        };
    
    public:
        class const_Iterator {
            public:
                const_Iterator();

                const Type& operator*() const;
                const_Iterator& operator++();
                const_Iterator& operator+( int n );
                const_Iterator operator++( int );
                const_Iterator& operator--();
                const_Iterator& operator-( int n );
                const_Iterator operator--( int );
                bool operator==( const const_Iterator &rhs ) const;
                bool operator!=( const const_Iterator &rhs ) const;

            protected:
                Node *current;
                Type& retrieveData() const;
                const_Iterator( Node *p ) : current( p ) {} 

            friend class CircularlyLinkedList<Type>;
        };

        class Iterator : public const_Iterator {
            public:
                Iterator() {}

                Type& operator*();
                const Type& operator*() const;
                Iterator& operator++();
                Iterator operator++( int );
                Iterator& operator--();
                Iterator operator--( int );

            protected:
                Iterator( Node *p ) : const_Iterator( p ) {}

            friend class CircularlyLinkedList<Type>;
        };

    public:
        CircularlyLinkedList();
        CircularlyLinkedList( const CircularlyLinkedList &otherList );
        CircularlyLinkedList( CircularlyLinkedList &&rhs );
        ~CircularlyLinkedList();

        void clearList();
        void pushCurrent( const Type &data );
        void printFList();
        void printBList();
        void deleteCurrent();
        void deleteIterator( Iterator it );

        int getSize() const;
        
        Type& currentElement();

        const_Iterator currentPos() const;
        const_Iterator currentNext() const;
        Iterator currentPos();
        Iterator currentNext();

    private:
        int size;
        Node *curr;

        void initList();
        void copyList( CircularlyLinkedList &otherList );
};

////////////////////////////////////////////////////////////////////
////////                 STRUCT NODE                     ///////////
////////////////////////////////////////////////////////////////////

// Default Constructor
template < typename Type >
CircularlyLinkedList<Type>::Node::Node() {
}

// Parameters Constructor
template < typename Type >
CircularlyLinkedList<Type>::Node::Node( const Type &data, Node *n, Node *p ) {
    this -> data = data;
    this -> next = n;
    this -> prev = p;
}

// Move Constructor
template < typename Type >
CircularlyLinkedList<Type>::Node::Node( Type &&data, Node *n, Node *p ) {
    this -> data = std::move( data );
    this -> next = n;
    this -> prev = p;
}

////////////////////////////////////////////////////////////////////
////////              CLASS CONST ITERATOR               ///////////
////////////////////////////////////////////////////////////////////

// Default constructor
template < typename Type >
CircularlyLinkedList<Type>::const_Iterator::const_Iterator() {
    current = NULL;
}

// Retrieve Data
template < typename Type >
const Type& CircularlyLinkedList<Type>::const_Iterator::operator*() const {
    return this -> retrieveData();
}

// Operator *
template < typename Type >
Type& CircularlyLinkedList<Type>::const_Iterator::retrieveData() const {
    return current -> data;
}

// Operator ++ Pre - Increment
template < typename Type >
typename CircularlyLinkedList<Type>::const_Iterator& CircularlyLinkedList<Type>::const_Iterator::operator++() {
    current = current -> next;
    return *this;
}

// Operator + Increment
template < typename Type >
typename CircularlyLinkedList<Type>::const_Iterator& CircularlyLinkedList<Type>::const_Iterator::operator+( int n ) {
    const_Iterator *pos = this;
    for( int i = 0; i < n; ++i )
        pos -> current = pos -> current -> next;
    return *pos;
}

// Operator ++ Post - Increment
template < typename Type >
typename CircularlyLinkedList<Type>::const_Iterator CircularlyLinkedList<Type>::const_Iterator::operator++( int ) {
    const_Iterator old = *this;
    ++( *this );
    return old;
}

// Operator -- Pre - Decrement
template < typename Type >
typename CircularlyLinkedList<Type>::const_Iterator& CircularlyLinkedList<Type>::const_Iterator::operator--() {
    current = current -> prev;
    return *this;
}

// Operator - Decrement
template < typename Type >
typename CircularlyLinkedList<Type>::const_Iterator& CircularlyLinkedList<Type>::const_Iterator::operator-( int n ) {
    const_Iterator *pos = this;
    for( int i = 0; i < n; ++i )
        pos -> current = pos -> current -> prev;
    return *pos;
}

// Operator -- Post - Decrement
template < typename Type >
typename CircularlyLinkedList<Type>::const_Iterator CircularlyLinkedList<Type>::const_Iterator::operator--( int ) {
    const_Iterator old = *this;
    --( *this );
    return old;
}

// Operator == 
template < typename Type >
bool CircularlyLinkedList<Type>::const_Iterator::operator==( const const_Iterator &rhs ) const {
    return current == rhs.current;
}

// Operator != 
template < typename Type >
bool CircularlyLinkedList<Type>::const_Iterator::operator!=( const const_Iterator &rhs ) const {
    return !( *this == rhs );
}


////////////////////////////////////////////////////////////////////
////////                 CLASS ITERATOR                  ///////////
////////////////////////////////////////////////////////////////////

// Operator *
template < typename Type >
Type& CircularlyLinkedList<Type>::Iterator::operator*() {
    return CircularlyLinkedList<Type>::const_Iterator::retrieveData();
}

// Operator * const
template < typename Type >
const Type& CircularlyLinkedList<Type>::Iterator::operator*() const {
    return CircularlyLinkedList<Type>::const_Iterator::operator*();
}

// Operator ++ Pre - Increment
template < typename Type >
typename CircularlyLinkedList<Type>::Iterator& CircularlyLinkedList<Type>::Iterator::operator++() {
    CircularlyLinkedList<Type>::const_Iterator::current = CircularlyLinkedList<Type>::const_Iterator::current -> next;
    return *this;
}

// Operator ++ Post - Increment
template < typename Type >
typename CircularlyLinkedList<Type>::Iterator CircularlyLinkedList<Type>::Iterator::operator++( int ) {
    Iterator& old = *this;
    ++( *this );
    return old;
}

// Operator -- Pre - Decrement
template < typename Type >
typename CircularlyLinkedList<Type>::Iterator& CircularlyLinkedList<Type>::Iterator::operator--() {
    CircularlyLinkedList<Type>::const_Iterator::current = CircularlyLinkedList<Type>::const_Iterator::current -> prev;
    return *this;
}

// Operator -- Post - Decrement
template < typename Type >
typename CircularlyLinkedList<Type>::Iterator CircularlyLinkedList<Type>::Iterator::operator--( int ) {
    Iterator& old = *this;
    --( *this );
    return old;
}

////////////////////////////////////////////////////////////////////
////////           CLASS CIRCULARLY LINKED LIST          ///////////
////////////////////////////////////////////////////////////////////

// Default Constructor
template < typename Type >
CircularlyLinkedList<Type>::CircularlyLinkedList() {    
    this -> initList();
}

// Init Linked List
template < typename Type >
void CircularlyLinkedList<Type>::initList() {
    size = 0;
    curr = new Node;
    curr -> next = curr;
    curr -> prev = curr;
}

// Copy Constructor
template < typename Type >
CircularlyLinkedList<Type>::CircularlyLinkedList( const CircularlyLinkedList &otherList ) {
    this -> initList();
    for( auto &x : otherList )
        this -> pushBack( x );
    this -> pushBack( *( otherList.end()));
}

// Default Destructor
template < typename Type >
CircularlyLinkedList<Type>::~CircularlyLinkedList() {
    this -> clearList();
}

// Destroy Linked List
template < typename Type >
void CircularlyLinkedList<Type>::clearList() {
    while( curr -> next != curr ) {
        this -> deleteCurrent();
    }
    delete curr;
}

// Insert a node at the end
template < typename Type >
void CircularlyLinkedList<Type>::pushCurrent( const Type &data ) {
    if( size == 0 ) {
        curr -> data = data;
    } else {
        Node *newNode = new Node( data );
        newNode -> prev = curr;
        newNode -> next = curr -> next;
        curr -> next -> prev = newNode;
        curr -> next = newNode;
        curr = curr -> next;
    }
    ++size;
}

// Delete a node at the front
template < typename Type >
void CircularlyLinkedList<Type>::deleteCurrent() {
    if( curr -> next == curr )
        delete curr;
    else {
        Node *temp = curr -> prev;
        temp -> next = curr -> next;
        curr -> next -> prev = temp;
        delete curr;
        curr = temp;
    }
    --size;
}

// Delete a node at the front
template < typename Type >
void CircularlyLinkedList<Type>::deleteIterator( CircularlyLinkedList<Type>::Iterator it ) {
    CircularlyLinkedList<Type>::Iterator i = currentPos();
    while( i != it ) {
        curr = curr -> next;
        i = currentPos();
    }
    this -> deleteCurrent();
}

// Print all the elements in the list
template < typename Type >
void CircularlyLinkedList<Type>::printFList() {
    CircularlyLinkedList<Type>::Iterator it = this -> currentPos();
    ++it;
    for( ; it != this -> currentPos(); ++it )
        std::cout << *it << " ";
    std::cout << *it << std::endl;
}

// Print all the elements in reverse
template < typename Type >
void CircularlyLinkedList<Type>::printBList() {
    CircularlyLinkedList<Type>::Iterator it = this -> currentPos();
    std::cout << *it << " ";
    --it;
    for( ; it != this -> currentPos(); --it )
        std::cout << *it << " ";
    std::cout << std:: endl;
}

// Get the size of the list
template < typename Type >
int CircularlyLinkedList<Type>::getSize() const {
    return size;
}


// Return the current element
template < typename Type >
Type& CircularlyLinkedList<Type>::currentElement() { 
    return *currentPos(); 
}

// const_Iterator current
template < typename Type >
typename CircularlyLinkedList<Type>::const_Iterator CircularlyLinkedList<Type>::currentPos() const {
    return curr;
}

// Iterator current next
template < typename Type >
typename CircularlyLinkedList<Type>::const_Iterator CircularlyLinkedList<Type>::currentNext() const {
    return curr -> next;
}

// Iterator current
template < typename Type >
typename CircularlyLinkedList<Type>::Iterator CircularlyLinkedList<Type>::currentPos() {
    return curr;
}

// Iterator current next
template < typename Type >
typename CircularlyLinkedList<Type>::Iterator CircularlyLinkedList<Type>::currentNext() {
    return curr -> next;
}

#endif