#ifndef AVL_H
#define AVL_H

#include <iostream>

template < typename Type >
class AVLTree {
    public:
        AVLTree();
        AVLTree( const AVLTree &otherTree );
        AVLTree( AVLTree &&rhs );
        ~AVLTree();

        void makeEmpty();
        void printTree() const;
        void insert( const Type &x );
        void insert( Type &&x );
        void remove( const Type &x );
        void generarTxt(std::string& txt )const;

        const Type& findMin() const;
        const Type& findMax() const;

        bool isEmpty() const;
        bool contains( const Type &x ) const;

        AVLTree& operator=( const AVLTree &rhs );
        AVLTree& operator=( AVLTree &&rhs );


    private:
        struct AVLNode {
            Type data;
            AVLNode *left;
            AVLNode *right;
            int height;
            AVLNode( const Type &d, AVLNode *l = NULL, AVLNode *r = NULL, int h = 0 );
            AVLNode( Type &&d, AVLNode *l = NULL, AVLNode *r = NULL, int h = 0 );
        };

        AVLNode *root;

        void makeEmpty( AVLNode *&T );
        void insert( const Type &x, AVLNode *&T );
        void insert( Type && x, AVLNode *&T );
        void remove( const Type & x, AVLNode *&T );
        void balance( AVLNode *&T );
        void printTree( AVLNode *T ) const;
        void rotateWithRightChild( AVLNode *&k1 );
        void rotateWithLeftChild( AVLNode *&k2 );
        void doubleWithLeftChild( AVLNode *&k3 );
        void doubleWithRightChild( AVLNode *&k4 );
        void generarTxt( AVLNode *T , std::string &txt ) const;

        AVLNode* clone( AVLNode *T ) const;
        AVLNode* findMin( AVLNode *T ) const;
        AVLNode* findMax( AVLNode *T ) const;

        bool contains( const Type &x, AVLNode *T ) const;

        int height( AVLNode* T ) const;
        int max( int lhs, int rhs ) const;

        static const int ALLOWED_IMBALANCE = 1;
};

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////                       AVL NODE STRUCT                      //////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


template < typename Type >
AVLTree<Type>::AVLNode::AVLNode( const Type &d, AVLNode *l, AVLNode *r, int h ) :
    data( d ), left( l ), right( r ), height( h ) {}

template < typename Type >
AVLTree<Type>::AVLNode::AVLNode( Type &&d, AVLNode *l, AVLNode *r, int h ) :
    data( std::move( d )), left( l ), right( r ), height( h ) {}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////                       CLASS AVL TREE                       //////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

///// PUBLIC METHODS
////////////////////////////////////////////////////////////////////////////////////////////////

// Default constructor
template < typename Type >
AVLTree<Type>::AVLTree() {
    root = NULL;
}

// Copy constructor
template < typename Type >
AVLTree<Type>::AVLTree( const AVLTree &otherTree ) {
    root = clone( otherTree.root );
}

// Move constructor
template < typename Type >
AVLTree<Type>::AVLTree( AVLTree &&rhs ) : root( rhs.root ) {
    rhs.root = NULL;
}

// Destructor
template < typename Type >
AVLTree<Type>::~AVLTree<Type>() {
    makeEmpty();
}

// Remove all items in the tree
template < typename Type >
void AVLTree<Type>::makeEmpty() {
    makeEmpty( root );
}

// Print the tree contents in sorted order
template < typename Type >
void AVLTree<Type>::printTree() const {
    if( isEmpty())
        std::cout << "The tree is empty" << std::endl;
    else
        printTree( root );
}

// Insert x into the tree; duplicates are ignored.
template < typename Type >
void AVLTree<Type>::insert( const Type &x ) {
    insert( x, root );
}

// Insert x into the tree; duplicates are ignored.
template < typename Type >
void AVLTree<Type>::insert( Type &&x ) {
    insert( std::move( x ), root );
}

// Remove x from the tree. Nothing is done if x is not found.
template < typename Type >
void AVLTree<Type>::remove( const Type &x ) {
    remove( x, root );
}

template < typename Type >
void AVLTree<Type>::generarTxt( std::string &txt ) const {
    generarTxt( root,txt);
}

