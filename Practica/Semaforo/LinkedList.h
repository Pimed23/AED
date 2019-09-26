#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template < typename Type >
struct NodeType
{
    Type data;
    NodeType<Type> *next = NULL;
};

template < typename Type >
class LinkedList {
    public:
        LinkedList();
        LinkedList( const LinkedList<Type> &otherList );
        ~LinkedList();

        void insertLast( const Type &data );
        void printList() const;
        void destroyList();
        Type back() const;

    protected:
        int size;
        NodeType<Type> *head;
        NodeType<Type> *tail;

    private:
        void copyList( const LinkedList<Type> &otherList );
};

template < typename Type >
LinkedList<Type>::LinkedList() {
    head = NULL;
    tail = NULL;
    size = 0;
}

template < typename Type >
LinkedList<Type>::LinkedList( const LinkedList &otherList ) {
    head = NULL;
    tail = NULL;
    copyList( otherList );
}

template < typename Type >
LinkedList<Type>::~LinkedList() {
    this -> destroyList();
}

template < typename Type >
void LinkedList<Type>::destroyList() {
    NodeType<Type> *temp;
    while( head != NULL ) {
        temp = head;
        head = head -> next;
        delete temp;
    }
    tail = NULL;
    size = 0;
}

template < typename Type >
void LinkedList<Type>::insertLast( const Type &data ) {
    NodeType<Type> *newNode;
    newNode = new NodeType<Type>;
    newNode -> data = data;

    if( head == NULL ) {
        head = newNode;
        tail = newNode;
        ++size;
    } else {
        tail -> next = newNode;
        tail = newNode;
        ++size;
    }
}

template < typename Type >
void LinkedList<Type>::printList() const {
    NodeType<Type> *current;
    current = head;
    while( current -> next != NULL ) {
        std::cout <<  current -> data << " ";
        current = current -> next;
    }
    std::cout << current -> data << std::endl;
}

template < typename Type >
Type LinkedList<Type>::back() const {
    return tail -> data;
}

template < typename Type >
void LinkedList<Type>::copyList( const LinkedList<Type> &otherList ) {
    NodeType<Type> *newNode;
    NodeType<Type> *current;

    if( head != NULL )
        this -> destroyList();
    
    if( otherList.head == NULL ) {
        head = NULL;
        size = 0;
    } else {
        current = otherList.head;
        size = otherList.size;

        head = new NodeType<Type>;
        head -> data = current -> data;
        head -> next = NULL;
        tail = head;
        current = current -> next;

        while( current != NULL ) {
            newNode = new NodeType<Type>;
            newNode -> data = current -> data;
            tail -> next = newNode;
            tail = newNode;
            current = current -> next;
        }
    }
}


#endif