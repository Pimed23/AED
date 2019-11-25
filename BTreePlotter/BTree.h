#ifndef BTREE_H
#define BTREE_H

#include <iostream>
using namespace std;

template < typename Type >
class BTreeNode {
    public:
        BTreeNode( int _t, bool _leaf );

        void insertNonFull( Type k );
        void splitChild( int i, BTreeNode<Type> *y );
        void traverse();
        void remove( Type k );
        void removeFromLeaf( int idx);
        void removeFromNonLeaf( int idx);
        void merge( int idx );
        void fill( int idx );
        void borrowFromPrev( int idx );
        void borrowFromNext( int idx );

        Type getPred( int idx );
        Type getSucc( int idx );

        BTreeNode<Type> *search( Type k );

        int findKey( Type k );

    private:
        Type *keys;
        BTreeNode<Type> **C;
        int n;
        int t;
        bool leaf;

        template < typename T >
        friend class BTree;
};

template < typename Type >
class BTree {
    public:
        BTree( int t );

        void traverse();
        void insert( Type k );
        void remove( Type k );

        BTreeNode<Type>* search( Type k );

    private:
        BTreeNode<Type> *root;
        int t;
};

//// METHODS CLASS BTREENODE
/////////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename Type >
BTreeNode<Type>::BTreeNode( int t, bool leaf ) {
    this -> t = t;
    this -> leaf = leaf;

    keys = new Type[ 2 * t - 1 ];
    C = new BTreeNode<Type> *[ 2 * t ];

    n = 0;
}

template < typename Type >
void BTreeNode<Type>::traverse() {
    int i;
    for( i = 0; i < n; i++ ) {
        if( leaf == false )
            C[ i ] -> traverse();
        cout << " " << keys[ i ];
    }

    if ( leaf == false )
        C[ i ] -> traverse();
}

template < typename Type >
BTreeNode<Type>* BTreeNode<Type>::search( Type k ) {
    int i = 0;
    while( i < n && k > keys[ i ])
        ++i;

    if( keys[ i ] == k )
        return this;

    if( leaf == true )
        return NULL;

    return C[ i ] -> search( k );
}

template < typename Type >
void BTreeNode<Type>::insertNonFull( Type k ) {
    int i = n - 1;

    if( leaf == true) {
        while( i >= 0 && keys[ i ] > k ) {
            keys[ i + 1 ] = keys[ i ];
            i--;
        }

        keys[ i + 1 ] = k;
        n = n + 1;

    } else {
        while (i >= 0 && keys[ i ] > k)
            i--;

        if( C[ i + 1 ] -> n == 2 * t - 1 ) {
            splitChild( i + 1, C[ i + 1 ]);

            if( keys[ i + 1 ] < k )
                i++;
        }
        C[ i + 1 ] -> insertNonFull( k );
    }
}

template < typename Type >
void BTreeNode<Type>::splitChild( int i, BTreeNode<Type> *y )  {
    auto z = new BTreeNode<Type>( y -> t, y -> leaf );
    z -> n = t - 1;

    for( int j = 0; j < t - 1; j++ )
        z -> keys[ j ] = y -> keys[ j + t ];

    if( y -> leaf == false ) {
        for( int j = 0; j < t; j++ )
            z -> C[ j ] = y -> C[ j + t ];
    }

    y -> n = t - 1;

    for( int j = n; j >= i + 1; j-- )
        C[ j + 1 ] = C[ j ];

    C[ i + 1 ] = z;

    for( int j = n - 1; j >= i; j-- )
        keys[ j + 1 ] = keys[ j ];

    keys[ i ] = y -> keys[ t - 1 ];
    n = n + 1;
}

template < typename Type >
int BTreeNode<Type>::findKey( Type k ) {
    int idx = 0;
    while( idx < n && keys[ idx ] < k )
        ++idx;
    return idx;
}

template < typename Type >
void BTreeNode<Type>::remove( Type k ) {
    int idx = findKey( k );

    if( idx < n && keys[ idx ] == k ) {
        if( leaf )
            removeFromLeaf( idx );
        else
            removeFromNonLeaf( idx );

    } else {
        if( leaf ) {
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }

        bool flag = (( idx==n ) ? true : false );

        if ( C[ idx ] -> n < t )
            fill( idx );

        if( flag && idx > n )
            C[ idx - 1 ] -> remove( k );
        else
            C[ idx ] -> remove( k );
    }
    return;
}

template < typename Type >
void BTreeNode<Type>::removeFromLeaf( int idx ) {
    for( int i = idx + 1; i < n; ++i )
        keys[ i - 1 ] = keys[ i ];
    n--;
    return;
}

template < typename Type >
void BTreeNode<Type>::removeFromNonLeaf( int idx ) {
    int k = keys[ idx ];

    if( C[ idx ] -> n >= t ) {
        Type pred = getPred( idx );
        keys[ idx ] = pred;
        C[ idx ] -> remove( pred );
    }

    else if( C[ idx + 1 ] -> n >= t ) {
        Type succ = getSucc( idx );
        keys[ idx ] = succ;
        C[ idx + 1 ] -> remove( succ );
    }

    else {
        merge( idx );
        C[ idx ] -> remove( k );
    }
    return;
}