// Find the smallest item in the tree
template < typename Type >
const Type& AVLTree<Type>::findMin() const {
    if( isEmpty())
        std::cout << "The tree is empty" << std::endl;
    return findMin( root ) -> data;
}

// Find the largest item in the tree
template < typename Type >
const Type& AVLTree<Type>::findMax() const {
    if( isEmpty())
        std::cout << "The tree is empty" << std::endl;
    return findMax( root ) -> data;
}

// Test if the tree is empty
template < typename Type >
bool AVLTree<Type>::isEmpty() const {
    return root == NULL;
}

// Returns true if x is found in the tree
template < typename Type >
bool AVLTree<Type>::contains( const Type &x ) const {
    return contains( x, root );
}

// Overloading Operator= for deep copy
template < typename Type >
AVLTree<Type>& AVLTree<Type>::operator=( const AVLTree &rhs ) {
    AVLTree copy = rhs;
    std::swap( *this, copy );
    return *this;
}

// Overloading Operator= for move constructor
template < typename Type >
AVLTree<Type>& AVLTree<Type>::operator=( AVLTree &&rhs ) {
    std::swap( root, rhs.root );
    return *this;
}

///// PRIVATE METHODS
////////////////////////////////////////////////////////////////////////////////////////////////


// Internal method to make subtree empty
template<typename Type>
void AVLTree<Type>::makeEmpty( AVLTree<Type>::AVLNode *&T ) {
    if( T != NULL ) {
        makeEmpty( T -> left );
        makeEmpty( T -> right );
        delete T;
    }
    T = NULL;
}

// Internal method to insert into a subtree
template < typename Type >
void AVLTree<Type>::insert( const Type &x, AVLTree<Type>::AVLNode *&T ) {
    if( T == NULL )
        T = new AVLTree<Type>::AVLNode( x, NULL, NULL );
    else if( x < T -> data )
        insert( x, T -> left );
    else if( T -> data < x )
        insert( x, T -> right );
    balance( T );
}

// Internal method to insert into a subtree
template < typename Type >
void AVLTree<Type>::insert( Type &&x, AVLTree<Type>::AVLNode *&T ) {
    if( T == NULL )
        T = new AVLTree<Type>::AVLNode( std::move( x ), NULL, NULL );
    else if( x < T -> data )
        insert( std::move( x ), T -> left );
    else if( T -> data < x )
        insert( std::move( x ), T -> right );
    balance( T );
}

// Internal method to remove from a subtree
template < typename Type >
void AVLTree<Type>::remove( const Type &x, AVLTree<Type>::AVLNode *&T ) {
    if( T == NULL )
        return;
    if( x < T -> data )
        remove( x, T -> left );
    else if( T -> data < x )
        remove( x, T -> right );
    else if( T -> left != NULL && T -> right != NULL ) {
        T -> data = findMin( T -> right ) -> data;
        remove( T -> data, T -> right );
    } else {
        AVLTree<Type>::AVLNode *oldNode = T;
        T =( T -> left != NULL ) ? T -> left : T -> right;
        delete oldNode;
    }
    balance( T );
}

// Assume T is balanced or within one of being balanced
template < typename Type >
void AVLTree<Type>::balance( AVLTree<Type>::AVLNode *&T ) {
    if( T == NULL )
        return;
    if( height( T -> left) - height( T -> right ) > ALLOWED_IMBALANCE ) {
        if( height( T -> left -> left ) >= height( T -> left -> right ))
            rotateWithLeftChild( T );
        else
            doubleWithLeftChild( T );
    } else {
        if( height( T -> right ) - height( T -> left ) > ALLOWED_IMBALANCE ) {
            if( height( T -> right -> right ) >= height( T -> right -> left ))
                rotateWithRightChild( T );
            else
                doubleWithRightChild( T );
        }
    }
    T -> height = max( height( T -> left ), height( T -> right )) + 1;
}

// Print a subtree rooted at t in sorted order
template < typename Type >
void AVLTree<Type>::printTree( AVLTree<Type>::AVLNode *T ) const {
    if( T != NULL ) {
        printTree( T -> left );
        std::cout << T -> data << std::endl;
        printTree( T -> right );
    }
}

