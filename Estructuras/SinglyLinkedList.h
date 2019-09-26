#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>

////////////////////////////////////////////////////////////////////
////////            CLASS SINGLY LINKED LIST             ///////////
////////////////////////////////////////////////////////////////////

template < typename Type >
class SinglyLinkedList {
    private:
        struct Node { 
            Type data;
            Node* next;
            
            Node();
            Node( const Type &data, Node *n = NULL );
            Node( Type &&data, Node *n = NULL );
        };
    
    public:
        class const_Iterator {
            public:
                const_Iterator();

                const Type& operator*() const;
                const_Iterator& operator++();
                const_Iterator& operator+( int n );
                const_Iterator operator++( int );
                bool operator==( const const_Iterator &rhs ) const;
                bool operator!=( const const_Iterator &rhs ) const;

            protected:
                Node *current;
                Type& retrieveData() const;
                const_Iterator( Node *p ) : current( p ) {} 

            friend class SinglyLinkedList<Type>;
        };

        class Iterator : public const_Iterator {
            public:
                Iterator() {}

                Type& operator*();
                const Type& operator*() const;
                Iterator& operator++();
                Iterator operator++( int );

            protected:
                Iterator( Node *p ) : const_Iterator( p ) {}

            friend class SinglyLinkedList<Type>;
        };

    public:
        SinglyLinkedList();
        SinglyLinkedList( const SinglyLinkedList &otherList );
        SinglyLinkedList( SinglyLinkedList &&rhs );
        ~SinglyLinkedList();

        void clearList();
        void pushFront( const Type &data );
        void pushBack( const Type &data );
        void pushPosition( const Type &data, int pos );
        void printList();
        void deleteFront();
        void deleteBack();
        void deletePosition( int pos );

        int getSize() const;
        
        Type& backElement();
        Type& frontElement();       

        const_Iterator begin() const;
        const_Iterator end() const;
        Iterator begin();
        Iterator end();      

        Iterator insert( Iterator it, const Type &data );
        Iterator insert( Iterator it, Type &&data );

    private:
        int size;
        Node *head = NULL;
        Node *last = NULL;

        void initList();
        void copyList( SinglyLinkedList &otherList );
};

////////////////////////////////////////////////////////////////////
////////                 STRUCT NODE                     ///////////
////////////////////////////////////////////////////////////////////

// Default Constructor
template < typename Type >
SinglyLinkedList<Type>::Node::Node() {
}

// Parameters Constructor
template < typename Type >
SinglyLinkedList<Type>::Node::Node( const Type &data, Node *n ) {
    this -> data = data;
    this -> next = n;
}

// Move Constructor
template < typename Type >
SinglyLinkedList<Type>::Node::Node( Type &&data, Node *n ) {
    this -> data = std::move( data );
    this -> next = n;
}

////////////////////////////////////////////////////////////////////
////////              CLASS CONST ITERATOR               ///////////
////////////////////////////////////////////////////////////////////

// Default constructor
template < typename Type >
SinglyLinkedList<Type>::const_Iterator::const_Iterator() {
    current = NULL;
}

// Retrieve Data
template < typename Type >
const Type& SinglyLinkedList<Type>::const_Iterator::operator*() const {
    return this -> retrieveData();
}

// Operator *
template < typename Type >
Type& SinglyLinkedList<Type>::const_Iterator::retrieveData() const {
    return current -> data;
}

// Operator ++ Pre - Increment
template < typename Type >
typename SinglyLinkedList<Type>::const_Iterator& SinglyLinkedList<Type>::const_Iterator::operator++() {
    current = current -> next;
    return *this;
}

// Operator + Increment
template < typename Type >
typename SinglyLinkedList<Type>::const_Iterator& SinglyLinkedList<Type>::const_Iterator::operator+( int n ) {
    const_Iterator *pos = this;
    for( int i = 0; i < n; ++i )
        pos -> current = pos -> current -> next;
    return *pos;
}

// Operator ++ Post - Increment
template < typename Type >
typename SinglyLinkedList<Type>::const_Iterator SinglyLinkedList<Type>::const_Iterator::operator++( int ) {
    const_Iterator old = *this;
    ++( *this );
    return old;
}

// Operator == 
template < typename Type >
bool SinglyLinkedList<Type>::const_Iterator::operator==( const const_Iterator &rhs ) const {
    return current == rhs.current;
}

// Operator != 
template < typename Type >
bool SinglyLinkedList<Type>::const_Iterator::operator!=( const const_Iterator &rhs ) const {
    return !( *this == rhs );
}


////////////////////////////////////////////////////////////////////
////////                 CLASS ITERATOR                  ///////////
////////////////////////////////////////////////////////////////////

// Operator *
template < typename Type >
Type& SinglyLinkedList<Type>::Iterator::operator*() {
    return SinglyLinkedList<Type>::const_Iterator::retrieveData();
}

// Operator * const
template < typename Type >
const Type& SinglyLinkedList<Type>::Iterator::operator*() const {
    return SinglyLinkedList<Type>::const_Iterator::operator*();
}

