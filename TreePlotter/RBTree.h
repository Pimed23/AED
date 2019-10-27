#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

template < typename Type >
class RBTree {
    public:
        RBTree();
        ~RBTree();

        void generarTxt( std::string& txt ) const;
        void makeEmpty();
        void printTree() const;
        void findElement( const Type &x );
        void insert( const Type &x );
        void remove( const Type &x );

        const Type& findMin() const;
        const Type& findMax() const;

        bool isEmpty() const;

    private:
        struct RBNode {
            Type data;
            RBNode *left;
            RBNode *right;
            RBNode *parent;
            char color;

            RBNode();
            RBNode( const Type &d, char c = 'R', RBNode *p = NULL, RBNode *l = NULL, RBNode *r = NULL );
            RBNode( Type &&d, char c = 'R', RBNode *p = NULL, RBNode *l = NULL, RBNode *r = NULL );
        };

        RBNode *root;
        RBNode *nil;

        RBNode* getRoot();
        RBNode* findElement( const Type &x, RBNode *T );
        RBNode* findMin( RBNode *T ) const;
        RBNode* findMax( RBNode *T ) const;

        void insert( const Type &x, RBNode *&T );
        void insert_fixup( RBNode *newNode );

        void makeEmpty( RBNode *&T );
        void remove( RBNode *z, RBNode *&T );
        void remove_fixup( RBNode *z );
        void transplant( RBNode *u, RBNode *v );
        void printTree( RBNode *T ) const;
        void rotateLeft( RBNode *x );
        void rotateRight( RBNode *x );
        void generarTxt( RBNode *T , std::string &txt ) const;

};

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////                       BR RBNode STRUCT                      ///////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

template < typename Type >
RBTree<Type>::RBNode::RBNode( const Type &d, char c, RBNode *p, RBNode *l, RBNode *r )
    : data( d )
    , color( c )
    , parent( p )
    , left( l )
    , right( r )

{}

template < typename Type >
RBTree<Type>::RBNode::RBNode( Type &&d, char c, RBNode *p, RBNode *l, RBNode *r )
    : data( std::move( d ))
    , color( c )
    , parent( p )
    , left( l )
    , right( r )
{}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////                       CLASS RB TREE                       ///////////////////
////////////////////////////////////////////////////////////////////////////////////////////////


///// PUBLIC METHODS
////////////////////////////////////////////////////////////////////////////////////////////////

// Default constructor
template < typename Type >
RBTree<Type>::RBTree() {
    nil = new RBTree<Type>::RBNode( 0, 'B' );
    root = nil;
}

// Destructor
template < typename Type >
RBTree<Type>::~RBTree<Type>() {
    makeEmpty();
    delete nil;
}

template < typename Type >
void RBTree<Type>::generarTxt( std::string &txt ) const {
    generarTxt( root, txt );
}

// Remove all items in the tree
template < typename Type >
void RBTree<Type>::makeEmpty() {
    makeEmpty( root );
}

template < typename Type >
void RBTree<Type>::findElement( const Type &x ) {
    if( findElement( x, root ) == NULL )
        std::cout << "No se encontro" << std::endl;
    else
        std::cout << "Se encontro" << std::endl;
}

// Print the tree contents in sorted order
template < typename Type >
void RBTree<Type>::printTree() const {
    if( isEmpty())
        std::cout << "The tree is empty" << std::endl;
    else {
        printTree( root );
        std::cout << "\n";
    }
}

// Obtiene el nodo raiz de un arbol RB
template < typename Type >
typename RBTree<Type>::RBNode* RBTree<Type>::getRoot() {
    return root ;
}

// Insert x into the tree; duplicates are ignored.
template < typename Type >
void RBTree<Type>::insert( const Type &x ) {
    insert( x, root );
}

// Remove x into the tree.
template < typename Type >
void RBTree<Type>::remove( const Type &x ) {
    RBTree<Type>::RBNode *element = findElement( x, root );
    if( element == NULL )
        std::cout << "Element doesn't exist \n";
    else
        remove( element, root );
}

// Test if the tree is empty
template < typename Type >
bool RBTree<Type>::isEmpty() const {
    return root == nil;
}

// Find the smallest item in the tree
template < typename Type >
const Type& RBTree<Type>::findMin() const {
    if( isEmpty())
        std::cout << "The tree is empty" << std::endl;
    return findMin( root ) -> data;
}

// Find the largest item in the tree
template < typename Type >
const Type& RBTree<Type>::findMax() const {
    if( isEmpty())
        std::cout << "The tree is empty" << std::endl;
    return findMax( root ) -> data;
}

///// PRIVATE METHODS
////////////////////////////////////////////////////////////////////////////////////////////////