template < typename Type >
Type BTreeNode<Type>::getPred( int idx ) {
    BTreeNode<Type> *cur = C[ idx ];
    while( !cur -> leaf )
        cur = cur -> C[ cur -> n ];

    return cur -> keys[ cur -> n - 1 ];
}

template < typename Type >
Type BTreeNode<Type>::getSucc( int idx ) {
    BTreeNode<Type> *cur = C[ idx + 1 ];
    while ( !cur -> leaf )
        cur = cur -> C[ 0 ];
    return cur -> keys[ 0 ];
}

template < typename Type >
void BTreeNode<Type>::merge( int idx ) {
    BTreeNode<Type> *child = C[ idx ];
    BTreeNode<Type> *sibling = C[ idx + 1 ];
    child -> keys[ t - 1 ] = keys[ idx ];

    for( int i = 0; i < sibling -> n; ++i )
        child -> keys[ i + t ] = sibling -> keys[ i ];

    if( !child -> leaf ) {
        for( int i = 0; i <= sibling -> n; ++i )
            child -> C[ i + t ] = sibling -> C[ i ];
    }

    for( int i = idx + 1; i < n; ++i )
        keys[ i - 1 ] = keys[ i ];

    for( int i = idx + 2; i <= n; ++i )
        C[ i - 1 ] = C[ i ];

    child ->n += sibling -> n + 1;
    n--;
    delete( sibling );
    return;
}

template < typename Type >
void BTreeNode<Type>::fill( int idx ) {
    if( idx != 0 && C[ idx - 1 ] -> n >= t )
        borrowFromPrev( idx );

    else if( idx != n && C[ idx + 1 ] -> n >= t )
        borrowFromNext( idx );

    else {
        if( idx != n )
            merge( idx );
        else
            merge( idx - 1 );
    }
    return;
}

template < typename Type >
void BTreeNode<Type>::borrowFromPrev( int idx ) {
    BTreeNode<Type> *child = C[ idx ];
    BTreeNode<Type> *sibling = C[ idx - 1 ];

    for( int i = child -> n - 1; i >= 0; --i )
        child -> keys[ i + 1 ] = child -> keys[ i ];

    if ( !child -> leaf ) {
        for( int i = child -> n; i >= 0; --i )
            child -> C[ i + 1 ] = child -> C[ i ];
    }

    child -> keys[ 0 ] = keys[ idx - 1 ];

    if( !child -> leaf )
        child -> C[ 0 ] = sibling -> C[ sibling -> n ];

    keys[ idx - 1 ] = sibling -> keys[ sibling -> n - 1 ];

    child -> n += 1;
    sibling -> n -= 1;

    return;
}

template < typename Type >
void BTreeNode<Type>::borrowFromNext( int idx ) {
    BTreeNode<Type> *child = C[ idx ];
    BTreeNode<Type> *sibling = C[ idx + 1 ];

    child -> keys[( child -> n )] = keys[ idx ];

    if( !( child -> leaf ))
        child -> C[( child -> n ) + 1 ] = sibling -> C[ 0 ];

    keys[ idx ] = sibling -> keys[ 0 ];

    for( int i = 1; i < sibling -> n; ++i )
        sibling -> keys[ i - 1 ] = sibling -> keys[ i ];

    if( !sibling -> leaf ) {
        for( int i = 1; i <= sibling -> n; ++i )
            sibling -> C[ i - 1 ] = sibling -> C[ i ];
    }

    child -> n += 1;
    sibling -> n -= 1;

    return;
}

/// METHODS CLASS BTREE
/////////////////////////////////////////////////////////////////////////////////////////////////////

template < typename Type >
BTree<Type>::BTree( int t ) {
    this -> root = NULL;
    this -> t = t;
}

template < typename Type >
void BTree<Type>::traverse() {
    if( root != NULL )
        root -> traverse();
}

template < typename Type >
BTreeNode<Type>* BTree<Type>::search( Type k ) {
    return ( root == NULL ) ? NULL : root -> search( k );
}

template < typename Type >
void BTree<Type>::insert( Type k ) {
    if( root == NULL ) {
        root = new BTreeNode<Type>( t, true );
        root -> keys[ 0 ] = k;
        root -> n = 1;

    } else {
        if( root -> n == 2 * t - 1 ) {
            auto s = new BTreeNode<Type>( t, false );

            s -> C[ 0 ] = root;
            s -> splitChild( 0, root );

            int i = 0;
            if( s -> keys[ 0 ] < k )
                i++;

            s -> C[ i ] -> insertNonFull( k );

            root = s;
        }
        else
            root->insertNonFull( k );
    }
}

template < typename Type >
void BTree<Type>::remove( Type k ) {
    if( !root ) {
        cout << "The tree is empty\n";
        return;
    }

    root -> remove( k );

    if( root -> n == 0 ) {
        BTreeNode<Type> *tmp = root;
        if( root -> leaf )
            root = NULL;
        else
            root = root -> C[ 0 ];

        delete tmp;
    }
    return;
}

#endif