// Operator ++ Pre - Increment
template < typename Type >
typename SinglyLinkedList<Type>::Iterator& SinglyLinkedList<Type>::Iterator::operator++() {
    SinglyLinkedList<Type>::const_Iterator::current = SinglyLinkedList<Type>::const_Iterator::current -> next;
    return *this;
}

// Operator ++ Post - Increment
template < typename Type >
typename SinglyLinkedList<Type>::Iterator SinglyLinkedList<Type>::Iterator::operator++( int ) {
    Iterator& old = *this;
    ++( *this );
    return old;
}

////////////////////////////////////////////////////////////////////
////////            CLASS SINGLY LINKED LIST             ///////////
////////////////////////////////////////////////////////////////////

// Default Constructor
template < typename Type >
SinglyLinkedList<Type>::SinglyLinkedList() {    
    this -> initList();
}

// Init Linked List
template < typename Type >
void SinglyLinkedList<Type>::initList() {
    size = 0;
    head = new Node;
}

// Copy Constructor
template < typename Type >
SinglyLinkedList<Type>::SinglyLinkedList( const SinglyLinkedList &otherList ) {
    this -> initList();
    for( auto &x : otherList )
        this -> pushBack( x );
}

// Default Destructor
template < typename Type >
SinglyLinkedList<Type>::~SinglyLinkedList() {
    this -> clearList();
}

// Destroy Linked List
template < typename Type >
void SinglyLinkedList<Type>::clearList() {
    Node *temp;
    while( head != NULL ) {
        temp = head;
        head = head -> next;
        delete temp;
    }
    last = NULL;
    size = 0; 
}

// Insert a node at the end
template < typename Type >
void SinglyLinkedList<Type>::pushBack( const Type &data ) {
    if( last == NULL ) {
        head -> data = data;
        last = head;
    } else {
        Node *newNode = new Node( data );
        last -> next = newNode;
        last = newNode;
    }
    ++size;
}

// Insert a node at the front
template < typename Type >
void SinglyLinkedList<Type>::pushFront( const Type &data ) {
    if( last == NULL ) {
        head -> data = data;
        last = head;
    } else {
        Node *newNode = new Node( data );
        newNode -> next = head;
        head = newNode;
    }
    ++size;
}

// Insert a node in a position
template < typename Type >
void SinglyLinkedList<Type>::pushPosition( const Type &data, int pos ) {
    if( pos < 0 || pos >= size )
        std::cout << "Out of range..." << std::endl;
    else if( pos > 0 && pos < size ) {      
        Node *newNode = new Node( data );
        Node *temp = head;
        for( int i = 1; i < pos; ++i )
            temp = temp -> next;
        newNode -> next = temp -> next;
        temp -> next = newNode;
        ++size;
    } else if( pos == 0 )
        this -> pushFront( data );
}

// Delete a node at the front
template < typename Type >
void SinglyLinkedList<Type>::deleteFront() {
    Node *temp = head;
    head = head -> next;
    delete temp;
    --size;
}

// Delete a node at the back
template < typename Type >
void SinglyLinkedList<Type>::deleteBack() {
    Node *temp = head;
    while( temp -> next != last )
        temp = temp -> next;
    delete last;
    last = temp;
    --size;
}

// Delete a node in a position
template < typename Type >
void SinglyLinkedList<Type>::deletePosition( int pos ) {
    if( pos < 0 || pos >= size )
        std::cout << "Out of range..." << std::endl;
    else if( pos > 0 && pos < size - 1 ) {      
        Node *prev = head;
        Node *temp;
        for( int i = 1; i < pos; ++i )
            prev = prev -> next;
        temp = prev -> next;
        prev -> next = temp -> next;
        delete temp;      
        --size;
    } else if( pos == 0 )
        this -> deleteFront();
    else if( pos == size - 1 )
        this -> deleteBack();
}

// Print all the elements in the list
template < typename Type >
void SinglyLinkedList<Type>::printList() {
    SinglyLinkedList<Type>::Iterator it = this -> begin();
    for( ; it != this -> end(); ++it )
        std::cout << *it << " ";
    std::cout << *it << std::endl;
}

// Get the size of the list
template < typename Type >
int SinglyLinkedList<Type>::getSize() const {
    return size;
}


// backElement: Return the last element in the list
template < typename Type >
Type& SinglyLinkedList<Type>::backElement() { 
    return *end(); 
}

template < typename Type >
Type& SinglyLinkedList<Type>::frontElement() {
    return *begin();
}

// const_Iterator begin
template < typename Type >
typename SinglyLinkedList<Type>::const_Iterator SinglyLinkedList<Type>::begin() const {
    return head;
}

// const_Iterator end
template < typename Type >
typename SinglyLinkedList<Type>::const_Iterator SinglyLinkedList<Type>::end() const {
    return last;
}

// Iterator begin
template < typename Type >
typename SinglyLinkedList<Type>::Iterator SinglyLinkedList<Type>::begin() {
    return head;
}

// Iterator end
template < typename Type >
typename SinglyLinkedList<Type>::Iterator SinglyLinkedList<Type>::end() {
    return last;
}


#endif