// Internal method to make subtree empty
template<typename Type>
void RBTree<Type>::makeEmpty( RBTree<Type>::RBNode *&T ) {
    if( T != nil ) {
        makeEmpty( T -> left );
        makeEmpty( T -> right );
        delete T;
    }
    T = nil;
}

// Insert a new element in the tree
template < typename Type >
void RBTree<Type>::insert( const Type &z, RBTree<Type>::RBNode *&T ) {
    auto *newNode = new RBTree<Type>::RBNode( z, 'R' );
    auto x = root;
    auto y = nil;

    while( x != nil ) {
        y = x;
        if( z < x -> data )
            x = x -> left;
        else if( z == x -> data )
            return;
        else
            x = x -> right;
    }

    newNode -> parent = y;

    if( y == nil )
        T = newNode;
    else if( z < y -> data )
        y -> left = newNode;
    else
        y -> right = newNode;

    newNode -> left = nil;
    newNode -> right = nil;
    insert_fixup( newNode );
}

// Print a subtree rooted at t in sorted order
template < typename Type >
void RBTree<Type>::printTree( RBTree<Type>::RBNode *T ) const {
    if( T != nil ) {
        printTree( T -> left );
        std::cout << T -> data << " -> " << T -> color << "\n";
        printTree( T -> right );
    }
}

// Evalue the balance conditions in the RB Tree
template < typename Type >
void RBTree<Type>::insert_fixup( RBTree<Type>::RBNode *z ) {
    while( z -> parent -> color == 'R' ) {
        auto grandfather = z -> parent -> parent;
        if( z -> parent == grandfather -> left ) {
            auto uncle = grandfather -> right;
            if( uncle -> color == 'R' ) {
                z -> parent -> color = 'B';
                uncle -> color = 'B';
                grandfather -> color = 'R';
                z = grandfather;
            } else if( z == grandfather ) {
                z = z -> parent;
                rotateLeft( z );
            } else {
                z -> parent -> color = 'B';
                grandfather -> color = 'R';
                rotateRight( grandfather );
            }
        } else {
            auto uncle = grandfather -> left;
            if( uncle -> color == 'R' ) {
                z -> parent -> color = 'B';
                uncle -> color = 'B';
                grandfather -> color = 'R';
                z = grandfather;
            } else if( z == grandfather ) {
                z = z -> parent;
                rotateRight( z );
            } else {
                z -> parent -> color = 'B';
                grandfather -> color = 'R';
                rotateLeft( grandfather );
            }
        }
    }
    root -> color = 'B';
}

template < typename Type >
typename RBTree<Type>::RBNode* RBTree<Type>::findElement( const Type &x, RBTree<Type>::RBNode *T ) {
    while( T != nil ) {
        if( x == T -> data )
            return T;
        else if( x < T -> data )
            T = T -> left;
        else
            T = T -> right;
    }
    return NULL;
}

template < typename Type >
void RBTree<Type>::transplant( RBTree<Type>::RBNode *u, RBTree<Type>::RBNode *v ) {
    if( u -> parent == nil )
        root = v;
    else if( u == u -> parent -> left )
        u -> parent -> left = v;
    else
        u -> parent -> right = v;
    v -> parent = u -> parent;
}

template < typename Type >
void RBTree<Type>::remove( RBNode *z, RBTree<Type>::RBNode *&T ) {
    auto y = z;
    auto x = getRoot();
    char y_color_original = y -> color;
    if( z -> left == nil ) {
        x = z -> right;
        transplant( z, z -> right );
    } else if( z -> right == nil ) {
        x = z -> left;
        transplant( z, z -> left );
    } else {
        y = findMin( z -> right );
        y_color_original = y -> color;
        x = y -> right;
        if( y -> parent == z )
            x -> parent = y;
        else {
            transplant( y, y -> right );
            y -> right = z -> right;
            y -> right -> parent = y;
        }

        transplant( z, y );
        y -> left = z -> left;
        y -> left -> parent = y;
        y -> color = z -> color;
    }

    if( y_color_original == 'B' )
        remove_fixup( x );

}

template < typename Type >
void RBTree<Type>::remove_fixup( RBNode *x ) {
    while( x != root && x -> color == 'B' ) {
        if( x == x -> parent -> left ) {
            auto w = x -> parent -> right;
            if( w -> color == 'R' ) {
                w -> color = 'B';
                x -> parent -> color = 'R';
                rotateLeft( x -> parent );
                w = x -> parent -> right;
            }

            if( w -> left -> color == 'B' && w -> right -> color == 'B') {
                w -> color = 'R';
                x = x -> parent;
            } else if( w -> right -> color == 'B') {
                w -> left -> color = 'B';
                w -> color = 'R';
                rotateRight( w );
                w = x -> parent -> right;
            } else {
                w -> color = x -> parent -> color;
                x -> parent -> color = 'B';
                w -> right -> color = 'B';
                rotateLeft( x -> parent );
                x = root;
            }
        } else {
            auto w = x -> parent -> left;
            if( w -> color == 'R' ) {
                w -> color = 'B';
                x -> parent -> color = 'R';
                rotateRight( x -> parent );
                w = x -> parent -> left;
            }

            if( w -> right -> color == 'B' && w -> left -> color == 'B') {
                w -> color = 'R';
                x = x -> parent;
            } else if( w -> left -> color == 'B') {
                w -> right -> color = 'B';
                w -> color = 'R';
                rotateLeft( w );
                w = x -> parent -> left;
            } else {
                w -> color = x -> parent -> color;
                x -> parent -> color = 'B';
                w -> left -> color = 'B';
                rotateRight( x -> parent );
                x = root;
            }
        }
    }
    x -> color = 'B';
}