// Rotate binary tree node with right child
template < typename Type >
void AVLTree<Type>::rotateWithRightChild( AVLTree<Type>::AVLNode *&k1 ) {
    AVLTree<Type>::AVLNode *k2 = k1 -> right;
    k1 -> right = k2 -> left;
    k2 -> left = k1;
    k1 -> height = max( height( k1 -> left ), height( k1 -> right )) + 1;
    k2 -> height = max( height( k2 -> right ), k1 -> height ) + 1;
    k1 = k2;
}

// Rotate binary tree node with left child
template < typename Type >
void AVLTree<Type>::rotateWithLeftChild( AVLTree<Type>::AVLNode *&k2 ) {
    AVLTree<Type>::AVLNode *k1 = k2 -> left;
    k2 -> left = k1 -> right;
    k1 -> right = k2;
    k2 -> height = max( height( k2 -> left ), height( k2 -> right )) + 1;
    k1 -> height = max( height( k1 -> left ), k2 -> height ) + 1;
    k2 = k1;
}

// Double rotate binary tree node: first left child with its right child; then node k3 with new left child.
template < typename Type >
void AVLTree<Type>::doubleWithLeftChild( AVLNode *&k3 ) {
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

// Double rotate binary tree node: first right child with its left child; then node k1 with new right child.
template < typename Type >
void AVLTree<Type>::doubleWithRightChild( AVLNode *&k4 ) {
    rotateWithLeftChild( k4 -> right );
    rotateWithRightChild( k4 );
}

// Convert tree in dot txt
template < typename Type >
void AVLTree<Type>::generarTxt( AVLTree<Type>::AVLNode *T, std::string &txt ) const {
    if( T != NULL ){
        if( height( root ) == 0 ) {
            txt.append("\"");
            txt.append(std::to_string(T->data));
            txt.append("\"");
            txt.append(" -> ");
            txt.append("\"");
            txt.append("NULL");
            txt.append("\"");
            txt.append("\n");
        }
        if( T -> left != NULL ){
            txt.append("\"");
            txt.append( std::to_string( T -> data ));
            txt.append("\"");
            txt.append(" -> ");
            txt.append("\"");
            txt.append( std::to_string( T -> left -> data ));
            txt.append("\"");
            txt.append("\n");
        }
        generarTxt( T -> left, txt );
        if( T -> right != NULL ){
            txt.append("\"");
            txt.append( std::to_string( T -> data ));
            txt.append("\"");
            txt.append(" -> ");
            txt.append("\"");
            txt.append( std::to_string( T -> right -> data ));
            txt.append("\"");
            txt.append("\n");
        }
        generarTxt( T -> right, txt );
    }
}


// Internal method to clone subtree
template < typename Type >
typename AVLTree<Type>::AVLNode* AVLTree<Type>::clone( AVLTree<Type>::AVLNode *T ) const {
    if( T == NULL )
        return NULL;
    else
        return new AVLTree<Type>::AVLNode( T -> data, clone( T -> left ), clone( T -> right ), T -> height );
}

// Return node containing the smallest item.
template < typename Type >
typename AVLTree<Type>::AVLNode* AVLTree<Type>::findMin( AVLTree<Type>::AVLNode *T ) const {
    if( T == NULL )
        return NULL;
    if( T -> left == NULL )
        return T;
    return findMin( T -> left );
}

// Return node containing the largest item.
template < typename Type >
typename AVLTree<Type>::AVLNode* AVLTree<Type>::findMax( AVLTree<Type>::AVLNode *T ) const {
    if( T != NULL )
        while( T -> right != NULL )
            T = T -> right;
    return T;
}

// Internal method to test if an item is in a subtree
template < typename Type >
bool AVLTree<Type>::contains( const Type &x, AVLTree<Type>::AVLNode *T ) const {
    if( T == NULL )
        return false;
    else if( x < T -> data )
        return contains( x, T -> left );
    else if( T -> data < x )
        return contains( x, T -> right );
    else
        return true;
}

// Return the height of node t or -1 if nullptr
template < typename Type >
int AVLTree<Type>::height( AVLTree<Type>::AVLNode *T ) const {
    return T == NULL ? -1 : T -> height;
}

// Compare two integer and returns the
template < typename Type >
int AVLTree<Type>::max( int lhs, int rhs ) const {
    return lhs > rhs ? lhs : rhs;
}




#endif // AVL_H
