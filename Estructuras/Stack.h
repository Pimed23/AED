#ifndef STACK_H
#define STACK_H

#include <iostream>

////////////////////////////////////////////////////////////////////
////////                    CLASS STACK                  ///////////
////////////////////////////////////////////////////////////////////

template < typename Type >
class Stack {
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

            friend class Stack<Type>;
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

            friend class Stack<Type>;
        };

    public:
        Stack();
        Stack( const Stack &otherList );
        Stack( Stack &&rhs );
        ~Stack();

        void empty();
        void push( const Type &data );
        void pop();
        void printStack();

        int getSize() const;
        
        Type& top();

        const_Iterator begin() const;
        const_Iterator end() const;
        Iterator begin();
        Iterator end();      

    private:
        int size;
        Node *head = NULL;
        Node *last = NULL;

        void initList();
        void copyList( Stack &otherList );
};

////////////////////////////////////////////////////////////////////
////////                 STRUCT NODE                     ///////////
////////////////////////////////////////////////////////////////////

// Default Constructor
template < typename Type >
Stack<Type>::Node::Node() {
}

// Parameters Constructor
template < typename Type >
Stack<Type>::Node::Node( const Type &data, Node *n, Node *p ) {
    this -> data = data;
    this -> next = n;
    this -> prev = p;
}

// Move Constructor
template < typename Type >
Stack<Type>::Node::Node( Type &&data, Node *n, Node *p ) {
    this -> data = std::move( data );
    this -> next = n;
    this -> prev = p;
}

////////////////////////////////////////////////////////////////////
////////              CLASS CONST ITERATOR               ///////////
////////////////////////////////////////////////////////////////////

// Default constructor
template < typename Type >
Stack<Type>::const_Iterator::const_Iterator() {
    current = NULL;
}

// Retrieve Data
template < typename Type >
const Type& Stack<Type>::const_Iterator::operator*() const {
    return this -> retrieveData();
}

// Operator *
template < typename Type >
Type& Stack<Type>::const_Iterator::retrieveData() const {
    return current -> data;
}

// Operator ++ Pre - Increment
template < typename Type >
typename Stack<Type>::const_Iterator& Stack<Type>::const_Iterator::operator++() {
    current = current -> next;
    return *this;
}

// Operator + Increment
template < typename Type >
typename Stack<Type>::const_Iterator& Stack<Type>::const_Iterator::operator+( int n ) {
    const_Iterator *pos = this;
    for( int i = 0; i < n; ++i )
        pos -> current = pos -> current -> next;
    return *pos;
}

// Operator ++ Post - Increment
template < typename Type >
typename Stack<Type>::const_Iterator Stack<Type>::const_Iterator::operator++( int ) {
    const_Iterator old = *this;
    ++( *this );
    return old;
}

// Operator -- Pre - Decrement
template < typename Type >
typename Stack<Type>::const_Iterator& Stack<Type>::const_Iterator::operator--() {
    current = current -> prev;
    return *this;
}

// Operator - Decrement
template < typename Type >
typename Stack<Type>::const_Iterator& Stack<Type>::const_Iterator::operator-( int n ) {
    const_Iterator *pos = this;
    for( int i = 0; i < n; ++i )
        pos -> current = pos -> current -> prev;
    return *pos;
}

// Operator -- Post - Decrement
template < typename Type >
typename Stack<Type>::const_Iterator Stack<Type>::const_Iterator::operator--( int ) {
    const_Iterator old = *this;
    --( *this );
    return old;
}

// Operator == 
template < typename Type >
bool Stack<Type>::const_Iterator::operator==( const const_Iterator &rhs ) const {
    return current == rhs.current;
}

// Operator != 
template < typename Type >
bool Stack<Type>::const_Iterator::operator!=( const const_Iterator &rhs ) const {
    return !( *this == rhs );
}


////////////////////////////////////////////////////////////////////
////////                 CLASS ITERATOR                  ///////////
////////////////////////////////////////////////////////////////////

// Operator *
template < typename Type >
Type& Stack<Type>::Iterator::operator*() {
    return Stack<Type>::const_Iterator::retrieveData();
}

// Operator * const
template < typename Type >
const Type& Stack<Type>::Iterator::operator*() const {
    return Stack<Type>::const_Iterator::operator*();
}

// Operator ++ Pre - Increment
template < typename Type >
typename Stack<Type>::Iterator& Stack<Type>::Iterator::operator++() {
    Stack<Type>::const_Iterator::current = Stack<Type>::const_Iterator::current -> next;
    return *this;
}

// Operator ++ Post - Increment
template < typename Type >
typename Stack<Type>::Iterator Stack<Type>::Iterator::operator++( int ) {
    Iterator& old = *this;
    ++( *this );
    return old;
}

// Operator -- Pre - Decrement
template < typename Type >
typename Stack<Type>::Iterator& Stack<Type>::Iterator::operator--() {
    Stack<Type>::const_Iterator::current = Stack<Type>::const_Iterator::current -> prev;
    return *this;
}

// Operator -- Post - Decrement
template < typename Type >
typename Stack<Type>::Iterator Stack<Type>::Iterator::operator--( int ) {
    Iterator& old = *this;
    --( *this );
    return old;
}

////////////////////////////////////////////////////////////////////
////////                    CLASS STACK                  ///////////
////////////////////////////////////////////////////////////////////

// Default Constructor
template < typename Type >
Stack<Type>::Stack() {    
    this -> initList();
}

// Init Stack
template < typename Type >
void Stack<Type>::initList() {
    size = 0;
    head = new Node;
}

// Copy Constructor
template < typename Type >
Stack<Type>::Stack( const Stack &otherList ) {
    this -> initList();
    for( auto &x : otherList )
        this -> pushBack( x );
    this -> pushBack( *( otherList.end()));
}

// Default Destructor
template < typename Type >
Stack<Type>::~Stack() {
    this -> empty();
}

// Destroy Stack
template < typename Type >
void Stack<Type>::empty() {
    Node *temp;
    while( head != NULL ) {
        temp = head;
        head = head -> next;
        delete temp;
    }
    last = NULL;
    size = 0; 
}

// Insert a node at the front
template < typename Type >
void Stack<Type>::push( const Type &data ) {
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

// Delete a node at the front
template < typename Type >
void Stack<Type>::pop() {
    Node *temp = head;
    head = head -> next;
    delete temp;
    --size;
}

// Print all the elements in the stack
template < typename Type >
void Stack<Type>::printStack() {
    Stack<Type>::Iterator it = this -> begin();
    for( ; it != this -> end(); ++it )
        std::cout << *it << " ";
    std::cout << *it << std::endl;
}

// Get the size of the stack
template < typename Type >
int Stack<Type>::getSize() const {
    return size;
}

// frontElement: Return the first element in the stack
template < typename Type >
Type& Stack<Type>::top() {
    return *begin();
}

// const_Iterator begin
template < typename Type >
typename Stack<Type>::const_Iterator Stack<Type>::begin() const {
    return head;
}

// const_Iterator end
template < typename Type >
typename Stack<Type>::const_Iterator Stack<Type>::end() const {
    return last;
}

// Iterator begin
template < typename Type >
typename Stack<Type>::Iterator Stack<Type>::begin() {
    return head;
}

// Iterator end
template < typename Type >
typename Stack<Type>::Iterator Stack<Type>::end() {
    return last;
}


#endif