// Rotate binary tree RBNode to the left
template < typename Type >
void RBTree<Type>::rotateLeft( RBTree<Type>::RBNode *x ) {
    auto y = x -> right;
    x -> right = y -> left;

    if( y -> left != nil )
        y -> left -> parent = x;
    y -> parent = x -> parent;

    if( x -> parent == nil )
        root = y;
    else if( x == x -> parent -> left )
        x -> parent -> left = y;
    else
        x -> parent -> right = y;
    y -> left = x;
    x -> parent = y;
}

// Rotate binary tree RBNode to the right
template < typename Type >
void RBTree<Type>::rotateRight( RBTree<Type>::RBNode *x ) {
    auto y = x -> left;
    x -> left = y -> right;

    if( y -> right != nil )
        y -> right -> parent = x;
    y -> parent = x -> parent;

    if( x -> parent == nil )
        root = y;
    else if( x == x -> parent -> right )
        x -> parent -> right = y;
    else
        x -> parent -> left = y;
    y -> right = x;
    x -> parent = y;
}

// Return node containing the smallest item.
template < typename Type >
typename RBTree<Type>::RBNode* RBTree<Type>::findMin( RBTree<Type>::RBNode *T ) const {
    if( T == nil )
        return NULL;
    if( T -> left == nil )
        return T;
    return findMin( T -> left );
}

// Return node containing the largest item.
template < typename Type >
typename RBTree<Type>::RBNode* RBTree<Type>::findMax( RBTree<Type>::RBNode *T ) const {
    if( T != nil )
        while( T -> right != nil )
            T = T -> right;
    return T;
}

// Convert tree in dot txt
template < typename Type >
void RBTree<Type>::generarTxt( RBTree<Type>::RBNode *T, std::string &txt ) const {
    if( T != nil ){
        txt.append( "\"" );
        txt.append( std::to_string( T -> data ));
        txt.append( "\"" );
        txt.append( " [style=filled,color=" );
        if( T -> color == 'R' )
            txt.append( "red" );
        else
            txt.append( "black" );
        txt.append( ",fontcolor=white]\n" );
        if( T -> left != nil ){
            txt.append( "\"" );
            txt.append( std::to_string( T -> data ));
            txt.append( "\"" );
            txt.append(" -> ");
            txt.append( "\"" );
            txt.append( std::to_string( T-> left -> data ));
            txt.append( "\"" );
            txt.append( "\n" );
        } else {
            std::string nodeLName;
            nodeLName = "null" + std::to_string( T -> data ) + "l";
            txt.append( "\"" );
            txt.append( nodeLName );
            txt.append( "\"" );
            txt.append( " [style=filled,color=black,fontcolor=white]\n" );
            txt.append( nodeLName );
            txt.append( " [label=\"NULL\"];\n" );
            txt.append( "\"" );
            txt.append( std::to_string( T -> data ));
            txt.append( "\"" );
            txt.append( " -> " );
            txt.append( nodeLName );
            txt.append( ";\n" );
        }
        generarTxt( T -> left, txt );
        if( T -> right != nil ){
            txt.append( "\"" );
            txt.append( std::to_string( T -> data ));
            txt.append( "\"" );
            txt.append( " -> " );
            txt.append( "\"" );
            txt.append( std::to_string( T -> right -> data ));
            txt.append( "\"" );
            txt.append( "\n" );
        } else {
            std::string nodeRName;
            nodeRName = "null" + std::to_string( T -> data ) + "r";
            txt.append( "\"" );
            txt.append( nodeRName );
            txt.append( "\"" );
            txt.append( " [style=filled,color=black,fontcolor=white]\n" );
            txt.append( nodeRName );
            txt.append( " [label=\"NULL\"];\n" );
            txt.append( "\"" );
            txt.append( std::to_string( T -> data ));
            txt.append( "\"" );
            txt.append( " -> " );
            txt.append( nodeRName );
            txt.append( ";\n" );
        }
        generarTxt( T -> right, txt );
    }
}

#endif
