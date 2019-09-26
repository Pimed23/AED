#ifndef UNORDEREDLINKEDLIST_H
#define UNORDEREDLINKEDLIST_H

#include <iostream>

template < typename Type >
struct nodeType {
    Type info;
    nodeType<Type> *link;
};

//////////////////////////////////////////////////////////////////////////////////
// LINKED LIST ITERATOR
//////////////////////////////////////////////////////////////////////////////////

template < typename Type >
class linkedListIterator {
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

//////////////////////////////////////////////////////////////////////////////////
// LINKED LIST
//////////////////////////////////////////////////////////////////////////////////

template < typename Type >
class linkedList {
    public:
        linkedList();
        linkedList( const linkedList<Type> &otherList );
        ~linkedList();

        const linkedList<Type> &operator=( const linkedList<Type> & );
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
        void copyList( const linkedList<Type> &otherList );
};

template < typename Type >
linkedList<Type>::linkedList() {
    first = NULL;
    last = NULL;
    count = 0;
}

template < typename Type >
linkedList<Type>::linkedList( const linkedList<Type> &otherList ) {
    first = NULL;
    copyList( otherList );
}

template < typename Type >
linkedList<Type>::~linkedList() {
    destroyList();
}

template < typename Type >
const linkedList<Type>& linkedList<Type>::operator=( const linkedList<Type> &otherList ) {
    if( this != &otherList )
        copyList( otherList );
    return *this;
}

template < typename Type >
void linkedList<Type>::initializeList() {
    destroyList();
}

template < typename Type >
bool linkedList<Type>::isEmptyList() const {
    return ( first == NULL );
}

template < typename Type >
void linkedList<Type>::print() const {
    nodeType<Type> *current = first;
    while( current != NULL ) {
        std::cout << current -> info << " ";
        current = current -> link;
    }
}

template < typename Type >
int linkedList<Type>::lenght() const {
    return count;
}

template < typename Type >
void linkedList<Type>::destroyList() {
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
Type linkedList<Type>::front() const {
    assert( first != NULL );
    return first -> info;
}

template < typename Type >
Type linkedList<Type>::back() const {
    assert( last != NULL );
    return last -> info;
}

template < typename Type >
linkedListIterator<Type> linkedList<Type>::begin() {
    linkedListIterator<Type> temp( first );
    return temp;
}

template < typename Type >
linkedListIterator<Type> linkedList<Type>::end() {
    linkedListIterator<Type> temp( NULL );
    return temp;
}

template < typename Type >
void linkedList<Type>::copyList( const linkedList<Type> &otherList ) {
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

//////////////////////////////////////////////////////////////////////////////////
// UNORDERED LINKED LIST
//////////////////////////////////////////////////////////////////////////////////

template < typename Type >
class unorderedLinkedList : public linkedList<Type> {
    public:
        bool search( const Type &searchItem ) const;
        void insertFirst( const Type &newItem );
        void insertLast( const Type &newItem );
        void deleteNode( const Type &deleteItem );
};

template < typename Type >
bool unorderedLinkedList<Type>::search( const Type &searchItem ) const {
    nodeType<Type> *current;
    bool found = false;
    current = this -> first;

    while( current != NULL && !found ) {
        if( current -> info == searchItem )
            found = true;
        else
            current = current -> link;
    }
    return found;
}

template < typename Type >
void unorderedLinkedList<Type>::insertFirst( const Type &newItem ) {
    nodeType<Type> *newNode;
    newNode = new nodeType<Type>;
    newNode -> info = newItem;
    newNode -> link = this -> first;
    this -> first = newNode;
    ++( this -> count );

    if( this -> last = NULL )
        this -> last = newNode;
}

template < typename Type >
void unorderedLinkedList<Type>::insertLast( const Type &newItem ) {
    nodeType<Type> *newNode;
    newNode = new nodeType<Type>;
    newNode -> info = newItem;
    newNode -> link = NULL;

    if( this -> first == NULL ) {
        this -> first = newNode;
        this -> last = newNode;
        ++( this -> count );
    } else {
        this -> last -> link = newNode;
        this -> last = newNode;
        ++( this -> count );
    }
}

template <class Type>
void unorderedLinkedList<Type>::deleteNode( const Type &deleteItem ) {
    nodeType<Type> *current;
    nodeType<Type> *trailCurrent;
    bool found;
    if( this -> first == NULL )
        std::cout << "Cannot delete from an empty list." << std::endl;
    else {
        if( this -> first -> info == deleteItem ) {
            current = this -> first;
            this -> first = this -> first -> link;
            --( this -> count );

            if( this -> first == NULL ) 
                this -> last = NULL;
            delete current;
        } else {
            found = false;
            trailCurrent = this -> first;
            current = this -> first -> link;

            while( current != NULL && !found ) {
                if( current -> info != deleteItem ) {
                    trailCurrent = current;
                    current = current -> link;
                } else
                    found = true;
            }
            if( found ) {
                trailCurrent -> link = current -> link;
                --( this -> count );
                if( this -> last == current )
                    this -> last = trailCurrent;
                delete current; 
            } else
                std::cout << "The item to be deleted is not in the list." << std::endl;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////
// ORDERED LINKED LIST
//////////////////////////////////////////////////////////////////////////////////

template < typename Type >
class orderedLinkedList : public linkedList<Type> {
    public:
        bool search( const Type& searchItem ) const;
        void insert( const Type& newItem );
        void insertFirst( const Type &newItem );
        void insertLast( const Type &newItem );
        void deleteNode( const Type &deleteItem );
};

template < typename Type >
bool orderedLinkedList<Type>::search( const Type &searchItem ) const {
    bool found = false;
    nodeType<Type> *current;

    current = this -> first;
    while( current != NULL && !found ) {
        if( current -> info >= searchItem )
            found = true;
        else
            current = current -> link;
    }
    if( found )
        found = ( current -> info == searchItem );
    
    return found;
}

template < typename Type >
void orderedLinkedList<Type>::insert( const Type &newItem ) {
    nodeType<Type> *current;
    nodeType<Type> *trailCurrent;
    nodeType<Type> *newNode;

    bool found;

    newNode = new nodeType<Type>;
    newNode -> info = newItem;
    newNode -> link = NULL;

    if( this -> first == NULL ) {
        this -> first = newNode;
        this -> last = newNode;
        ++( this -> count );
    } else {
        current = this -> first;
        found = false;

        while( current != NULL && !found ) {
            if( current -> info >= newItem )
                found = true;
            else {
                trailCurrent = current;
                current = current -> link;
            }
        }
        
        if( current == this -> first ) {
            newNode -> link = this -> first;
            this -> first = newNode;
            ++( this -> count );
        } else {
            trailCurrent -> link = newNode;
            newNode -> link = current;
            
            if( current == NULL )
                this -> last = newNode;
            
            ++( this -> count );
        }
    }
}

template < typename Type >
void orderedLinkedList<Type>::insertFirst( const Type &newItem ) {
    insert( newItem );
}

template < typename Type >
void orderedLinkedList<Type>::insertLast( const Type &newItem ) {
    insert( newItem );
}

template < typename Type >
void orderedLinkedList<Type>::deleteNode( const Type &deleteItem ) {
    nodeType<Type> *current;
    nodeType<Type> *trailCurrent;
    bool found;

    if( this -> first == NULL )
        std::cout << "Cannot delete from an empty list." << std::endl;
    else {
        current = this -> first;
        found = false;

        while( current != NULL && !found ) {
            if( current -> info >= deleteItem )
                found = true;
            else {
                trailCurrent = current;
                current = current -> link;
            }
        }

        if( current == NULL )
            std::cout << "The item to be deleted is not in the list." << std::endl;
        else {
            if( current -> info == deleteItem ) {
                if( this -> first == current ) {
                    this -> first = this -> first -> link;

                    if( this -> first == NULL ) 
                        this -> last = NULL;
                    delete current;

                } else {
                    trailCurrent -> link = current -> link;

                    if( current == this -> last )
                        this -> last = trailCurrent;
                    delete current;
                }
                --( this -> count );
            } else 
                std::cout << "The item to be deleted is not in the list " << std::endl;
        }
    }
}


#endif