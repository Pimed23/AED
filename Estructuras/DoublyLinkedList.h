#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

////////////////////////////////////////////////////////////////////
////////            CLASS DOUBLY LINKED LIST             ///////////
////////////////////////////////////////////////////////////////////

template < typename Type >
class DoublyLinkedList {
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

            friend class DoublyLinkedList<Type>;
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

            friend class DoublyLinkedList<Type>;
        };

    public:
        DoublyLinkedList();
        DoublyLinkedList( const DoublyLinkedList &otherList );
        DoublyLinkedList( DoublyLinkedList &&rhs );
        ~DoublyLinkedList();

        void clearList();
        void pushFront( const Type &data );
        void pushBack( const Type &data );
        void pushPosition( const Type &data, int pos );
        void printFList();
        void printBList();
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

    private:
        int size;
        Node *head = NULL;
        Node *last = NULL;

        void initList();
        void copyList( DoublyLinkedList &otherList );
};

////////////////////////////////////////////////////////////////////
////////                 STRUCT NODE                     ///////////
////////////////////////////////////////////////////////////////////

// Default Constructor
template < typename Type >
DoublyLinkedList<Type>::Node::Node() {
}

// Parameters Constructor
template < typename Type >
DoublyLinkedList<Type>::Node::Node( const Type &data, Node *n, Node *p ) {
    this -> data = data;
    this -> next = n;
    this -> prev = p;
}

// Move Constructor
template < typename Type >
DoublyLinkedList<Type>::Node::Node( Type &&data, Node *n, Node *p ) {
    this -> data = std::move( data );
    this -> next = n;
    this -> prev = p;
}

////////////////////////////////////////////////////////////////////
////////              CLASS CONST ITERATOR               ///////////
////////////////////////////////////////////////////////////////////

// Default constructor
template < typename Type >
DoublyLinkedList<Type>::const_Iterator::const_Iterator() {
    current = NULL;
}

// Retrieve Data
template < typename Type >
const Type& DoublyLinkedList<Type>::const_Iterator::operator*() const {
    return this -> retrieveData();
}

// Operator *
template < typename Type >
Type& DoublyLinkedList<Type>::const_Iterator::retrieveData() const {
    return current -> data;
}

// Operator ++ Pre - Increment
template < typename Type >
typename DoublyLinkedList<Type>::const_Iterator& DoublyLinkedList<Type>::const_Iterator::operator++() {
    current = current -> next;
    return *this;
}

// Operator + Increment
template < typename Type >
typename DoublyLinkedList<Type>::const_Iterator& DoublyLinkedList<Type>::const_Iterator::operator+( int n ) {
    const_Iterator *pos = this;
    for( int i = 0; i < n; ++i )
        pos -> current = pos -> current -> next;
    return *pos;
}

// Operator ++ Post - Increment
template < typename Type >
typename DoublyLinkedList<Type>::const_Iterator DoublyLinkedList<Type>::const_Iterator::operator++( int ) {
    const_Iterator old = *this;
    ++( *this );
    return old;
}

// Operator -- Pre - Decrement
template < typename Type >
typename DoublyLinkedList<Type>::const_Iterator& DoublyLinkedList<Type>::const_Iterator::operator--() {
    current = current -> prev;
    return *this;
}

// Operator - Decrement
template < typename Type >
typename DoublyLinkedList<Type>::const_Iterator& DoublyLinkedList<Type>::const_Iterator::operator-( int n ) {
    const_Iterator *pos = this;
    for( int i = 0; i < n; ++i )
        pos -> current = pos -> current -> prev;
    return *pos;
}

// Operator -- Post - Decrement
template < typename Type >
typename DoublyLinkedList<Type>::const_Iterator DoublyLinkedList<Type>::const_Iterator::operator--( int ) {
    const_Iterator old = *this;
    --( *this );
    return old;
}

// Operator == 
template < typename Type >
bool DoublyLinkedList<Type>::const_Iterator::operator==( const const_Iterator &rhs ) const {
    return current == rhs.current;
}

// Operator != 
template < typename Type >
bool DoublyLinkedList<Type>::const_Iterator::operator!=( const const_Iterator &rhs ) const {
    return !( *this == rhs );
}


////////////////////////////////////////////////////////////////////
////////                 CLASS ITERATOR                  ///////////
////////////////////////////////////////////////////////////////////

// Operator *
template < typename Type >
Type& DoublyLinkedList<Type>::Iterator::operator*() {
    return DoublyLinkedList<Type>::const_Iterator::retrieveData();
}

// Operator * const
template < typename Type >
const Type& DoublyLinkedList<Type>::Iterator::operator*() const {
    return DoublyLinkedList<Type>::const_Iterator::operator*();
}

// Operator ++ Pre - Increment
template < typename Type >
typename DoublyLinkedList<Type>::Iterator& DoublyLinkedList<Type>::Iterator::operator++() {
    DoublyLinkedList<Type>::const_Iterator::current = DoublyLinkedList<Type>::const_Iterator::current -> next;
    return *this;
}

// Operator ++ Post - Increment
template < typename Type >
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::Iterator::operator++( int ) {
    Iterator& old = *this;
    ++( *this );
    return old;
}

