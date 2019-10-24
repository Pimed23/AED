#ifndef RB_TREE_H
#define RB_TREE_H

#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

template < typename Type >
class RBTree {
    public:
        RBTree();
        ~RBTree();

        void makeEmpty();
        void printTree() const;
        void insert( const Type &x );
        void generarTxt( std::string& txt )const;

        bool isEmpty() const;

    private:
        struct RBNode {
            Type data;
            RBNode *left;
            RBNode *right;
            RBNode *parent;
            std::string color;

            RBNode();
            RBNode( const Type &d, std::string c = "R", RBNode *p = NULL, RBNode *l = NULL, RBNode *r = NULL );
            RBNode( Type &&d, std::string c = "R", RBNode *p = NULL, RBNode *l = NULL, RBNode *r = NULL );
        };

        RBNode *root;

        RBNode* getRoot();
        void makeEmpty( RBNode *&T );
        void printTree( RBNode *T ) const;
        void insert( const Type &x, RBNode *&T );
        void rotateLeft( RBNode *x );
        void rotateRight( RBNode *x );
        void insert_fixup( RBNode *newNode );
        void generarTxt( RBNode *T , std::string &txt ) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////                       BR RBNode STRUCT                      ///////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

template < typename Type >
RBTree<Type>::RBNode::RBNode( const Type &d, std::string c, RBNode *p, RBNode *l, RBNode *r )
    : data( d )
    , color( c )
    , parent( p )
    , left( l )
    , right( r )

{}

template < typename Type >
RBTree<Type>::RBNode::RBNode( Type &&d, std::string c, RBNode *p, RBNode *l, RBNode *r )
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
    root = NULL;
}

// Destructor
template < typename Type >
RBTree<Type>::~RBTree<Type>() {
    makeEmpty();
}

// Remove all items in the tree
template < typename Type >
void RBTree<Type>::makeEmpty() {
    makeEmpty( root );
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

template < typename Type >
void RBTree<Type>::generarTxt( std::string &txt ) const {
    generarTxt( root, txt );
}

// Test if the tree is empty
template < typename Type >
bool RBTree<Type>::isEmpty() const {
    return root == NULL;
}

///// PRIVATE METHODS
////////////////////////////////////////////////////////////////////////////////////////////////

// Internal method to make subtree empty
template<typename Type>
void RBTree<Type>::makeEmpty( RBTree<Type>::RBNode *&T ) {
    if( T != NULL ) {
        makeEmpty( T -> left );
        makeEmpty( T -> right );
        delete T;
    }
    T = NULL;
}

// Insert a new element in the tree
template < typename Type >
void RBTree<Type>::insert( const Type &x, RBTree<Type>::RBNode *&T ) {
    auto *newNode = new RBTree<Type>::RBNode( x );
    auto linker = getRoot();
    RBTree<Type>::RBNode *old = NULL;

    while( linker != NULL ) {
        old = linker;
        if( x < linker -> data )
            linker = linker -> left;
        else
            linker = linker -> right;
    }

    newNode -> parent = old;

    if( old == NULL )
        T = newNode;
    else if( x < old -> data )
        old -> left = newNode;
    else
        old -> right = newNode;

    insert_fixup( newNode );
}

// Print a subtree rooted at t in sorted order
template < typename Type >
void RBTree<Type>::printTree( RBTree<Type>::RBNode *T ) const {
    if( T != NULL ) {
        printTree( T -> left );
        std::cout << T -> data << " -> " << T -> color << "\n";
        printTree( T -> right );
    }
}

// Evalue the balance conditions in the RB Tree
template < typename Type >
void RBTree<Type>::insert_fixup( RBTree<Type>::RBNode *newNode ) {
    while( newNode -> parent != NULL && newNode -> parent -> color == "R") {
        auto grandparent = newNode -> parent -> parent;
        auto uncle = getRoot();
        if( newNode -> parent == grandparent -> left ) {
            if( grandparent -> right )
                uncle = grandparent -> right;
            if( uncle -> color == "R" ) {
                newNode -> parent -> color = "B";
                uncle -> color = "B";
                grandparent -> color = "R";
                if( grandparent -> data != root -> data )
                    newNode = grandparent;
                else
                    break;
            } else if( newNode == grandparent -> left -> right )
                rotateLeft( newNode -> parent );
            else {
                newNode -> parent -> color = "B";
                grandparent -> color = "R";
                rotateRight( grandparent );
                if( grandparent -> data != root -> data )
                    newNode = grandparent;
                else
                    break;
            }
        } else {
            if( grandparent -> left )
                uncle = grandparent -> left;
            if( uncle -> color == "R" ) {
                newNode -> parent -> color = "B";
                uncle -> color = "B";
                grandparent -> color = "R";
                if( grandparent -> data != root -> data )
                    newNode = grandparent;
                else
                    break;
            } else if( newNode == grandparent -> right -> left )
                rotateRight( newNode -> parent );
            else {
                newNode -> parent -> color = "B";
                grandparent -> color = "R";
                rotateLeft( grandparent );
                if( grandparent -> data != root -> data )
                    newNode = grandparent;
                else
                    break;
            }
        }
    }
    root -> color = "B";
}

// Rotate binary tree RBNode to the left
template < typename Type >
void RBTree<Type>::rotateLeft( RBTree<Type>::RBNode *x ) {
    auto y = x -> right;
    x -> right = y -> left;

    if( y -> left != NULL )
        y -> left -> parent = x;
    y -> parent = x -> parent;

    if( x -> parent == NULL )
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

    if( y -> right != NULL )
        y -> right -> parent = x;
    y -> parent = x -> parent;

    if( x -> parent == NULL )
        root = y;
    else if( x == x -> parent -> right )
        x -> parent -> right = y;
    else
        x -> parent -> left = y;
    y -> right = x;
    x -> parent = y;
}

// Convert tree in dot txt
template < typename Type >
void RBTree<Type>::generarTxt( RBTree<Type>::RBNode *T, std::string &txt ) const {

    if( T != nullptr ){
        if(T->left != nullptr){
            txt.append("\"");
            txt.append(std::to_string(T->data));
            txt.append("\"");
            txt.append(" -> ");
            txt.append("\"");
            txt.append(std::to_string(T->left->data));
            txt.append("\"");
            txt.append("\n");
        }
        else{
            std::string nodeLName;
            nodeLName = "null" + std::to_string(T->data) + "l";
            txt.append(nodeLName);
            txt.append(" [label=\"NULL\"];\n");
            txt.append("\"");
            txt.append(std::to_string(T->data));
            txt.append("\"");
            txt.append(" -> ");
            txt.append(nodeLName);
            txt.append(";\n");
        }
        generarTxt( T->left,txt );
        if(T->right != nullptr){
            txt.append("\"");
            txt.append(std::to_string(T->data));
            txt.append("\"");
            txt.append(" -> ");
            txt.append("\"");
            txt.append(std::to_string(T->right->data));
            txt.append("\"");
            txt.append("\n");
        }
        else{
            std::string nodeRName;
            nodeRName = "null" + std::to_string(T->data) + "r";
            txt.append(nodeRName);
            txt.append(" [label=\"NULL\"];\n");
            txt.append("\"");
            txt.append(std::to_string(T->data));
            txt.append("\"");
            txt.append(" -> ");
            txt.append(nodeRName);
            txt.append(";\n");
        }
        generarTxt( T->right,txt );
    }
}



#endif
#endif // RB_TREE_H
