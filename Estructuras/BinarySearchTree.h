#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template < typename Type, typename Comparator = less<Type> >
class BSTree {
	public:
		BSTree() {
			root = nullptr;
		}
		BSTree( const BSTree<Type> &rhs ) : root{ nullptr } {
			root = clone( rhs.root );
		}
		~BSTree() {
			makeEmpty();
		}
		void makeEmpty( TreeNode *& T ) {
			if( T != nullptr ) {
				makeEmpty( t -> left );
				makeEmpty( t -> right );
				delete T;
			}
			T = nullptr;
		}
		bool contains( const Type &x ) const {
			return contains( x, root );
		}
		const Type& findMin() const {
			return findMin( root );
		}
		const Type& findMax() const {
			return findMax( root );
		}
		void insert( const Type &x ) {
			insert( x, root );
		}
		void remove( const Type &x ) {
			remove( x, root );
		}
	private:
		struct TreeNode {
			Type data;
			TreeNode *left;
			TreeNode *right;

			TreeNode() {
				data = 0;
				left = NULL;
				right = NULL;
			}

			TreeNode( const Type& nData, TreeNode *nLeft, TreeNode *nRight ) {
				data = nData;
				left = nLeft;
				right = nRight;
			}

			TreeNode( Type&& nData, TreeNode *nLeft, TreeNode *nRight ) {
				data = std::move( nData );
				left = nLeft;
				right = nRight;
			}
		};
		
		TreeNode *root;
		Comparator isLessThan;
		TreeNode* clone( TreeNode *T ) const {
			if( T == nullptr )
				return nullptr;
			else
				return new TreeNode{ T -> data, clone( T -> left ), clone( T -> right )};
		}
		bool contains( const Type &x, TreeNode *T ) const {
			if( T == nullptr )
				return false;
			else if( isLessThan( x, t -> data ))
				return contains( x, t -> left );
			else if( isLessThan( t -> data, x ))
				return contains( x, t -> right );
			else
				return true;
		}
		TreeNode* findMin( TreeNode *T ) const {
			if( T == nullptr )
				return nullptr;
			if( T -> left == nullptr )
				return T;
			return findMin( T -> left );
		}
		TreeNode* findMax( TreeNode *T ) const {
			if( T != nullptr )
				while ( T -> right != nullptr ) {
					T = T -> right;
				}
			return T;
		}
		void insert( const Type &x, TreeNode *& T ) {
			if( T == nullptr )
				T = new TreeNode{ x, nullptr, nullptr };
			else if( x < T -> data )
				insert( x, T -> left );
			else if( T -> data > T )
				insert( x, T -> right );
			else
				;
		}
		void insert( Type &&x, TreeNode *&T ) {
			if( T == nullptr )
				T = new TreeNode{ std::move( x ), nullptr, nullptr };
			else if( x < T -> data )
				insert( std::move( x ), T -> left );
			else if( T -> data > T )
				insert( std::move( x ), T -> right );
			else
				;
		}
		void remove( const Type &x, TreeNode *&T ) {
			if( T == nullptr )
				return;
			if( x < T -> data )
				remove( x, T -> left );
			else if( T -> data < x )
				remove( x, T -> right );
			else if( T -> left != nullptr && T -> right != nullptr ) {
				T -> data = findMin( T -> right ) -> data;
				remove( T -> data, T -> right );
			} else {
				TreeNode *oldNode = T;
				T = ( T -> left != nullptr ) ? T -> left : T -> right;
				delete oldNode;
			}
		}
		
};

#endif