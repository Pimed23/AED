#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

#include <iostream>
#include <vector>

class SegmentTree {
    public:
        SegmentTree( std::vector<int> nums );
        ~SegmentTree();

        void makeEmpty();
        void printTree() const;
        void update( int pos, int val );
        int sumRange( int first, int last );

    private:
        struct SNode {
            int suma;
            int begin;
            int end;
            SNode *left;
            SNode *right;
            SNode( int b, int e );
        };

        SNode *root = NULL;

        void makeEmpty( SNode *T );
        void printTree( SNode *T ) const;
        void update( SNode *T, int pos, int val );
        int sumRange( SNode *T, int first, int last );
        SNode* buildTree( std::vector<int> leaves, int first, int last );

};

SegmentTree::SNode::SNode( int b, int e ) 
    : begin( b )
    , end( e )
    , left( NULL )
    , right( NULL )
    , suma( 0 )
{}

SegmentTree::SegmentTree( std::vector<int> nums ) {
    root = buildTree( nums, 0, nums.size() - 1 );
}

SegmentTree::~SegmentTree() {
    makeEmpty( root );
}

void SegmentTree::makeEmpty() {
    makeEmpty( root );
}

void SegmentTree::makeEmpty( SNode *T ) {
    if( T != NULL ) {
        makeEmpty( T -> left );
        makeEmpty( T -> right );
        delete T;
    }
    T = NULL;
}

typename SegmentTree::SNode* SegmentTree::buildTree( std::vector<int> leaves, int first, int last ) {
    if( first > last ) {
        return NULL;
    } else {
        auto r = new SNode( first, last );
        if( first == last )
            r -> suma = leaves[ first ];
        else {
            int mid = first + ( last - first ) / 2;
            r -> left = buildTree( leaves, first, mid );
            r -> right = buildTree( leaves, mid + 1, last );
            r -> suma = r -> left -> suma + r -> right -> suma;
        }
        return r;
    }
}

void SegmentTree::printTree() const {
    if( root == NULL )
        std::cout << "The tree is empty" << std::endl;
    else
        printTree( root );
    std::cout << "\n";
}

void SegmentTree::printTree( SNode *T ) const {
    if( T != NULL ) {
        printTree( T -> left );
        std::cout << T -> suma << " ";
        printTree( T -> right );
    }
}

void SegmentTree::update( int pos, int val ) {
    update( root, pos, val );
}

void SegmentTree::update( SNode *T, int pos, int val ) {
    if( T -> begin == T -> end )
        T -> suma = val;
    else {
        int mid = T -> begin + ( T -> end - T -> begin ) / 2;
        if( pos <= mid )
            update( T -> left, pos, val );
        else
            update( T -> right, pos, val );
        T -> suma = T -> left -> suma + T -> right -> suma;
    }
}

int SegmentTree::sumRange( int first, int last ) {
    return sumRange( root, first, last );
}

int SegmentTree::sumRange( SNode *T, int first, int last ) {
    if( T -> end == last && T -> begin == first )
        return T -> suma;
    else {
        int mid = T -> begin + ( T -> end - T -> begin ) / 2;
        if( last <= mid )
            return sumRange( T -> left, first, last );
        else if( first >= mid + 1 )
            return sumRange( T -> right, first, last );
        else
            return sumRange( T -> right, mid + 1, last ) + sumRange( T -> left, first, mid );
    }
}

#endif