// Operator -- Pre - Decrement
template < typename Type >
typename DoublyLinkedList<Type>::Iterator& DoublyLinkedList<Type>::Iterator::operator--() {
    DoublyLinkedList<Type>::const_Iterator::current = DoublyLinkedList<Type>::const_Iterator::current -> prev;
    return *this;
}

// Operator -- Post - Decrement
template < typename Type >
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::Iterator::operator--( int ) {
    Iterator& old = *this;
    --( *this );
    return old;
}

////////////////////////////////////////////////////////////////////
////////            CLASS DOUBLY LINKED LIST             ///////////
////////////////////////////////////////////////////////////////////

// Default Constructor
template < typename Type >
DoublyLinkedList<Type>::DoublyLinkedList() {    
    this -> initList();
}

// Init Linked List
template < typename Type >
void DoublyLinkedList<Type>::initList() {
    size = 0;
    head = new Node;
}

// Copy Constructor
template < typename Type >
DoublyLinkedList<Type>::DoublyLinkedList( const DoublyLinkedList &otherList ) {
    this -> initList();
    for( auto &x : otherList )
        this -> pushBack( x );
    this -> pushBack( *( otherList.end()));
}

// Default Destructor
template < typename Type >
DoublyLinkedList<Type>::~DoublyLinkedList() {
    this -> clearList();
}

// Destroy Linked List
template < typename Type >
void DoublyLinkedList<Type>::clearList() {
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
void DoublyLinkedList<Type>::pushBack( const Type &data ) {
    if( last == NULL ) {
        head -> data = data;
        last = head;
    } else {
        Node *newNode = new Node( data );
        newNode -> prev = last;
        last -> next = newNode;
        last = newNode;
    }
    ++size;
}

// Insert a node at the front
template < typename Type >
void DoublyLinkedList<Type>::pushFront( const Type &data ) {
    if( last == NULL ) {
        head -> data = data;
        last = head;
    } else {
        Node *newNode = new Node( data );
        newNode -> next = head;
        head -> prev = newNode;
        head = newNode;
    }
    ++size;
}

// Insert a node in a position
template < typename Type >
void DoublyLinkedList<Type>::pushPosition( const Type &data, int pos ) {
    if( pos < 0 || pos >= size )
        std::cout << "Out of range..." << std::endl;
    else if( pos > 0 && pos < size ) {      
        Node *newNode = new Node( data );
        Node *temp = head;
        for( int i = 1; i < pos; ++i )
            temp = temp -> next;
        newNode -> next = temp -> next;
        newNode -> prev = temp;
        temp -> next -> prev = newNode;
        temp -> next = newNode;
        ++size;
    } else if( pos == 0 )
        this -> pushFront( data );
}

// Delete a node at the front
template < typename Type >
void DoublyLinkedList<Type>::deleteFront() {
    Node *temp = head;
    head = head -> next;
    delete temp;
    --size;
}

// Delete a node at the back
template < typename Type >
void DoublyLinkedList<Type>::deleteBack() {
    Node *temp = last;
    last = last -> prev;
    delete temp;
    --size;
}

// Delete a node in a position
template < typename Type >
void DoublyLinkedList<Type>::deletePosition( int pos ) {
    if( pos < 0 || pos >= size )
        std::cout << "Out of range..." << std::endl;
    else if( pos > 0 && pos < size - 1 ) {      
        Node *ante = head;
        Node *temp;
        for( int i = 1; i < pos; ++i )
            ante = ante -> next;
        temp = ante -> next;
        ante -> next = temp -> next;
        temp -> next -> prev = ante;
        delete temp;      
        --size;
    } else if( pos == 0 )
        this -> deleteFront();
    else if( pos == size - 1 )
        this -> deleteBack();
}

// Print all the elements in the list
template < typename Type >
void DoublyLinkedList<Type>::printFList() {
    DoublyLinkedList<Type>::Iterator it = this -> begin();
    for( ; it != this -> end(); ++it )
        std::cout << *it << " ";
    std::cout << *it << std::endl;
}

// Print all the elements in reverse
template < typename Type >
void DoublyLinkedList<Type>::printBList() {
    DoublyLinkedList<Type>::Iterator it = this -> end();
    for( ; it != this -> begin(); --it )
        std::cout << *it << " ";
    std::cout << *it << std::endl;
}

// Get the size of the list
template < typename Type >
int DoublyLinkedList<Type>::getSize() const {
    return size;
}


// backElement: Return the last element in the list
template < typename Type >
Type& DoublyLinkedList<Type>::backElement() { 
    return *end(); 
}

// frontElement: Return the first element in the list
template < typename Type >
Type& DoublyLinkedList<Type>::frontElement() {
    return *begin();
}

// const_Iterator begin
template < typename Type >
typename DoublyLinkedList<Type>::const_Iterator DoublyLinkedList<Type>::begin() const {
    return head;
}

// const_Iterator end
template < typename Type >
typename DoublyLinkedList<Type>::const_Iterator DoublyLinkedList<Type>::end() const {
    return last;
}

// Iterator begin
template < typename Type >
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::begin() {
    return head;
}

// Iterator end
template < typename Type >
typename DoublyLinkedList<Type>::Iterator DoublyLinkedList<Type>::end() {
    return last;
}


#endif